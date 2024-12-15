#include "AI/AIController/BehaviorTree/BehaviorTreeTask/MS_PrintTextTask.h"

UMS_PrintTextTask::UMS_PrintTextTask()
{
	NodeName = FString(TEXT("Print Debug String"));
}

EBTNodeResult::Type UMS_PrintTextTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetWorld())
	{
		if (TimerHandle.IsValid() == true)
			return Result;

		OwnerComp.GetWorld()->GetTimerManager().SetTimer(
			TimerHandle,
			FTimerDelegate::CreateUObject(this, &UMS_PrintTextTask::StopBehaviorTree, &OwnerComp),
			10.0f,
			false
		);
	}


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

void UMS_PrintTextTask::StopBehaviorTree(UBehaviorTreeComponent* OwnerComp)
{
	if (OwnerComp)
	{
		// Behavior Tree ÁßÁö
		OwnerComp->StopTree(EBTStopMode::Safe);
		TimerHandle.Invalidate();
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Behavior Tree Stopped!"));
	}

}
