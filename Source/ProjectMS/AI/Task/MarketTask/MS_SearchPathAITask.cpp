// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_SearchPathAITask.h"

UMS_SearchPathAITask::UMS_SearchPathAITask(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Search Path";
	bNotifyTick = true;
}

EBTNodeResult::Type UMS_SearchPathAITask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}

void UMS_SearchPathAITask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
}
