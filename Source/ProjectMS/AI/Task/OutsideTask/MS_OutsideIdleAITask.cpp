// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_OutsideIdleAITask.h"

#include "AI/AIController/OutsideAIController/MS_OutsideAIController.h"
#include "AI/AnimInstance/MS_AIAnimInstance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AICharacter/OutsideAICharacter/MS_OutsideAICharacter.h"

UMS_OutsideIdleAITask::UMS_OutsideIdleAITask(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Outside Idle";
	bNotifyTick = true;
}

EBTNodeResult::Type UMS_OutsideIdleAITask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const TObjectPtr<AMS_OutsideAIController> OutsideAIController = Cast<AMS_OutsideAIController>(OwnerComp.GetAIOwner());
	if(!OutsideAIController)
	{
		return EBTNodeResult::Failed;
	}

	const TObjectPtr<UBlackboardComponent> BlackboardComp = Cast<UBlackboardComponent>(OwnerComp.GetBlackboardComponent());
	if(!BlackboardComp)
	{
		return EBTNodeResult::Failed;
	}

	const float RandomIdleTime = GetRandomRemainTime(2.f, 8.f);
	BlackboardComp->SetValueAsFloat(OutsideBoardKeyName::RemainIdleTime, RandomIdleTime);

#if WITH_EDITOR
	MS_LOG(TEXT("Outside Duck AI \"Idle Task\" Start [Total Idle Time : %f]"), RandomIdleTime);
#endif
	
	return EBTNodeResult::InProgress; 
}

void UMS_OutsideIdleAITask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	
	const TObjectPtr<UBlackboardComponent> BlackboardComp = Cast<UBlackboardComponent>(OwnerComp.GetBlackboardComponent());
	if(!BlackboardComp)
	{
		return;
	}

	const float IdleRemainTime = BlackboardComp->GetValueAsFloat(OutsideBoardKeyName::RemainIdleTime);
	if(IdleRemainTime <= 0.f)
	{
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

		const TObjectPtr<UMS_AIAnimInstance> AIAnimInstance = AICharacter->GetAIAnimInstance();
		if(!AIAnimInstance)
		{
			return;
		}

		AIAnimInstance->SetIsActWalking(true);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	
	BlackboardComp->SetValueAsFloat(OutsideBoardKeyName::RemainIdleTime, IdleRemainTime - DeltaSeconds);
}
