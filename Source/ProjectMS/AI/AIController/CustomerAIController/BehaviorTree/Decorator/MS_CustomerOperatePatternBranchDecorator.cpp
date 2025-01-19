#include "AI/AIController/CustomerAIController/BehaviorTree/Decorator/MS_CustomerOperatePatternBranchDecorator.h"

UMS_CustomerOperatePatternBranchDecorator::UMS_CustomerOperatePatternBranchDecorator()
{
	NodeName = TEXT("Customer Operate Pattern Branch: Undefined");
}

#if WITH_EDITOR
void UMS_CustomerOperatePatternBranchDecorator::PostEditChangeProperty(FPropertyChangedEvent& aPropertyChangedEvent)
{
	Super::PostEditChangeProperty(aPropertyChangedEvent);

	FName ChangedMemberPropertyName = (aPropertyChangedEvent.MemberProperty != nullptr ? aPropertyChangedEvent.MemberProperty->GetFName() : NAME_None);
	if (ChangedMemberPropertyName == FName(TEXT("ConditionCustomerOperatePattern")))
	{
		NodeName = FString::Printf(TEXT("Customer Operate Pattern Branch: %s"), *StaticEnum<EMS_CustomerOperatePattern>()->GetNameStringByValue(static_cast<int64>(ConditionCustomerOperatePattern)));
	}
}

FString UMS_CustomerOperatePatternBranchDecorator::GetStaticDescription() const
{
	return FString();
}
#endif

bool UMS_CustomerOperatePatternBranchDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory) const
{
	bool Result = Super::CalculateRawConditionValue(aOwnerComp, aNodeMemory);

	int AIBehaviorPattern = aOwnerComp.GetBlackboardComponent()->GetValueAsEnum(FName(TEXT("CustomerOperatePattern")));

	if (AIBehaviorPattern == static_cast<uint8>(ConditionCustomerOperatePattern))
	{
		Result = true;
	}
	else
	{
		Result = false;
	}

	return Result;
}
