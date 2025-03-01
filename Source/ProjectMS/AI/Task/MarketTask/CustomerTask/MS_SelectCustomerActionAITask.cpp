// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_SelectCustomerActionAITask.h"

#include "AI/AIController/CustomerAIController/MS_CustomerAIController.h"
#include "Animation/Market/Customer/MS_CustomerAIAnimInstance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AICharacter/CustomerAICharacter/MS_CustomerAICharacter.h"
#include "Units/MS_CustomerAIUnit.h"


UMS_SelectCustomerActionAITask::UMS_SelectCustomerActionAITask(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Select Customer Action";
	bNotifyTick = false;
}

EBTNodeResult::Type UMS_SelectCustomerActionAITask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const TObjectPtr<AMS_CustomerAIController> AIController = Cast<AMS_CustomerAIController>(OwnerComp.GetAIOwner());
	if(!AIController)
	{
		return EBTNodeResult::Type::Failed;
	}

	const TObjectPtr<AMS_CustomerAICharacter> AICharacter = Cast<AMS_CustomerAICharacter>(AIController->GetCharacter());
	if(!AICharacter)
	{
		return EBTNodeResult::Type::Failed;
	}

	const TObjectPtr<UMS_CustomerAIUnit> AIUnit = Cast<UMS_CustomerAIUnit>(AICharacter->GetOwnerUnitBase());
	if(!AIUnit)
	{
		return EBTNodeResult::Type::Failed;
	}
	
	const TObjectPtr<UMS_CustomerAIAnimInstance> AIAnimInstance = Cast<UMS_CustomerAIAnimInstance>(AICharacter->GetAIAnimInstance());
	if(!AIAnimInstance)
	{
		return EBTNodeResult::Type::Failed;
	}
	
	const TObjectPtr<UBlackboardComponent> BlackboardComp = Cast<UBlackboardComponent>(OwnerComp.GetBlackboardComponent());
	if(!BlackboardComp)
	{
		return EBTNodeResult::Type::Failed;
	}
	
	// Customer Action
	EMS_CustomerActionType CustomerAction =  AIUnit->GetCustomerActionType();

	BlackboardComp->SetValueAsEnum(CustomerBoardKeyName::CustomerAction, static_cast<uint8>(CustomerAction));

	if (CustomerAction == EMS_CustomerActionType::None)
	{
		return EBTNodeResult::Type::Failed;
	}

	// Issue Type, Action State
	EMS_CustomerActionState ActionState = EMS_CustomerActionState::None;
	
	if (CustomerAction == EMS_CustomerActionType::GoToMarket)
	{
		ActionState = EMS_CustomerActionState::Spline_GoToMarket;
	}
	
	BlackboardComp->SetValueAsEnum(CustomerBoardKeyName::CustomerActionState, static_cast<uint8>(ActionState));

	AIAnimInstance->SetActionState(ActionState);
	
	return EBTNodeResult::Type::Succeeded;
}
