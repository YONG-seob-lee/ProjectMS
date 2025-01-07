#include "AI/AIController/StaffAIController/BehaviorTree/Task/MS_CheckUnloadingStorageStockTask.h"

#include "Kismet/GameplayStatics.h"

#include "Management/Manager_Both/MS_TableManager.h"
#include "Data/Table/RowBase/MS_Item.h"
#include "Actor/Storage/MS_Storage.h"
#include "Actor/Character/AICharacter/StaffAICharacter/MS_StaffAICharacter.h"

UMS_CheckUnloadingStorageStockTask::UMS_CheckUnloadingStorageStockTask()
{
	NodeName = FString(TEXT("Check Unloading Storage Stock"));
}

EBTNodeResult::Type UMS_CheckUnloadingStorageStockTask::ExecuteTask(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(aOwnerComp, aNodeMemory);

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
			if (ItemRowNameArray.Contains(StorageEachSlotStatus[j].StuffRowName) == true &&
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
			aOwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("UnloadingStorage")), AllStorageArray[i]);
			aOwnerComp.GetBlackboardComponent()->SetValueAsInt(FName(TEXT("LoadingStorageSlotOrder")), UnoccupiedSlotOrder);

			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
