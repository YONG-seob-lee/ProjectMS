#include "AI/AIController/StaffAIController/BehaviorTree/Task/MS_UnloadStockFromStorageTask.h"

#include "Actor/Character/AICharacter/StaffAICharacter/MS_StaffAICharacter.h"
#include "Actor/Prop/Furniture/Storage/MS_Storage.h"

UMS_UnloadStockFromStorageTask::UMS_UnloadStockFromStorageTask()
{
	NodeName = FString(TEXT("Unload Stock From Storage Task"));
}

EBTNodeResult::Type UMS_UnloadStockFromStorageTask::ExecuteTask(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(aOwnerComp, aNodeMemory);

	AMS_StaffAICharacter* OwnerCharacter = Cast<AMS_StaffAICharacter>(aOwnerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("OwnerCharacter"))));
	AMS_Storage* TargetStorage = Cast<AMS_Storage>(aOwnerComp.GetBlackboardComponent()->GetValueAsObject(TargetStorageKey.SelectedKeyName));

	FName StuffName = FName(*aOwnerComp.GetBlackboardComponent()->GetValueAsString(FName(TEXT("StorageSlotStuffName"))));
	int EmptyStuffQuantity = aOwnerComp.GetBlackboardComponent()->GetValueAsInt(FName(TEXT("EmptyStuffQuantity")));
	int LoadingStorageSlotOrder = aOwnerComp.GetBlackboardComponent()->GetValueAsInt(FName(TEXT("LoadingStorageSlotOrder")));

	TargetStorage->SlotComponentArray[LoadingStorageSlotOrder]->LoadStuff(StuffName, EmptyStuffQuantity, SlotStaticMeshType);
	TargetStorage->SlotComponentArray[LoadingStorageSlotOrder]->UnreserveWorker();
	OwnerCharacter->DeattachStockStaticMesh();
	OwnerCharacter->CarriedStuffName = NAME_None;

	return Result;
}
