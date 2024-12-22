#include "AI/AIController/StaffAIController/BehaviorTree/Decorator/MS_StaffObservePatternBranchDecorator.h"

UMS_StaffObservePatternBranchDecorator::UMS_StaffObservePatternBranchDecorator()
{
	NodeName = TEXT("Staff Observe Pattern Branch: Undefined");
}

#if WITH_EDITOR
void UMS_StaffObservePatternBranchDecorator::PostEditChangeProperty(FPropertyChangedEvent& aPropertyChangedEvent)
{
	Super::PostEditChangeProperty(aPropertyChangedEvent);

	FName ChangedMemberPropertyName = (aPropertyChangedEvent.MemberProperty != nullptr ? aPropertyChangedEvent.MemberProperty->GetFName() : NAME_None);
	if (ChangedMemberPropertyName == FName(TEXT("ConditionStaffObservePattern")))
	{
		NodeName = FString::Printf(TEXT("Staff Observe Pattern Branch: %s"), *StaticEnum<EMS_StaffObservePattern>()->GetNameStringByValue(static_cast<int64>(ConditionStaffObservePattern)));
	}
}

FString UMS_StaffObservePatternBranchDecorator::GetStaticDescription() const
{
	return Super::GetStaticDescription();
}
#endif

bool UMS_StaffObservePatternBranchDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory) const
{
	bool Result = Super::CalculateRawConditionValue(aOwnerComp, aNodeMemory);

	int AIBehaviorPattern = aOwnerComp.GetBlackboardComponent()->GetValueAsEnum(FName(TEXT("StaffObservePattern")));

	if (AIBehaviorPattern == static_cast<uint8>(ConditionStaffObservePattern))
	{
		Result = true;
	}
	else
	{
		Result = false;
	}

	return Result;
}
