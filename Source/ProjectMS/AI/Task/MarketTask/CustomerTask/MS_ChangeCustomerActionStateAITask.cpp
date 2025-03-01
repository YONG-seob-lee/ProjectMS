// Fill out your copyright notice in the Description page of Project Settings.

#include "MS_ChangeCustomerActionStateAITask.h"

#include "AI/AIController/MS_AIController.h"
#include "Animation/Market/Customer/MS_CustomerAIAnimInstance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AICharacter/MS_MarketAICharacter.h"


UMS_ChangeCustomerActionStateAITask::UMS_ChangeCustomerActionStateAITask(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Change Customer Action State";
	bNotifyTick = false;

	ActionState = EMS_CustomerActionState::None;
}

EBTNodeResult::Type UMS_ChangeCustomerActionStateAITask::ExecuteTask(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory)
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

	BlackboardComp->SetValueAsEnum(CustomerBoardKeyName::CustomerActionState, static_cast<uint8>(ActionState));

	AIAnimInstance->SetActionState(ActionState);
	
	return EBTNodeResult::Type::Succeeded;
}