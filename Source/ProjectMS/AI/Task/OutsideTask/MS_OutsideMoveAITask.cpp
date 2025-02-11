// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_OutsideMoveAITask.h"

#include "MS_Define.h"
#include "AI/AIController/OutsideAIController/MS_OutsideAIController.h"
#include "AI/Blackboard/MS_OutsideBlackboardComponent.h"

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

	const TObjectPtr<UMS_OutsideBlackboardComponent> BlackboardComp = Cast<UMS_OutsideBlackboardComponent>(OwnerComp.GetBlackboardComponent());
	if(!BlackboardComp)
	{
		return EBTNodeResult::Failed;
	}

	BlackboardComp->SetValueAsFloat(OutsideBoardKeyName::RemainTime, 10.f);
    		
	MS_LOG(TEXT("Outside Move Task Start"));
	return EBTNodeResult::InProgress;
}

void UMS_OutsideMoveAITask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	const TObjectPtr<UMS_OutsideBlackboardComponent> BlackboardComp = Cast<UMS_OutsideBlackboardComponent>(OwnerComp.GetBlackboardComponent());
	if(!BlackboardComp)
	{
		return;
	}
	const float MoveRemainTime = BlackboardComp->GetValueAsFloat(OutsideBoardKeyName::RemainTime);
	if(MoveRemainTime <= 0.f)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	
	BlackboardComp->SetValueAsFloat(OutsideBoardKeyName::RemainTime, MoveRemainTime - DeltaSeconds);
}
