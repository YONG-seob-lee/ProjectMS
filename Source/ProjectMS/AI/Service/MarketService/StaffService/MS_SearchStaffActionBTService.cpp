// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_SearchStaffActionBTService.h"

#include "AI/AIController/StaffAIController/MS_StaffAIController.h"
#include "Character/AICharacter/StaffAICharacter/MS_StaffAICharacter.h"
#include "Units/MS_StaffAIUnit.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Mode/ModeObject/Container/MS_IssueTicketContainer.h"


UMS_SearchStaffActionBTService::UMS_SearchStaffActionBTService(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Search Staff Action";
	bCallTickOnSearchStart = false;
}

void UMS_SearchStaffActionBTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	const TObjectPtr<AMS_StaffAIController> AIController = Cast<AMS_StaffAIController>(OwnerComp.GetAIOwner());
	if(!AIController)
	{
		return;
	}

	const TObjectPtr<AMS_StaffAICharacter> AICharacter = Cast<AMS_StaffAICharacter>(AIController->GetCharacter());
	if(!AICharacter)
	{
		return;
	}

	const TObjectPtr<UMS_StaffAIUnit> AIUnit = Cast<UMS_StaffAIUnit>(AICharacter->GetOwnerUnitBase());
	if(!AIUnit)
	{
		return;
	}
	
	const TObjectPtr<UBlackboardComponent> BlackboardComp = Cast<UBlackboardComponent>(OwnerComp.GetBlackboardComponent());
	if(!BlackboardComp)
	{
		return;
	}

	EMS_StaffActionState ActionState = static_cast<EMS_StaffActionState>(BlackboardComp->GetValueAsEnum(StaffBoardKeyName::StaffActionState));

	if (ActionState == EMS_StaffActionState::None_Idle || ActionState == EMS_StaffActionState::None_IdleAction
		|| ActionState == EMS_StaffActionState::None_GoToRandomCounterUnit
		|| ActionState == EMS_StaffActionState::None_GoToRandomPoint_Display
		|| ActionState == EMS_StaffActionState::None_GoToRandomPoint_Shelf)
	{
		// Staff Action
		TWeakObjectPtr<UMS_IssueTicket> IssueTicket;
		EMS_StaffActionType StaffAction =  AIUnit->GetFirstStaffAction(IssueTicket);
	}
}
