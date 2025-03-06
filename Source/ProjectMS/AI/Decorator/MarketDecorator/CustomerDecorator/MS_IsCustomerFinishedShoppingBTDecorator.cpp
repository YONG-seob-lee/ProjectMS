// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_IsCustomerFinishedShoppingBTDecorator.h"

#include "AI/AIController/MS_AIController.h"
#include "Animation/Market/Customer/MS_CustomerAIAnimInstance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AICharacter/MS_MarketAICharacter.h"
#include "Units/MS_CustomerAIUnit.h"

UMS_IsCustomerFinishedShoppingBTDecorator::UMS_IsCustomerFinishedShoppingBTDecorator(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Is Customer Finished Shopping";
}

bool UMS_IsCustomerFinishedShoppingBTDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const TObjectPtr<AMS_AIController> AIController = Cast<AMS_AIController>(OwnerComp.GetAIOwner());
	if(!AIController)
	{
		return false;
	}

	const TObjectPtr<AMS_MarketAICharacter> AICharacter = Cast<AMS_MarketAICharacter>(AIController->GetCharacter());
	if(!AICharacter)
	{
		return false;
	}

	
	const TObjectPtr<UMS_CustomerAIUnit> AIUnit = Cast<UMS_CustomerAIUnit>(AICharacter->GetOwnerUnitBase());
	if(!AIUnit)
	{
		return false;
	}

	const TObjectPtr<UMS_CustomerAIAnimInstance> AIAnimInstance = Cast<UMS_CustomerAIAnimInstance>(AICharacter->GetAIAnimInstance());
	if(!AIAnimInstance)
	{
		return false;
	}

	const TObjectPtr<UBlackboardComponent> BlackboardComp = Cast<UBlackboardComponent>(OwnerComp.GetBlackboardComponent());
	if(!BlackboardComp)
	{
		return false;
	}
	
	if(BlackboardComp->GetValueAsBool(CustomerBoardKeyName::IsCustomerPickUpAllItem) == true)
	{
		return false;
	}

	if(AIUnit->IsPickUpAllItems())
	{
		const EMS_CustomerActionType CustomerActionType = static_cast<EMS_CustomerActionType>(BlackboardComp->GetValueAsEnum(CustomerBoardKeyName::CustomerAction));
		AIUnit->UnregisterCustomerAction(CustomerActionType);
		
		BlackboardComp->SetValueAsBool(CustomerBoardKeyName::IsCustomerPickUpAllItem, true);
		BlackboardComp->SetValueAsEnum(CustomerBoardKeyName::CustomerAction, static_cast<uint8>(EMS_CustomerActionType::None));
		BlackboardComp->SetValueAsEnum(CustomerBoardKeyName::CustomerActionState, static_cast<uint8>(EMS_CustomerActionState::None));
		AIAnimInstance->SetActionState(EMS_CustomerActionState::None);
		return false;
	}
	else
	{
		return true;
	}
}
