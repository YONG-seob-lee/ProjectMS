#include "AI/AIController/StaffAIController/BehaviorTree/Task/MS_CheckUnloadingStorageStockTask.h"

#include "Kismet/GameplayStatics.h"

#include "Management/Manager_Both/MS_TableManager.h"
#include "Data/Table/Caches/MS_ItemCacheTable.h"
#include "Data/Table/RowBase/MS_ItemData.h"
#include "Actor/Prop/Furniture/Storage/MS_Storage.h"
#include "Actor/Character/AICharacter/StaffAICharacter/MS_StaffAICharacter.h"
#include "Component/Prop/Furniture/MS_StorageSlotComponent.h"

UMS_CheckUnloadingStorageStockTask::UMS_CheckUnloadingStorageStockTask()
{
	NodeName = FString(TEXT("Check Unloading Storage Stock"));
}

EBTNodeResult::Type UMS_CheckUnloadingStorageStockTask::ExecuteTask(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(aOwnerComp, aNodeMemory);
	return EBTNodeResult::InProgress;
}

void UMS_CheckUnloadingStorageStockTask::TickTask(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory, float aDeltaSeconds)
{
	Super::TickTask(aOwnerComp, aNodeMemory, aDeltaSeconds);
	SetNextTickTime(aNodeMemory, 0.2f);

	TObjectPtr<UMS_ItemCacheTable> CachedItemTable = Cast<UMS_ItemCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::ItemData));
	MS_CHECK(CachedItemTable);
	TArray<FName> ItemDataNameArray = CachedItemTable->GetAllItemNames();

	TArray<AActor*> AllStorageArray = {};
	AMS_StaffAICharacter* OwnerCharacter = Cast<AMS_StaffAICharacter>(aOwnerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("OwnerCharacter"))));
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), OwnerCharacter->GetUnloadingStorageType(), AllStorageArray);

	for (int i = 0; i < AllStorageArray.Num(); i++)
	{
		TArray<FMS_StorageEachSlotStatus> StorageEachSlotStatus = Cast<AMS_Storage>(AllStorageArray[i])->CheckStorageEachSlotStatus();
		bool UnoccupiedSlotExistenceFlag = false;
		int UnoccupiedSlotOrder = INT_MIN;

		FName StorageStuffName = NAME_None;
		int StorageStockCapacity = INT_MIN;
		int StorageStockQuantity = INT_MIN;

		for (int j = 0; j < StorageEachSlotStatus.Num(); ++j)
		{
			if (ItemDataNameArray.Contains(StorageEachSlotStatus[j].StuffRowName) == true &&
				aOwnerComp.GetBlackboardComponent()->GetValueAsString(FName(TEXT("StorageSlotStuffName"))) == StorageEachSlotStatus[j].StuffRowName &&
				StorageEachSlotStatus[j].ReservationFlag == false &&
				aOwnerComp.GetBlackboardComponent()->GetValueAsInt(FName(TEXT("EmptyStuffQuantity"))) <= StorageEachSlotStatus[j].StockQuantity)
			{
				UnoccupiedSlotExistenceFlag = true;
				UnoccupiedSlotOrder = StorageEachSlotStatus[j].SlotOrder;
				StorageStuffName = StorageEachSlotStatus[j].StuffRowName;
				StorageStockCapacity = StorageEachSlotStatus[j].StockCapacity;
				StorageStockQuantity = StorageEachSlotStatus[j].StockQuantity;
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

			aOwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("UnloadingStorage")), AllStorageArray[i]);
			aOwnerComp.GetBlackboardComponent()->SetValueAsInt(FName(TEXT("UnloadingStorageSlotOrder")), UnoccupiedSlotOrder);

			FinishLatentTask(aOwnerComp, EBTNodeResult::Succeeded);
			break;
		}
	}
	FinishLatentTask(aOwnerComp, EBTNodeResult::InProgress);
}
