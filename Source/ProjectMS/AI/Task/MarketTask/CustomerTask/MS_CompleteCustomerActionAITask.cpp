// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_CompleteCustomerActionAITask.h"

#include "AI/AIController/MS_AIController.h"
#include "Animation/Market/Customer/MS_CustomerAIAnimInstance.h"
#include "Character/AICharacter/MS_MarketAICharacter.h"
#include "Units/MS_CustomerAIUnit.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Manager_Both/MS_UnitManager.h"


UMS_CompleteCustomerActionAITask::UMS_CompleteCustomerActionAITask(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Complete Customer Action";
	bNotifyTick = false;
}

EBTNodeResult::Type UMS_CompleteCustomerActionAITask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

	const TObjectPtr<UMS_CustomerAIUnit> AIUnit = Cast<UMS_CustomerAIUnit>(AICharacter->GetOwnerUnitBase());
	if(!AIUnit)
	{
		return EBTNodeResult::Type::Failed;
	}
	
	const TObjectPtr<UBlackboardComponent> BlackboardComp = Cast<UBlackboardComponent>(OwnerComp.GetBlackboardComponent());
	if(!BlackboardComp)
	{
		return EBTNodeResult::Type::Failed;
	}

	if(BlackboardComp->GetValueAsEnum(CustomerBoardKeyName::CustomerActionState) == static_cast<uint8>(EMS_CustomerActionState::Spline_GoHome))
	{
		AIController->UnPossess();
		gUnitMng.DestroyUnit(AIUnit->GetUnitHandle());
		return EBTNodeResult::Type::Succeeded;
	}
	
	EMS_CustomerActionType CustomerActionType = static_cast<EMS_CustomerActionType>(BlackboardComp->GetValueAsEnum(CustomerBoardKeyName::CustomerAction));
	AIUnit->UnregisterCustomerAction(CustomerActionType);
	
	BlackboardComp->SetValueAsEnum(CustomerBoardKeyName::CustomerAction, static_cast<uint8>(EMS_CustomerActionType::None));
	BlackboardComp->SetValueAsEnum(CustomerBoardKeyName::CustomerActionState, static_cast<uint8>(EMS_CustomerActionState::None));
	AIAnimInstance->SetActionState(EMS_CustomerActionState::None);
	
	return EBTNodeResult::Type::Succeeded;
}
