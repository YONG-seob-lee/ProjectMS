// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_IsCustomerActionProcessBTDecorator.h"

#include "BehaviorTree/BlackboardComponent.h"

UMS_IsCustomerActionProcessBTDecorator::UMS_IsCustomerActionProcessBTDecorator(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ActionProcesses = {};
	NodeName = "Is Customer Action Process";
}

bool UMS_IsCustomerActionProcessBTDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory) const
{
	const TObjectPtr<UBlackboardComponent> BlackboardComp = Cast<UBlackboardComponent>(OwnerComp.GetBlackboardComponent());
	if(!BlackboardComp)
	{
		return EBTNodeResult::Type::Failed;
	}

	const EMS_CustomerActionState CurrentActionProcess = static_cast<EMS_CustomerActionState>(BlackboardComp->GetValueAsEnum(StaffBoardKeyName::CurrentActionProcess));
	return ActionProcesses.Contains(CurrentActionProcess);
}
