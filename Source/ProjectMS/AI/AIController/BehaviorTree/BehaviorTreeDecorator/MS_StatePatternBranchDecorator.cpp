#include "AI/AIController/BehaviorTree/BehaviorTreeDecorator/MS_StatePatternBranchDecorator.h"

#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Enum.h"

UMS_StatePatternBranchDecorator::UMS_StatePatternBranchDecorator()
{
	NodeName = TEXT("State Branch");
}


bool UMS_StatePatternBranchDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory) const
{
	bool Result = Super::CalculateRawConditionValue(aOwnerComp, aNodeMemory);
	return Result;
}

void UMS_StatePatternBranchDecorator::OnBecomeRelevant(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory)
{
	Super::OnBecomeRelevant(aOwnerComp, aNodeMemory);

}

void UMS_StatePatternBranchDecorator::OnCeaseRelevant(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory)
{
	Super::OnCeaseRelevant(aOwnerComp, aNodeMemory);

}

void UMS_StatePatternBranchDecorator::OnNodeActivation(FBehaviorTreeSearchData& aSearchData)
{
	Super::OnNodeActivation(aSearchData);

}

void UMS_StatePatternBranchDecorator::OnNodeDeactivation(FBehaviorTreeSearchData& aSearchData, EBTNodeResult::Type aNodeResult)
{
	Super::OnNodeDeactivation(aSearchData, aNodeResult);

}

void UMS_StatePatternBranchDecorator::OnNodeProcessed(FBehaviorTreeSearchData& aSearchData, EBTNodeResult::Type& aNodeResult)
{
	Super::OnNodeProcessed(aSearchData, aNodeResult);

}

#if WITH_EDITOR
FString UMS_StatePatternBranchDecorator::GetStaticDescription() const
{
	Super::GetStaticDescription();
}

void UMS_StatePatternBranchDecorator::PostEditChangeProperty(FPropertyChangedEvent& aPropertyChangedEvent)
{
    Super::PostEditChangeProperty(aPropertyChangedEvent);
}
#endif