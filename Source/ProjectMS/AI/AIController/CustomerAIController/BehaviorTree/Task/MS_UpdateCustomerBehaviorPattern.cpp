#include "AI/AIController/CustomerAIController/BehaviorTree/Task/MS_UpdateCustomerBehaviorPattern.h"

UMS_UpdateCustomerBehaviorPattern::UMS_UpdateCustomerBehaviorPattern()
{
}

void UMS_UpdateCustomerBehaviorPattern::PostEditChangeProperty(FPropertyChangedEvent& aPropertyChangedEvent)
{
	Super::PostEditChangeProperty(aPropertyChangedEvent);

	FName ChangedMemberPropertyName = (aPropertyChangedEvent.MemberProperty != nullptr ? aPropertyChangedEvent.MemberProperty->GetFName() : NAME_None);

	if (ChangedMemberPropertyName == FName(TEXT("ConditionCustomerObservePattern")))
	{
		NodeName = FString::Printf(TEXT("Update Customer Observe Pattern: %s"), *StaticEnum<EMS_CustomerObservePattern>()->GetNameStringByValue(static_cast<int64>(ConditionCustomerObservePattern)));
	}
	else if (ChangedMemberPropertyName == FName(TEXT("ConditionCustomerOperatePattern")))
	{
		NodeName = FString::Printf(TEXT("Update Customer Operate Pattern: %s"), *StaticEnum<EMS_CustomerOperatePattern>()->GetNameStringByValue(static_cast<int64>(ConditionCustomerOperatePattern)));
	}
	else if (ChangedMemberPropertyName == FName(TEXT("ConditionCustomerInteractPattern")))
	{
		NodeName = FString::Printf(TEXT("Update Customer Interact Pattern: %s"), *StaticEnum<EMS_CustomerInteractPattern>()->GetNameStringByValue(static_cast<int64>(ConditionCustomerInteractPattern)));
	}
	else if (ChangedMemberPropertyName == FName(TEXT("ConditionCustomerIdlePattern")))
	{
		NodeName = FString::Printf(TEXT("Update Customer Idle Pattern: %s"), *StaticEnum<EMS_CustomerIdlePattern>()->GetNameStringByValue(static_cast<int64>(ConditionCustomerIdlePattern)));
	}
}

EBTNodeResult::Type UMS_UpdateCustomerBehaviorPattern::ExecuteTask(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(aOwnerComp, aNodeMemory);
	aOwnerComp.GetBlackboardComponent()->SetValueAsEnum(FName(TEXT("CustomerObservePattern")), static_cast<uint8>(ConditionCustomerObservePattern));
	aOwnerComp.GetBlackboardComponent()->SetValueAsEnum(FName(TEXT("CustomerOperatePattern")), static_cast<uint8>(ConditionCustomerOperatePattern));
	aOwnerComp.GetBlackboardComponent()->SetValueAsEnum(FName(TEXT("CustomerInteractPattern")), static_cast<uint8>(ConditionCustomerInteractPattern));
	aOwnerComp.GetBlackboardComponent()->SetValueAsEnum(FName(TEXT("CustomerIdlePattern")), static_cast<uint8>(ConditionCustomerIdlePattern));
	Result = EBTNodeResult::Succeeded;
	return Result;
}
