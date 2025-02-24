// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_MoveToTargetAITask.h"

#include "AI/AIController/MS_AIController.h"
#include "Animation/MS_AIAnimInstance.h"
#include "Character/AICharacter/MS_MarketAICharacter.h"
#include "Units/MS_MarketAIUnit.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ContentsUtilities/MS_AIDefine.h"


UMS_MoveToTargetAITask::UMS_MoveToTargetAITask(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Move To Target";
	bNotifyTick = true;
}

EBTNodeResult::Type UMS_MoveToTargetAITask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
		
	const TObjectPtr<UMS_AIAnimInstance> AIAnimInstance = AICharacter->GetAIAnimInstance();
	if(!AIAnimInstance)
	{
		return EBTNodeResult::Type::Failed;
	}
	
	AIAnimInstance->SetIsActWalking(true);
	return EBTNodeResult::Type::InProgress;
}

void UMS_MoveToTargetAITask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	const TObjectPtr<AMS_AIController> AIController = Cast<AMS_AIController>(OwnerComp.GetAIOwner());
	if(!AIController)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Type::Failed);
		return;
	}

	const TObjectPtr<AMS_MarketAICharacter> AICharacter = Cast<AMS_MarketAICharacter>(AIController->GetCharacter());
	if(!AICharacter)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Type::Failed);
		return;
	}

	const TObjectPtr<UMS_MarketAIUnit> AIUnit = Cast<UMS_MarketAIUnit>(AICharacter->GetOwnerUnitBase());
	if(!AIUnit)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Type::Failed);
		return;
	}

	EBTNodeResult::Type Result = AIUnit->UpdateActorLocationByPath();
	if (Result != EBTNodeResult::Type::InProgress)
	{
		FinishLatentTask(OwnerComp, Result);
	}
}