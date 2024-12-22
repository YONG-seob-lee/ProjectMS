#include "AI/AIController/BehaviorTree/BehaviorTreeTask/MS_BehaviorTreeTask.h"

UMS_BehaviorTreeTask::UMS_BehaviorTreeTask()
{
	bCreateNodeInstance = true;
	bTickIntervals = true;
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UMS_BehaviorTreeTask::ExecuteTask(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(aOwnerComp, aNodeMemory);

	return Result;
}

EBTNodeResult::Type UMS_BehaviorTreeTask::AbortTask(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory)
{
	EBTNodeResult::Type Result = Super::AbortTask(aOwnerComp, aNodeMemory);

	return Result;
}

void UMS_BehaviorTreeTask::TickTask(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory, float aDeltaSeconds)
{
	Super::TickTask(aOwnerComp, aNodeMemory, aDeltaSeconds);
}

void UMS_BehaviorTreeTask::OnMessage(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory, FName aMessage, int32 aRequestID, bool abSuccess)
{
	Super::OnMessage(aOwnerComp, aNodeMemory, aMessage, aRequestID, abSuccess);
}

void UMS_BehaviorTreeTask::OnTaskFinished(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory, EBTNodeResult::Type aTaskResult)
{
	Super::OnTaskFinished(aOwnerComp, aNodeMemory, aTaskResult);
}
