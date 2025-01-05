#include "AI/AIController/StaffAIController/BehaviorTree/Task/MS_CheckAllStorageStockTask.h"

#include "Kismet/GameplayStatics.h"

#include "Management/Manager_Both/MS_TableManager.h"
#include "Data/Table/RowBase/MS_Item.h"
#include "Actor/Storage/MS_Storage.h"
#include "Actor/Character/AICharacter/StaffAICharacter/MS_StaffAICharacter.h"

UMS_CheckAllStorageStockTask::UMS_CheckAllStorageStockTask()
{
	NodeName = FString(TEXT("Check All Storage Stock"));
}

EBTNodeResult::Type UMS_CheckAllStorageStockTask::ExecuteTask(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory)
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
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMS_Storage::StaticClass(), AllStorageArray);
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
			if (ItemRowNameArray.Contains(StorageEachSlotStatus[j].StuffRowName) == true && StorageEachSlotStatus[j].ReservationFlag == false)
			{
				UnoccupiedSlotExistenceFlag = true;
				UnoccupiedSlotOrder = StorageEachSlotStatus[j].SlotOrder;
				StorageStuffName = StorageEachSlotStatus[j].StuffRowName;
				StorageStockCapacity = StorageEachSlotStatus[j].StockCapacity;
				StorageStockQuantity = StorageEachSlotStatus[j].StockQuantity;

				UE_LOG(LogTemp, Warning, TEXT("StorageStockCapacity: %d"), StorageStockCapacity);
				UE_LOG(LogTemp, Warning, TEXT("StorageStockQuantity: %d"), StorageStockQuantity);
				UE_LOG(LogTemp, Warning, TEXT("UnoccupiedSlotOrder: %d"), UnoccupiedSlotOrder);
				UE_LOG(LogTemp, Warning, TEXT("UnoccupiedSlotExistenceFlag: %d"), UnoccupiedSlotExistenceFlag);

				break;
			}
			UE_LOG(LogTemp, Warning, TEXT("StorageEachSlotStatus[j].StuffRowName: %s"), *StorageEachSlotStatus[j].StuffRowName.ToString());
		}

		if (UnoccupiedSlotExistenceFlag == false)
		{
			continue;
		}
		else
		{
			AMS_StaffAICharacter* OwnerCharacter = Cast<AMS_StaffAICharacter>(aOwnerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("OwnerCharacter"))));
			Cast<AMS_Storage>(AllStorageArray[i])->BayComponentArray[0]->ReserveWorker(OwnerCharacter);

			aOwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("TargetStorage")), AllStorageArray[i]);
			aOwnerComp.GetBlackboardComponent()->SetValueAsInt(FName(TEXT("StorageSlotOrder")), UnoccupiedSlotOrder);
			aOwnerComp.GetBlackboardComponent()->SetValueAsVector(FName(TEXT("TargetLocation")), Cast<AMS_Storage>(AllStorageArray[i])->StorageAssemblyAreaComponent->GetComponentLocation());
			aOwnerComp.GetBlackboardComponent()->SetValueAsString(FName(TEXT("StorageSlotStuffName")), StorageStuffName.ToString());
			aOwnerComp.GetBlackboardComponent()->SetValueAsInt(FName(TEXT("StorageSlotStockCapacity")), StorageStockCapacity);
			aOwnerComp.GetBlackboardComponent()->SetValueAsInt(FName(TEXT("StorageSlotStockQuantity")), StorageStockQuantity);

			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
