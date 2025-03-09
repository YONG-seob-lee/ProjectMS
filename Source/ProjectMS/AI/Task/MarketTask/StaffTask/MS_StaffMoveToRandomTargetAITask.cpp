// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_StaffMoveToRandomTargetAITask.h"

#include "AI/AIController/MS_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AICharacter/StaffAICharacter/MS_StaffAICharacter.h"
#include "Units/MS_StaffAIUnit.h"

UMS_StaffMoveToRandomTargetAITask::UMS_StaffMoveToRandomTargetAITask(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Staff Move To Random Target";
	bNotifyTick = true;
}

EBTNodeResult::Type UMS_StaffMoveToRandomTargetAITask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}

void UMS_StaffMoveToRandomTargetAITask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
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
	
	// ===== Staff가 대기 중에 랜덤 이동 하고 있을 때 ===== //
	EMS_StaffActionState ActionState = static_cast<EMS_StaffActionState>(BlackboardComp->GetValueAsEnum(StaffBoardKeyName::StaffActionState));

	if (ActionState == EMS_StaffActionState::None_Idle || ActionState == EMS_StaffActionState::None_IdleAction
		|| ActionState == EMS_StaffActionState::None_GoToRandomCounterUnit
		|| ActionState == EMS_StaffActionState::None_GoToRandomPoint_Display
		|| ActionState == EMS_StaffActionState::None_GoToRandomPoint_Shelf)
	{
		TWeakObjectPtr<UMS_IssueTicket> IssueTicket;
		EMS_StaffActionType ActionType = AIUnit->GetFirstStaffAction(IssueTicket);

		if (ActionType != EMS_StaffActionType::None)
		{
			AIUnit->ResetPath();
			FinishLatentTask(OwnerComp, EBTNodeResult::Type::Failed);
			return;
		}
	}
	// ========== //

	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
}
