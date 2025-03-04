// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_IsCustomerActionStateBTDecorator.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "ContentsUtilities/MS_AIDefine.h"


UMS_IsCustomerActionStateBTDecorator::UMS_IsCustomerActionStateBTDecorator(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ActionStates = {};
	NodeName = "Is Customer Action State";
}

bool UMS_IsCustomerActionStateBTDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory) const
{
	const TObjectPtr<UBlackboardComponent> BlackboardComp = Cast<UBlackboardComponent>(OwnerComp.GetBlackboardComponent());
	if(!BlackboardComp)
	{
		return EBTNodeResult::Type::Failed;
	}

	const EMS_CustomerActionState CurrentActionState = static_cast<EMS_CustomerActionState>(BlackboardComp->GetValueAsEnum(CustomerBoardKeyName::CustomerActionState));
	return ActionStates.Contains(CurrentActionState);
}
