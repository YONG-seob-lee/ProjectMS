#include "AI/AIController/StaffAIController/BehaviorTree/Task/MS_DepolyStaffToStorageBayTask.h"

#include "Actor/Character/AICharacter/StaffAICharacter/MS_StaffAICharacter.h"
#include "Actor/Prop/Furniture/Storage/MS_Storage.h"
#include "Component/Prop/Furniture/MS_StorageBayComponent.h"

UMS_DepolyStaffToStorageBayTask::UMS_DepolyStaffToStorageBayTask()
{
	NodeName = FString(TEXT("Deploy Staff To Storage Bay"));
}

EBTNodeResult::Type UMS_DepolyStaffToStorageBayTask::ExecuteTask(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(aOwnerComp, aNodeMemory);

	AMS_StaffAICharacter* OwnerCharacter = Cast<AMS_StaffAICharacter>(aOwnerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("OwnerCharacter"))));
	AMS_Storage* TargetStorage = Cast<AMS_Storage>(aOwnerComp.GetBlackboardComponent()->GetValueAsObject(TargetStorageKey.SelectedKeyName));

	int StorageBayOrder = INT_MIN;
	StorageBayOrder = aOwnerComp.GetBlackboardComponent()->GetValueAsInt(FName(TEXT("StorageBayOrder")));
	TargetStorage->BayComponentArray[StorageBayOrder]->DeployWorker(OwnerCharacter);
	TargetStorage->BayComponentArray[StorageBayOrder]->UnreserveWorker();
	OwnerCharacter->SetWorkAnimationFlag(true);

	return EBTNodeResult::Succeeded;
}
