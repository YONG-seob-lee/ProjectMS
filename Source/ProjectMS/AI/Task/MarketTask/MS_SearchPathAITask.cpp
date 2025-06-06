﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_SearchPathAITask.h"

#include "AI/AIController/MS_AIController.h"
#include "Character/AICharacter/MS_MarketAICharacter.h"
#include "Units/MS_MarketAIUnit.h"


UMS_SearchPathAITask::UMS_SearchPathAITask(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Search Path";
	bNotifyTick = true;
}

EBTNodeResult::Type UMS_SearchPathAITask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const TObjectPtr<AMS_AIController> AIController = Cast<AMS_AIController>(OwnerComp.GetAIOwner());
	if(!AIController)
	{
		return EBTNodeResult::Type::Failed;
	}

	const TObjectPtr<AMS_MarketAICharacter> AICharacter = Cast<AMS_MarketAICharacter>(AIController->GetCharacter());
	if(!AICharacter)
	{
		return EBTNodeResult::Type::Failed;
	}

	const TObjectPtr<UMS_MarketAIUnit> AIUnit = Cast<UMS_MarketAIUnit>(AICharacter->GetOwnerUnitBase());
	if(!AIUnit)
	{
		return EBTNodeResult::Type::Failed;
	}

	TArray<FIntVector2> Path = {};
	AIUnit->SearchPathToTarget(Path, AIUnit->GetActorGridPosition(), AIUnit->GetTargetPositions());

	if (Path.IsEmpty())
	{
		return EBTNodeResult::Type::Failed;
	}
	
	AIUnit->SetPath(Path);
	return EBTNodeResult::Type::Succeeded;
}

void UMS_SearchPathAITask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
}
