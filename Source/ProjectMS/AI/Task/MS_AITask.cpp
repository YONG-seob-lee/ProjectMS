// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_AITask.h"

UMS_AITask::UMS_AITask(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}

EBTNodeResult::Type UMS_AITask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}

EBTNodeResult::Type UMS_AITask::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::AbortTask(OwnerComp, NodeMemory);
}

void UMS_AITask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
}
