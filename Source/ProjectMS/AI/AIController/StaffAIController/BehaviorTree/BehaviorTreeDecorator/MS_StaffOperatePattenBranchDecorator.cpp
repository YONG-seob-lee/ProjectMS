#include "AI/AIController/StaffAIController/BehaviorTree/BehaviorTreeDecorator/MS_StaffOperatePattenBranchDecorator.h"

UMS_StaffOperatePattenBranchDecorator::UMS_StaffOperatePattenBranchDecorator()
{
	NodeName = TEXT("Staff Operate Pattern Branch: Undefined");
}

#if WITH_EDITOR
void UMS_StaffOperatePattenBranchDecorator::PostEditChangeProperty(FPropertyChangedEvent& aPropertyChangedEvent)
{
	Super::PostEditChangeProperty(aPropertyChangedEvent);

	FName ChangedMemberPropertyName = (aPropertyChangedEvent.MemberProperty != nullptr ? aPropertyChangedEvent.MemberProperty->GetFName() : NAME_None);
	if (ChangedMemberPropertyName == FName(TEXT("ConditionStaffOperatePattern")))
	{
		NodeName = FString::Printf(TEXT("Staff Operate Pattern Branch: %s"), *StaticEnum<EMS_StaffOperatePattern>()->GetNameStringByValue(static_cast<int64>(ConditionStaffOperatePattern)));
	}
}

FString UMS_StaffOperatePattenBranchDecorator::GetStaticDescription() const
{
	return Super::GetStaticDescription();
}
#endif

bool UMS_StaffOperatePattenBranchDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory) const
{
	bool Result = Super::CalculateRawConditionValue(aOwnerComp, aNodeMemory);

	int AIBehaviorPattern = aOwnerComp.GetBlackboardComponent()->GetValueAsEnum(FName(TEXT("StaffOperatePattern")));

	if (AIBehaviorPattern == static_cast<uint8>(ConditionStaffOperatePattern))
	{
		Result = true;
	}
	else
	{
		Result = false;
	}

	return Result;
}
