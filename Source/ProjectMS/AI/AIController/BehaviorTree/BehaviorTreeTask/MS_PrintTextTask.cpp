#include "AI/AIController/BehaviorTree/BehaviorTreeTask/MS_PrintTextTask.h"

UMS_PrintTextTask::UMS_PrintTextTask()
{
	NodeName = FString(TEXT("Print Debug String"));
}

EBTNodeResult::Type UMS_PrintTextTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("%s"), *StringToPrint));

	return Result;
}

EBTNodeResult::Type UMS_PrintTextTask::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::AbortTask(OwnerComp, NodeMemory);

	return Result;
}

void UMS_PrintTextTask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
}

void UMS_PrintTextTask::OnMessage(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, FName Message, int32 RequestID, bool bSuccess)
{
	Super::OnMessage(OwnerComp, NodeMemory, Message, RequestID, bSuccess);
}

void UMS_PrintTextTask::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
}
