// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_IsCustomerFinishedPickUp.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "ContentsUtilities/MS_AIDefine.h"

UMS_IsCustomerFinishedPickUp::UMS_IsCustomerFinishedPickUp(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

bool UMS_IsCustomerFinishedPickUp::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const TObjectPtr<UBlackboardComponent> BlackboardComp = Cast<UBlackboardComponent>(OwnerComp.GetBlackboardComponent());
	if(!BlackboardComp)
	{
		return EBTNodeResult::Type::Failed;
	}

	if(BlackboardComp->GetValueAsBool(CustomerBoardKeyName::CustomerPickUpAllItem) == true)
	{
		return true;
	}
	
	return false;
}
