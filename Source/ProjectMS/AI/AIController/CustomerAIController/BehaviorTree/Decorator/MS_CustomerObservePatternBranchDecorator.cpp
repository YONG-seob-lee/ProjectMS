#include "AI/AIController/CustomerAIController/BehaviorTree/Decorator/MS_CustomerObservePatternBranchDecorator.h"

UMS_CustomerObservePatternBranchDecorator::UMS_CustomerObservePatternBranchDecorator()
{
	NodeName = TEXT("Customer Observe Pattern Branch: Undefined");
}

#if WITH_EDITOR
void UMS_CustomerObservePatternBranchDecorator::PostEditChangeProperty(FPropertyChangedEvent& aPropertyChangedEvent)
{
	Super::PostEditChangeProperty(aPropertyChangedEvent);

	FName ChangedMemberPropertyName = (aPropertyChangedEvent.MemberProperty != nullptr ? aPropertyChangedEvent.MemberProperty->GetFName() : NAME_None);
	if (ChangedMemberPropertyName == FName(TEXT("ConditionCustomerObservePattern")))
	{
		NodeName = FString::Printf(TEXT("Customer Observe Pattern Branch: %s"), *StaticEnum<EMS_CustomerObservePattern>()->GetNameStringByValue(static_cast<int64>(ConditionCustomerObservePattern)));
	}
}

FString UMS_CustomerObservePatternBranchDecorator::GetStaticDescription() const
{
	return FString();
}
#endif

bool UMS_CustomerObservePatternBranchDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory) const
{
	bool Result = Super::CalculateRawConditionValue(aOwnerComp, aNodeMemory);

	int AIBehaviorPattern = aOwnerComp.GetBlackboardComponent()->GetValueAsEnum(FName(TEXT("CustomerObservePattern")));

	if (AIBehaviorPattern == static_cast<uint8>(ConditionCustomerObservePattern))
	{
		Result = true;
	}
	else
	{
		Result = false;
	}

	return Result;
}
