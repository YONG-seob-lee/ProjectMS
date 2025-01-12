#include "AI/AIController/StaffAIController/BehaviorTree/Task/MS_UndeployStaffFromStorageBayTask.h"

#include "Actor/Character/AICharacter/StaffAICharacter/MS_StaffAICharacter.h"
#include "Actor/Storage/MS_Storage.h"

UMS_UndeployStaffFromStorageBayTask::UMS_UndeployStaffFromStorageBayTask()
{
	NodeName = FString(TEXT("Undeploy Staff From Storage Bay"));
}

EBTNodeResult::Type UMS_UndeployStaffFromStorageBayTask::ExecuteTask(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(aOwnerComp, aNodeMemory);

	AMS_StaffAICharacter* OwnerCharacter = Cast<AMS_StaffAICharacter>(aOwnerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("OwnerCharacter"))));
	AMS_Storage* TargetStorage = Cast<AMS_Storage>(aOwnerComp.GetBlackboardComponent()->GetValueAsObject(TargetStorageKey.SelectedKeyName));

	int TargetStorageBayOrder = INT_MIN;
	TargetStorageBayOrder = aOwnerComp.GetBlackboardComponent()->GetValueAsInt(FName(TEXT("TargetStorageBayOrder")));
	TargetStorage->BayComponentArray[TargetStorageBayOrder]->UndeployWorker();
	OwnerCharacter->SetWorkAnimationFlag(false);

	return EBTNodeResult::Succeeded;
}
