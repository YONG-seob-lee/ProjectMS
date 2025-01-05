#include "AI/AIController/StaffAIController/BehaviorTree/Task/MS_UpdateStaffBehaviorPattern.h"

UMS_UpdateStaffBehaviorPattern::UMS_UpdateStaffBehaviorPattern()
{
	NodeName = FString(TEXT("Update Staff Behavior Pattern"));
}

void UMS_UpdateStaffBehaviorPattern::PostEditChangeProperty(FPropertyChangedEvent& aPropertyChangedEvent)
{
	Super::PostEditChangeProperty(aPropertyChangedEvent);

	FName ChangedMemberPropertyName = (aPropertyChangedEvent.MemberProperty != nullptr ? aPropertyChangedEvent.MemberProperty->GetFName() : NAME_None);

	if (ChangedMemberPropertyName == FName(TEXT("ConditionStaffObservePattern")))
	{
		NodeName = FString::Printf(TEXT("Update Staff Observe Pattern: %s"), *StaticEnum<EMS_StaffObservePattern>()->GetNameStringByValue(static_cast<int64>(ConditionStaffObservePattern)));
	}
	else if (ChangedMemberPropertyName == FName(TEXT("ConditionStaffOperatePattern")))
	{
		NodeName = FString::Printf(TEXT("Update Staff Operate Pattern: %s"), *StaticEnum<EMS_StaffOperatePattern>()->GetNameStringByValue(static_cast<int64>(ConditionStaffOperatePattern)));
	}
	else if (ChangedMemberPropertyName == FName(TEXT("ConditionStaffInteractPattern")))
	{
		NodeName = FString::Printf(TEXT("Update Staff Interact Pattern: %s"), *StaticEnum<EMS_StaffInteractPattern>()->GetNameStringByValue(static_cast<int64>(ConditionStaffInteractPattern)));
	}
	else if (ChangedMemberPropertyName == FName(TEXT("ConditionStaffIdlePattern")))
	{
		NodeName = FString::Printf(TEXT("Update Staff Idle Pattern: %s"), *StaticEnum<EMS_StaffIdlePattern>()->GetNameStringByValue(static_cast<int64>(ConditionStaffIdlePattern)));
	}
}

EBTNodeResult::Type UMS_UpdateStaffBehaviorPattern::ExecuteTask(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(aOwnerComp, aNodeMemory);
	aOwnerComp.GetBlackboardComponent()->SetValueAsEnum(FName(TEXT("StaffObservePattern")), static_cast<uint8>(ConditionStaffObservePattern));
	aOwnerComp.GetBlackboardComponent()->SetValueAsEnum(FName(TEXT("StaffOperatePattern")), static_cast<uint8>(ConditionStaffOperatePattern));
	aOwnerComp.GetBlackboardComponent()->SetValueAsEnum(FName(TEXT("StaffInteractPattern")), static_cast<uint8>(ConditionStaffInteractPattern));
	aOwnerComp.GetBlackboardComponent()->SetValueAsEnum(FName(TEXT("StaffIdlePattern")), static_cast<uint8>(ConditionStaffIdlePattern));

	Result = EBTNodeResult::Succeeded;
	return Result;
}
