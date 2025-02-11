// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_OutsideIdleAITask.h"

#include "AI/AIController/OutsideAIController/MS_OutsideAIController.h"
#include "AI/AnimInstance/MS_AIAnimInstance.h"
#include "AI/Blackboard/MS_OutsideBlackboardComponent.h"
#include "Character/AICharacter/OutsideAICharacter/MS_OutsideAICharacter.h"

UMS_OutsideIdleAITask::UMS_OutsideIdleAITask(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Outside Idle";
}

EBTNodeResult::Type UMS_OutsideIdleAITask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const TObjectPtr<AMS_OutsideAIController> OutsideAIController = Cast<AMS_OutsideAIController>(OwnerComp.GetAIOwner());
	if(!OutsideAIController)
	{
		return EBTNodeResult::Failed;
	}

	const TObjectPtr<UMS_OutsideBlackboardComponent> BlackboardComp = Cast<UMS_OutsideBlackboardComponent>(OwnerComp.GetBlackboardComponent());
	if(!BlackboardComp)
	{
		return EBTNodeResult::Failed;
	}

	BlackboardComp->SetValueAsBool(TEXT("bFinishedIdleAnimation"), false);

	return EBTNodeResult::InProgress; 
}

void UMS_OutsideIdleAITask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	const TObjectPtr<AMS_OutsideAIController> OutsideAIController = Cast<AMS_OutsideAIController>(OwnerComp.GetAIOwner());
	if(!OutsideAIController)
	{
		return;
	}

	const TObjectPtr<AMS_OutsideAICharacter> AICharacter = Cast<AMS_OutsideAICharacter>(OutsideAIController->GetCharacter());
	if(!AICharacter)
	{
		return;
	}

	const TObjectPtr<UMS_AIAnimInstance> AIAnimInstance = AICharacter->GetAnimInstance();
	if(!AIAnimInstance)
	{
		return;
	}

	if(AIAnimInstance->AnimIsFinished())
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
