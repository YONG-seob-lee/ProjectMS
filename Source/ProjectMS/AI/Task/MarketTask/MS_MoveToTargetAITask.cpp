// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_MoveToTargetAITask.h"

UMS_MoveToTargetAITask::UMS_MoveToTargetAITask(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Move To Target";
	bNotifyTick = true;
}

EBTNodeResult::Type UMS_MoveToTargetAITask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}

void UMS_MoveToTargetAITask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
}
