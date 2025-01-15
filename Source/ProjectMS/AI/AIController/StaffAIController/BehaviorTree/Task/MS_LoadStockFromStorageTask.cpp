#include "AI/AIController/StaffAIController/BehaviorTree/Task/MS_LoadStockFromStorageTask.h"

#include "Actor/Character/AICharacter/StaffAICharacter/MS_StaffAICharacter.h"
#include "Actor/Storage/MS_Storage.h"

UMS_LoadStockFromStorageTask::UMS_LoadStockFromStorageTask()
{
	NodeName = FString(TEXT("Load Stock From Storage Task"));
}

EBTNodeResult::Type UMS_LoadStockFromStorageTask::ExecuteTask(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(aOwnerComp, aNodeMemory);

	AMS_StaffAICharacter* OwnerCharacter = Cast<AMS_StaffAICharacter>(aOwnerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("OwnerCharacter"))));
	AMS_Storage* TargetStorage = Cast<AMS_Storage>(aOwnerComp.GetBlackboardComponent()->GetValueAsObject(TargetStorageKey.SelectedKeyName));

	FName StuffName = FName(*aOwnerComp.GetBlackboardComponent()->GetValueAsString(FName(TEXT("StorageSlotStuffName"))));
	int EmptyStuffQuantity = aOwnerComp.GetBlackboardComponent()->GetValueAsInt(FName(TEXT("EmptyStuffQuantity")));
	int UnloadingStorageSlotOrder = aOwnerComp.GetBlackboardComponent()->GetValueAsInt(FName(TEXT("UnloadingStorageSlotOrder")));

	TObjectPtr<UDataTable> ItemData = gTableMng.GetTableData(EMS_TableDataType::ItemData);
	FMS_ItemData* ItemRowData = ItemData->FindRow<FMS_ItemData>(StuffName, TEXT(""));

	TargetStorage->SlotComponentArray[UnloadingStorageSlotOrder]->UnreserveWorker();
	TargetStorage->SlotComponentArray[UnloadingStorageSlotOrder]->LoadStuff(StuffName, TargetStorage->SlotComponentArray[UnloadingStorageSlotOrder]->StockQuantity - EmptyStuffQuantity, SlotStaticMeshType);
	OwnerCharacter->AttachStockStaticMesh(ItemRowData->StuffBoxStaticMesh);

	return Result;
}

