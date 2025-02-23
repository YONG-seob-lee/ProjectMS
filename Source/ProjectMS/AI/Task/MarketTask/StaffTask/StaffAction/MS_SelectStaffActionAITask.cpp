// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_SelectStaffActionAITask.h"

#include "AI/AIController/StaffAIController/MS_StaffAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AICharacter/StaffAICharacter/MS_StaffAICharacter.h"
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
	
	const TObjectPtr<UBlackboardComponent> BlackboardComp = Cast<UBlackboardComponent>(OwnerComp.GetBlackboardComponent());
	if(!BlackboardComp)
	{
		return EBTNodeResult::Type::Failed;
	}

	TWeakObjectPtr<UMS_IssueTicket> IssueTicket;
	EMS_StaffActionType SelectedStaffAction =  AIUnit->GetFirstStaffAction(IssueTicket);
	
	if (SelectedStaffAction == EMS_StaffActionType::None)
	{
		return EBTNodeResult::Type::Failed;
	}
	
	BlackboardComp->SetValueAsEnum(StaffBoardKeyName::SelectedStaffAction, static_cast<uint8>(SelectedStaffAction));

	if (SelectedStaffAction == EMS_StaffActionType::Issue)
	{
		EMS_StaffIssueType IssueType = IssueTicket->GetIssueType();

		if (IssueType == EMS_StaffIssueType::ReturnItemsFromDisplay || IssueType == EMS_StaffIssueType::ReturnItemsFromShelf)
		{
			BlackboardComp->SetValueAsEnum(StaffBoardKeyName::CurrentIssueProcess, static_cast<uint8>(EMS_StaffIssueProcess::GoToRequestUnit));
		}
		else if (IssueType == EMS_StaffIssueType::AddItemsToDisplay || IssueType == EMS_StaffIssueType::AddItemsToShelf)
		{
			BlackboardComp->SetValueAsEnum(StaffBoardKeyName::CurrentIssueProcess, static_cast<uint8>(EMS_StaffIssueProcess::GoToTakeOutTargets));	
		}
	}
	
	return EBTNodeResult::Type::Succeeded;
}