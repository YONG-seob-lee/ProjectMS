// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_HasPersonalActionBTDecorator.h"

#include "AI/AIController/StaffAIController/MS_StaffAIController.h"
#include "Character/AICharacter/StaffAICharacter/MS_StaffAICharacter.h"
#include "Units/MS_StaffAIUnit.h"


UMS_HasPersonalActionBTDecorator::UMS_HasPersonalActionBTDecorator(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Has Personal Action";
}

bool UMS_HasPersonalActionBTDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const TObjectPtr<AMS_StaffAIController> AIController = Cast<AMS_StaffAIController>(OwnerComp.GetAIOwner());
	if(!AIController)
	{
		return false;
	}

	const TObjectPtr<AMS_StaffAICharacter> AICharacter = Cast<AMS_StaffAICharacter>(AIController->GetCharacter());
	if(!AICharacter)
	{
		return false;
	}

	const TObjectPtr<UMS_StaffAIUnit> AIUnit = Cast<UMS_StaffAIUnit>(AICharacter->GetOwnerUnitBase());
	if(!AIUnit)
	{
		return false;
	}

	return AIUnit->GetPersonalActionNum() > 0;
}
