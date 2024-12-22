#include "AI/AIController/BehaviorTree/BehaviorTreeTask/MS_PrintTextTask.h"

UMS_PrintTextTask::UMS_PrintTextTask()
{
	NodeName = FString(TEXT("Print Debug String"));
}

EBTNodeResult::Type UMS_PrintTextTask::ExecuteTask(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(aOwnerComp, aNodeMemory);

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("%s"), *StringToPrint));

	return Result;
}

EBTNodeResult::Type UMS_PrintTextTask::AbortTask(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory)
{
	EBTNodeResult::Type Result = Super::AbortTask(aOwnerComp, aNodeMemory);

	return Result;
}

void UMS_PrintTextTask::TickTask(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory, float aDeltaSeconds)
{
	Super::TickTask(aOwnerComp, aNodeMemory, aDeltaSeconds);
}

void UMS_PrintTextTask::OnMessage(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory, FName aMessage, int32 aRequestID, bool abSuccess)
{
	Super::OnMessage(aOwnerComp, aNodeMemory, aMessage, aRequestID, abSuccess);
}

void UMS_PrintTextTask::OnTaskFinished(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory, EBTNodeResult::Type aTaskResult)
{
	Super::OnTaskFinished(aOwnerComp, aNodeMemory, aTaskResult);
}
