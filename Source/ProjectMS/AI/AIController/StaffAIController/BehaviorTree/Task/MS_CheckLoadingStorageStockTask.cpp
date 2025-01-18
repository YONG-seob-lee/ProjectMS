#include "AI/AIController/StaffAIController/BehaviorTree/Task/MS_CheckLoadingStorageStockTask.h"

#include "Kismet/GameplayStatics.h"

#include "Management/Manager_Both/MS_TableManager.h"
#include "Data/Table/Caches/MS_ItemCacheTable.h"
#include "Data/Table/RowBase/MS_ItemData.h"

#include "Actor/Prop/Furniture/Storage/MS_Storage.h"
#include "Component/Prop/Furniture/MS_StorageBayComponent.h"
#include "Component/Prop/Furniture/MS_StorageSlotComponent.h"
#include "Actor/Character/AICharacter/StaffAICharacter/MS_StaffAICharacter.h"


UMS_CheckLoadingStorageStockTask::UMS_CheckLoadingStorageStockTask()
{
	NodeName = FString(TEXT("Check Loading Storage Stock"));
}

EBTNodeResult::Type UMS_CheckLoadingStorageStockTask::ExecuteTask(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(aOwnerComp, aNodeMemory);
	return EBTNodeResult::InProgress;
}

void UMS_CheckLoadingStorageStockTask::TickTask(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory, float aDeltaSeconds)
{
	Super::TickTask(aOwnerComp, aNodeMemory, aDeltaSeconds);
	SetNextTickTime(aNodeMemory, 0.2f);

	TObjectPtr<UMS_ItemCacheTable> CachedItemTable = Cast<UMS_ItemCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::ItemData));
	MS_CHECK(CachedItemTable);
	TArray<FName> ItemDataNameArray = CachedItemTable->GetAllItemNames();

	TArray<AActor*> AllStorageArray = {};
	AMS_StaffAICharacter* OwnerCharacter = Cast<AMS_StaffAICharacter>(aOwnerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("OwnerCharacter"))));
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), OwnerCharacter->GetLoadingStorageType(), AllStorageArray);
	for (int i = 0; i < AllStorageArray.Num(); i++)
	{
		TArray<FMS_StorageEachSlotStatus> StorageEachSlotStatus = Cast<AMS_Storage>(AllStorageArray[i])->CheckStorageEachSlotStatus();
		bool UnoccupiedSlotExistenceFlag = false;
		int UnoccupiedSlotOrder = INT_MIN;

		FName StorageStuffName = NAME_None;
		int EmptyStuffQuantity = INT_MIN;

		for (int j = 0; j < StorageEachSlotStatus.Num(); ++j)
		{
			if (ItemDataNameArray.Contains(StorageEachSlotStatus[j].StuffRowName) == true && StorageEachSlotStatus[j].ReservationFlag == false && StorageEachSlotStatus[j].StockQuantity < StorageEachSlotStatus[j].StockCapacity)
			{
				UnoccupiedSlotExistenceFlag = true;
				UnoccupiedSlotOrder = StorageEachSlotStatus[j].SlotOrder;
				StorageStuffName = StorageEachSlotStatus[j].StuffRowName;
				EmptyStuffQuantity = StorageEachSlotStatus[j].StockCapacity - StorageEachSlotStatus[j].StockQuantity;
				break;
			}
		}

		if (UnoccupiedSlotExistenceFlag == false)
		{
			continue;
		}
		else
		{
			Cast<AMS_Storage>(AllStorageArray[i])->SlotComponentArray[UnoccupiedSlotOrder]->ReserveWorker(OwnerCharacter);
			aOwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("LoadingStorage")), AllStorageArray[i]);
			aOwnerComp.GetBlackboardComponent()->SetValueAsInt(FName(TEXT("LoadingStorageSlotOrder")), UnoccupiedSlotOrder);
			aOwnerComp.GetBlackboardComponent()->SetValueAsInt(FName(TEXT("EmptyStuffQuantity")), EmptyStuffQuantity);

			aOwnerComp.GetBlackboardComponent()->SetValueAsString(FName(TEXT("StorageSlotStuffName")), StorageStuffName.ToString());
			FinishLatentTask(aOwnerComp, EBTNodeResult::Succeeded);
			break;
		}
	}
	FinishLatentTask(aOwnerComp, EBTNodeResult::InProgress);
}
