#include "MS_IsStaffActionStateBTDecorator.h"

#include "BehaviorTree/BlackboardComponent.h"


UMS_IsStaffActionStateBTDecorator::UMS_IsStaffActionStateBTDecorator(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ActionStates = {};
	NodeName = "Is Staff Action States";
}

bool UMS_IsStaffActionStateBTDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory) const
{
	const TObjectPtr<UBlackboardComponent> BlackboardComp = Cast<UBlackboardComponent>(OwnerComp.GetBlackboardComponent());
	if(!BlackboardComp)
	{
		return EBTNodeResult::Type::Failed;
	}

	EMS_StaffActionState CurrentActionState = static_cast<EMS_StaffActionState>(BlackboardComp->GetValueAsEnum(StaffBoardKeyName::StaffActionState));
	return ActionStates.Contains(CurrentActionState);
}
