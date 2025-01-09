#include "AI/AIController/StaffAIController/BehaviorTree/Task/MS_CheckStorageStockTask.h"

#include "Kismet/GameplayStatics.h"

#include "Management/Manager_Both/MS_TableManager.h"
#include "Data/Table/RowBase/MS_Item.h"
#include "Actor/Storage/MS_Storage.h"
#include "Component/Storage/MS_StorageBayComponent.h"
#include "Component/Storage/MS_StorageSlotComponent.h"
#include "Actor/Character/AICharacter/StaffAICharacter/MS_StaffAICharacter.h"

UMS_CheckStorageStockTask::UMS_CheckStorageStockTask()
{
	NodeName = FString(TEXT("Check All Storage Stock"));
}

EBTNodeResult::Type UMS_CheckStorageStockTask::ExecuteTask(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(aOwnerComp, aNodeMemory);
	return EBTNodeResult::InProgress;
}

void UMS_CheckStorageStockTask::TickTask(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory, float aDeltaSeconds)
{
	Super::TickTask(aOwnerComp, aNodeMemory, aDeltaSeconds);
	SetNextTickTime(aNodeMemory, 0.2f);

	TObjectPtr<UDataTable> ItemData = gTableMng.GetTableData(EMS_TableDataType::Item);
	TArray<FName> ItemRowNameArray = {};

	TArray<FName> DataRowNameArray = ItemData->GetRowNames();
	for (const FName& RowName : DataRowNameArray)
	{
		FMS_Item* ItemRowData = ItemData->FindRow<FMS_Item>(RowName, TEXT(""));
		if (ItemRowData != nullptr)
		{
			ItemRowNameArray.Add(ItemRowData->ItemName);
		}
	}

	bool LoadingUnoccupiedSlotExistenceFlag = false;
	int LoadingUnoccupiedSlotOrder = INT_MIN;

	FName LoadingStorageStuffName = NAME_None;
	int EmptyStuffQuantity = INT_MIN;

	AMS_Storage* FoundLoadingStorage = nullptr;

	TArray<AActor*> AllLoadingStorageArray = {};
	AMS_StaffAICharacter* OwnerCharacter = Cast<AMS_StaffAICharacter>(aOwnerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("OwnerCharacter"))));
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), OwnerCharacter->GetLoadingStorageType(), AllLoadingStorageArray);
	for (int i = 0; i < AllLoadingStorageArray.Num(); i++)
	{
		TArray<FMS_StorageEachSlotStatus> StorageEachSlotStatus = Cast<AMS_Storage>(AllLoadingStorageArray[i])->CheckStorageEachSlotStatus();

		for (int j = 0; j < StorageEachSlotStatus.Num(); ++j)
		{
			if (ItemRowNameArray.Contains(StorageEachSlotStatus[j].StuffRowName) == true && StorageEachSlotStatus[j].ReservationFlag == false && StorageEachSlotStatus[j].StockQuantity < StorageEachSlotStatus[j].StockCapacity)
			{
				FoundLoadingStorage = Cast<AMS_Storage>(AllLoadingStorageArray[i]);
				LoadingUnoccupiedSlotExistenceFlag = true;
				LoadingUnoccupiedSlotOrder = StorageEachSlotStatus[j].SlotOrder;
				LoadingStorageStuffName = StorageEachSlotStatus[j].StuffRowName;
				EmptyStuffQuantity = StorageEachSlotStatus[j].StockCapacity - StorageEachSlotStatus[j].StockQuantity;
				break;
			}
		}

		if (LoadingUnoccupiedSlotExistenceFlag == false)
		{
			continue;
		}
	}

	bool UnloadingUnoccupiedSlotExistenceFlag = false;
	int UnloadingUnoccupiedSlotOrder = INT_MIN;

	FName UnloadingStorageStuffName = NAME_None;
	int UnloadingStorageStockCapacity = INT_MIN;
	int UnloadingStorageStockQuantity = INT_MIN;

	AMS_Storage* FoundUnloadingStorage = nullptr;

	TArray<AActor*> AllUnloadingStorageArray = {};
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), OwnerCharacter->GetUnloadingStorageType(), AllUnloadingStorageArray);
	for (int i = 0; i < AllUnloadingStorageArray.Num(); i++)
	{
		TArray<FMS_StorageEachSlotStatus> StorageEachSlotStatus = Cast<AMS_Storage>(AllUnloadingStorageArray[i])->CheckStorageEachSlotStatus();

		for (int j = 0; j < StorageEachSlotStatus.Num(); ++j)
		{
			if (ItemRowNameArray.Contains(StorageEachSlotStatus[j].StuffRowName) == true &&
				LoadingStorageStuffName == StorageEachSlotStatus[j].StuffRowName &&
				StorageEachSlotStatus[j].ReservationFlag == false &&
				EmptyStuffQuantity <= StorageEachSlotStatus[j].StockQuantity)
			{
				FoundUnloadingStorage = Cast<AMS_Storage>(AllUnloadingStorageArray[i]);
				UnloadingUnoccupiedSlotExistenceFlag = true;
				UnloadingUnoccupiedSlotOrder = StorageEachSlotStatus[j].SlotOrder;
				UnloadingStorageStuffName = StorageEachSlotStatus[j].StuffRowName;
				UnloadingStorageStockCapacity = StorageEachSlotStatus[j].StockCapacity;
				UnloadingStorageStockQuantity = StorageEachSlotStatus[j].StockQuantity;
				break;
			}
			if (UnloadingUnoccupiedSlotExistenceFlag == false)
			{
				continue;
			}
		}

	}

	if (LoadingUnoccupiedSlotExistenceFlag == true && UnloadingUnoccupiedSlotExistenceFlag == true)
	{
		FoundLoadingStorage->SlotComponentArray[LoadingUnoccupiedSlotOrder]->ReserveWorker(OwnerCharacter);
		FoundUnloadingStorage->SlotComponentArray[UnloadingUnoccupiedSlotOrder]->ReserveWorker(OwnerCharacter);

		aOwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("LoadingStorage")), FoundLoadingStorage);
		aOwnerComp.GetBlackboardComponent()->SetValueAsInt(FName(TEXT("LoadingStorageSlotOrder")), LoadingUnoccupiedSlotOrder);
		aOwnerComp.GetBlackboardComponent()->SetValueAsInt(FName(TEXT("EmptyStuffQuantity")), EmptyStuffQuantity);
		aOwnerComp.GetBlackboardComponent()->SetValueAsString(FName(TEXT("StorageSlotStuffName")), LoadingStorageStuffName.ToString());

		aOwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("UnloadingStorage")), FoundUnloadingStorage);
		aOwnerComp.GetBlackboardComponent()->SetValueAsInt(FName(TEXT("UnloadingStorageSlotOrder")), UnloadingUnoccupiedSlotOrder);

		FinishLatentTask(aOwnerComp, EBTNodeResult::Succeeded);
	}

	FinishLatentTask(aOwnerComp, EBTNodeResult::InProgress);
}
