#include "MS_IsStaffActionProcessBTDecorator.h"

#include "BehaviorTree/BlackboardComponent.h"


UMS_IsStaffActionProcessBTDecorator::UMS_IsStaffActionProcessBTDecorator(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ActionProcesses = {};
	NodeName = "Is Staff Action Process";
}

bool UMS_IsStaffActionProcessBTDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory) const
{
	const TObjectPtr<UBlackboardComponent> BlackboardComp = Cast<UBlackboardComponent>(OwnerComp.GetBlackboardComponent());
	if(!BlackboardComp)
	{
		return EBTNodeResult::Type::Failed;
	}

	EMS_StaffActionProcess CurrentActionProcess = static_cast<EMS_StaffActionProcess>(BlackboardComp->GetValueAsEnum(StaffBoardKeyName::CurrentActionProcess));
	return ActionProcesses.Contains(CurrentActionProcess);
}
