// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_OutsideMoveAITask.h"

#include "MS_Define.h"
#include "AI/AIController/OutsideAIController/MS_OutsideAIController.h"
#include "AI/AnimInstance/MS_AIAnimInstance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AICharacter/OutsideAICharacter/MS_OutsideAICharacter.h"

UMS_OutsideMoveAITask::UMS_OutsideMoveAITask(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Outside Move";
	bNotifyTick = true;
}

EBTNodeResult::Type UMS_OutsideMoveAITask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

	const float RandomWalkTime = GetRandomRemainTime(5.f, 6.f);
	BlackboardComp->SetValueAsFloat(OutsideBoardKeyName::RemainWalkTime, RandomWalkTime);
    		
#if WITH_EDITOR
	MS_LOG(TEXT("Outside \"Move Task\" Start [Total Move Time : %f]"), RandomWalkTime);
#endif
	
	return EBTNodeResult::InProgress;
}

void UMS_OutsideMoveAITask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	const TObjectPtr<UBlackboardComponent> BlackboardComp = Cast<UBlackboardComponent>(OwnerComp.GetBlackboardComponent());
	if(!BlackboardComp)
	{
		return;
	}
	const float MoveRemainTime = BlackboardComp->GetValueAsFloat(OutsideBoardKeyName::RemainWalkTime);
	if(MoveRemainTime <= 0.f)
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
		
		AIAnimInstance->SetIsActWalking(false);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	
	BlackboardComp->SetValueAsFloat(OutsideBoardKeyName::RemainWalkTime, MoveRemainTime - DeltaSeconds);
}
