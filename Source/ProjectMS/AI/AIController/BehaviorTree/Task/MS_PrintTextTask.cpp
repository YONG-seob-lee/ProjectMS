#include "AI/AIController/BehaviorTree/Task/MS_PrintTextTask.h"

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