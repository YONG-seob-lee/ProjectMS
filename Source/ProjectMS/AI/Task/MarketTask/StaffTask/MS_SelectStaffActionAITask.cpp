// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_SelectStaffActionAITask.h"

#include "AI/AIController/StaffAIController/MS_StaffAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AICharacter/StaffAICharacter/MS_StaffAICharacter.h"
#include "Animation/Market/Staff/MS_StaffAIAnimInstance.h"
#include "Mode/ModeObject/Container/MS_IssueTicketContainer.h"
#include "Units/MS_StaffAIUnit.h"


UMS_SelectStaffActionAITask::UMS_SelectStaffActionAITask(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Select Staff Action";
	bNotifyTick = false;
}

EBTNodeResult::Type UMS_SelectStaffActionAITask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const TObjectPtr<AMS_StaffAIController> AIController = Cast<AMS_StaffAIController>(OwnerComp.GetAIOwner());
	if(!AIController)
	{
		return EBTNodeResult::Type::Failed;
	}

	const TObjectPtr<AMS_StaffAICharacter> AICharacter = Cast<AMS_StaffAICharacter>(AIController->GetCharacter());
	if(!AICharacter)
	{
		return EBTNodeResult::Type::Failed;
	}

	const TObjectPtr<UMS_StaffAIUnit> AIUnit = Cast<UMS_StaffAIUnit>(AICharacter->GetOwnerUnitBase());
	if(!AIUnit)
	{
		return EBTNodeResult::Type::Failed;
	}

	const TObjectPtr<UMS_StaffAIAnimInstance> AIAnimInstance = Cast<UMS_StaffAIAnimInstance>(AICharacter->GetAIAnimInstance());
	if(!AIAnimInstance)
	{
		return EBTNodeResult::Type::Failed;
	}
	
	const TObjectPtr<UBlackboardComponent> BlackboardComp = Cast<UBlackboardComponent>(OwnerComp.GetBlackboardComponent());
	if(!BlackboardComp)
	{
		return EBTNodeResult::Type::Failed;
	}
	
	// Staff Action
	TWeakObjectPtr<UMS_IssueTicket> IssueTicket;
	EMS_StaffActionType StaffAction =  AIUnit->GetFirstStaffAction(IssueTicket);

	BlackboardComp->SetValueAsEnum(StaffBoardKeyName::StaffAction, static_cast<uint8>(StaffAction));

	if (StaffAction == EMS_StaffActionType::None)
	{
		return EBTNodeResult::Type::Succeeded;
	}

	// Issue Type, Action State
	EMS_StaffIssueType IssueType = EMS_StaffIssueType::None;
	EMS_StaffActionState ActionState = EMS_StaffActionState::None;
	
	if (StaffAction == EMS_StaffActionType::GoToWork)
	{
		ActionState = EMS_StaffActionState::Spline_GoToWork;
	}
	
	else if (StaffAction == EMS_StaffActionType::Issue)
	{
		IssueType = IssueTicket->GetIssueType();
		
		if (IssueType == EMS_StaffIssueType::ReturnItemsFromDisplay || IssueType == EMS_StaffIssueType::ReturnItemsFromShelf)
		{
			ActionState = EMS_StaffActionState::Return_PickUp_SearchRequestUnit;
		}
		else if (IssueType == EMS_StaffIssueType::AddItemsToDisplay || IssueType == EMS_StaffIssueType::AddItemsToShelf)
		{
			ActionState = EMS_StaffActionState::Add_PickUp_SearchTargets;
		}

		else if (IssueType == EMS_StaffIssueType::Payment)
		{
			ActionState = EMS_StaffActionState::Payment_SearchCounterUnit;
		}
	}
	
	BlackboardComp->SetValueAsEnum(StaffBoardKeyName::StaffIssueType, static_cast<uint8>(IssueType));
	BlackboardComp->SetValueAsEnum(StaffBoardKeyName::StaffActionState, static_cast<uint8>(ActionState));

	AIAnimInstance->SetActionState(ActionState);
	
	return EBTNodeResult::Type::Succeeded;
}