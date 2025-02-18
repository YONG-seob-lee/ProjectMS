// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_HasStaffActionTargetBTDecorator.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Mode/ModeObject/Container/MS_StaffAction.h"


UMS_HasStaffActionTargetBTDecorator::UMS_HasStaffActionTargetBTDecorator(
	const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Has Staff Action Target";
}

bool UMS_HasStaffActionTargetBTDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory) const
{
	const TObjectPtr<UBlackboardComponent> BlackboardComp = Cast<UBlackboardComponent>(OwnerComp.GetBlackboardComponent());
	if(!BlackboardComp)
	{
		return EBTNodeResult::Type::Failed;
	}

	EMS_StaffActionType SelectedStaffAction = static_cast<EMS_StaffActionType>(BlackboardComp->GetValueAsEnum(StaffBoardKeyName::SelectedStaffAction));
	if (SelectedStaffAction == EMS_StaffActionType::None)
	{
		return EBTNodeResult::Type::Failed;
	}

	return UMS_StaffAction::HasStaffActionTarget(SelectedStaffAction);
}
