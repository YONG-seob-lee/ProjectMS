// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_CompleteStaffActionAITask.h"

#include "AI/AIController/MS_AIController.h"
#include "Animation/Market/Staff/MS_StaffAIAnimInstance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AICharacter/MS_MarketAICharacter.h"
#include "Units/MS_StaffAIUnit.h"


UMS_CompleteStaffActionAITask::UMS_CompleteStaffActionAITask(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Complete Staff Action";
	bNotifyTick = false;
}

EBTNodeResult::Type UMS_CompleteStaffActionAITask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const TObjectPtr<AMS_AIController> AIController = Cast<AMS_AIController>(OwnerComp.GetAIOwner());
	if(!AIController)
	{
		return EBTNodeResult::Type::Failed;
	}

	const TObjectPtr<AMS_MarketAICharacter> AICharacter = Cast<AMS_MarketAICharacter>(AIController->GetCharacter());
	if(!AICharacter)
	{
		return EBTNodeResult::Type::Failed;
	}
		
	const TObjectPtr<UMS_StaffAIAnimInstance> AIAnimInstance = Cast<UMS_StaffAIAnimInstance>(AICharacter->GetAIAnimInstance());
	if(!AIAnimInstance)
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

	EMS_StaffActionType StaffActionType = static_cast<EMS_StaffActionType>(BlackboardComp->GetValueAsEnum(StaffBoardKeyName::StaffAction));

	if (StaffActionType == EMS_StaffActionType::Issue)
	{
		AIUnit->UnregisterAsIssueTicketStaff();
	}
	else
	{
		AIUnit->UnregisterNoneIssueStaffAction(StaffActionType);
	}
	
	BlackboardComp->SetValueAsEnum(StaffBoardKeyName::StaffActionState, static_cast<uint8>(EMS_StaffActionState::None));
	AIAnimInstance->SetActionProcess(EMS_StaffActionState::None);
	
	return EBTNodeResult::Type::Succeeded;
}
