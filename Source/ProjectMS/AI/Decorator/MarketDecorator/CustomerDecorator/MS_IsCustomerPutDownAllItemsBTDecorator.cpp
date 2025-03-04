// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_IsCustomerPutDownAllItemsBTDecorator.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "ContentsUtilities/MS_AIDefine.h"

UMS_IsCustomerPutDownAllItemsBTDecorator::UMS_IsCustomerPutDownAllItemsBTDecorator(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Is Customer Put Down All Items";
}

bool UMS_IsCustomerPutDownAllItemsBTDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const TObjectPtr<UBlackboardComponent> BlackboardComp = Cast<UBlackboardComponent>(OwnerComp.GetBlackboardComponent());
	if(!BlackboardComp)
	{
		return EBTNodeResult::Type::Failed;
	}

	return BlackboardComp->GetValueAsBool(CustomerBoardKeyName::IsCustomerPutDownAllItems);
}
