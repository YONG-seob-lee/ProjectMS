// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_HasPersonalActionTargetBTDecorator.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Mode/ModeObject/Container/MS_PersonalAction.h"


UMS_HasPersonalActionTargetBTDecorator::UMS_HasPersonalActionTargetBTDecorator(
	const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Has Personal Action Target";
}

bool UMS_HasPersonalActionTargetBTDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory) const
{
	const TObjectPtr<UBlackboardComponent> BlackboardComp = Cast<UBlackboardComponent>(OwnerComp.GetBlackboardComponent());
	if(!BlackboardComp)
	{
		return EBTNodeResult::Type::Failed;
	}

	EMS_PersonalActionType SelectedPersonalAction = static_cast<EMS_PersonalActionType>(BlackboardComp->GetValueAsEnum(StaffBoardKeyName::SelectedPersonalAction));
	if (SelectedPersonalAction == EMS_PersonalActionType::None)
	{
		return EBTNodeResult::Type::Failed;
	}

	return UMS_PersonalAction::HasPersonalActionTarget(SelectedPersonalAction);
}
