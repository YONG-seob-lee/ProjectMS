// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_OutsideMoveToMarketAITask.h"

#include "AI/AIController/OutsideAIController/MS_OutsideAIController.h"
#include "AI/AnimInstance/MS_AIAnimInstance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AICharacter/OutsideAICharacter/MS_OutsideAICharacter.h"
#include "Manager_Both/MS_UnitManager.h"

namespace MoveToMarket
{
	const FVector Location = FVector(0.f, 1.f, 0.f);
}

UMS_OutsideMoveToMarketAITask::UMS_OutsideMoveToMarketAITask(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Outside Move To Market";
	bNotifyTick = true;
}

EBTNodeResult::Type UMS_OutsideMoveToMarketAITask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const TObjectPtr<UBlackboardComponent> BlackboardComp = Cast<UBlackboardComponent>(OwnerComp.GetBlackboardComponent());
	if(!BlackboardComp)
	{
		return EBTNodeResult::Failed;
	}
	const TObjectPtr<AMS_OutsideAIController> OutsideAIController = Cast<AMS_OutsideAIController>(OwnerComp.GetAIOwner());
	if(!OutsideAIController)
	{
		return EBTNodeResult::Failed;
	}

	const TObjectPtr<AMS_OutsideAICharacter> AICharacter = Cast<AMS_OutsideAICharacter>(OutsideAIController->GetCharacter());
	if(!AICharacter)
	{
		return EBTNodeResult::Failed;
	}

	const TObjectPtr<UMS_AIAnimInstance> AIAnimInstance = AICharacter->GetAIAnimInstance();
	if(!AIAnimInstance)
	{
		return EBTNodeResult::Failed;
	}

	BlackboardComp->SetValueAsFloat(OutsideBoardKeyName::RemainWalkToMarketTime, 3.f);
	AIAnimInstance->SetIsActFinished(true);
	return EBTNodeResult::InProgress;
}

void UMS_OutsideMoveToMarketAITask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	const TObjectPtr<UBlackboardComponent> BlackboardComp = Cast<UBlackboardComponent>(OwnerComp.GetBlackboardComponent());
	if(!BlackboardComp)
	{
		return;
	}
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
	
	const float WalkToMarketRemainTime = BlackboardComp->GetValueAsFloat(OutsideBoardKeyName::RemainWalkToMarketTime);
	if(WalkToMarketRemainTime <= 0.f)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

		gUnitMng.DestroyUnit(AICharacter->GetUnitHandle());
	}

	BlackboardComp->SetValueAsFloat(OutsideBoardKeyName::RemainWalkToMarketTime, WalkToMarketRemainTime - DeltaSeconds);
	AICharacter->AddMovementInput(MoveToMarket::Location);
}
