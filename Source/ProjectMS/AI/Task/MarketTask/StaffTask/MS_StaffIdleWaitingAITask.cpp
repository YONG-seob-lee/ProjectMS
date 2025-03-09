// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_StaffIdleWaitingAITask.h"

#include "AI/AIController/MS_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AICharacter/StaffAICharacter/MS_StaffAICharacter.h"
#include "Units/MS_StaffAIUnit.h"


UMS_StaffIdleWaitingAITask::UMS_StaffIdleWaitingAITask(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Staff Idle Waiting";
	bNotifyTick = true;
}

EBTNodeResult::Type UMS_StaffIdleWaitingAITask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	RemainIdleTime = MaxIdleTime;

	return EBTNodeResult::Type::InProgress;
}

void UMS_StaffIdleWaitingAITask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	const TObjectPtr<AMS_AIController> AIController = Cast<AMS_AIController>(OwnerComp.GetAIOwner());
	if(!AIController)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Type::Failed);
		return;
	}

	const TObjectPtr<AMS_StaffAICharacter> AICharacter = Cast<AMS_StaffAICharacter>(AIController->GetCharacter());
	if(!AICharacter)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Type::Failed);
		return;
	}

	const TObjectPtr<UMS_StaffAIUnit> AIUnit = Cast<UMS_StaffAIUnit>(AICharacter->GetOwnerUnitBase());
	if(!AIUnit)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Type::Failed);
		return;
	}

	const TObjectPtr<UBlackboardComponent> BlackboardComp = Cast<UBlackboardComponent>(OwnerComp.GetBlackboardComponent());
	if(!BlackboardComp)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Type::Failed);
		return;
	}
	
	EMS_StaffActionState ActionState = static_cast<EMS_StaffActionState>(BlackboardComp->GetValueAsEnum(StaffBoardKeyName::StaffActionState));
	
	TWeakObjectPtr<UMS_IssueTicket> IssueTicket;
	EMS_StaffActionType ActionType = AIUnit->GetFirstStaffAction(IssueTicket);

	if (ActionType != EMS_StaffActionType::None)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Type::Failed);
	}

	RemainIdleTime -= DeltaSeconds;
	if (RemainIdleTime <= 0.f)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Type::Succeeded);
	}
}
