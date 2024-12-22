#include "AI/AIController/BehaviorTree/BehaviorTreeTask/MS_MoveToLocationTask.h"

UMS_MoveToLocationTask::UMS_MoveToLocationTask()
{
	NodeName = FString(TEXT("Move To Location"));
	AcceptableRadius = 0.5f;
	bAllowStrafe = false;
	bReachTestIncludesAgentRadius = false;
	bReachTestIncludesGoalRadius = false;
	bObserveBlackboardValue = false;
	ObservedBlackboardValueTolerance = 0.45f;

	BlackboardKey.AllowedTypes.Empty();
	BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UMS_MoveToLocationTask, BlackboardKey));
}

FString UMS_MoveToLocationTask::GetStaticDescription() const
{
	FString Result = FString(TEXT("MoveToLocationBehaviorTreeTask"));

	Result = Result + '\n' + TEXT("BlackboardKey: ") + BlackboardKey.SelectedKeyName.ToString();

	return Result;
}

EBTNodeResult::Type UMS_MoveToLocationTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
