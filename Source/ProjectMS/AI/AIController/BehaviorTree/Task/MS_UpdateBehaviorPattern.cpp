#include "AI/AIController/BehaviorTree/Task/MS_UpdateBehaviorPattern.h"

UMS_UpdateBehaviorPattern::UMS_UpdateBehaviorPattern()
{
	NodeName = TEXT("Update AI Behavior Pattern: Undefined");
}

#if WITH_EDITOR
void UMS_UpdateBehaviorPattern::PostEditChangeProperty(FPropertyChangedEvent& aPropertyChangedEvent)
{
	Super::PostEditChangeProperty(aPropertyChangedEvent);

	FName ChangedMemberPropertyName = (aPropertyChangedEvent.MemberProperty != nullptr ? aPropertyChangedEvent.MemberProperty->GetFName() : NAME_None);
	if (ChangedMemberPropertyName == FName(TEXT("ConditionAIBehaviorPattern")))
	{
		NodeName = FString::Printf(TEXT("Update AI Behavior Pattern: %s"), *StaticEnum<EMS_AIBehaviorPattern>()->GetNameStringByValue(static_cast<int64>(ConditionAIBehaviorPattern)));
	}
}
#endif

EBTNodeResult::Type UMS_UpdateBehaviorPattern::ExecuteTask(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(aOwnerComp, aNodeMemory);

	aOwnerComp.GetBlackboardComponent()->SetValueAsEnum(FName(TEXT("AIBehaviorPattern")), static_cast<uint8>(ConditionAIBehaviorPattern));
	UE_LOG(LogTemp, Warning, TEXT("Execute Task"));

	Result = EBTNodeResult::Succeeded;
	return Result;
}