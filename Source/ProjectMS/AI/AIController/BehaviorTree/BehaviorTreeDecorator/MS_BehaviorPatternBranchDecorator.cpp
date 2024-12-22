#include "AI/AIController/BehaviorTree/BehaviorTreeDecorator/MS_BehaviorPatternBranchDecorator.h"

#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Enum.h"

UMS_BehaviorPatternBranchDecorator::UMS_BehaviorPatternBranchDecorator()
{
	NodeName = TEXT("AI Behavior Pattern Branch: Undefined");
}

#if WITH_EDITOR
void UMS_BehaviorPatternBranchDecorator::PostEditChangeProperty(FPropertyChangedEvent& aPropertyChangedEvent)
{
	Super::PostEditChangeProperty(aPropertyChangedEvent);

	FName ChangedMemberPropertyName = (aPropertyChangedEvent.MemberProperty != nullptr ? aPropertyChangedEvent.MemberProperty->GetFName() : NAME_None);
	if (ChangedMemberPropertyName == FName(TEXT("ConditionAIBehaviorPattern")))
	{
		NodeName = FString::Printf(TEXT("AI Behavior Pattern Branch: %s"), *StaticEnum<EMS_AIBehaviorPattern>()->GetNameStringByValue(static_cast<int64>(ConditionAIBehaviorPattern)));
	}
}

FString UMS_BehaviorPatternBranchDecorator::GetStaticDescription() const
{
	Super::GetStaticDescription();

	return FString();
}
#endif

bool UMS_BehaviorPatternBranchDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory) const
{
	bool Result = Super::CalculateRawConditionValue(aOwnerComp, aNodeMemory);

	int AIBehaviorPattern = aOwnerComp.GetBlackboardComponent()->GetValueAsEnum(FName(TEXT("AIBehaviorPattern")));
	
	if (AIBehaviorPattern == static_cast<uint8>(ConditionAIBehaviorPattern))
	{
		Result = true;
	}
	else
	{
		Result = false;
	}

	return Result;
}

