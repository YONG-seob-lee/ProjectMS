#include "AI/AIController/BehaviorTree/BehaviorTreeDecorator/MS_BehaviorTreeDecorator.h"

UMS_BehaviorTreeDecorator::UMS_BehaviorTreeDecorator()
{
	bNotifyBecomeRelevant = true;
	bNotifyCeaseRelevant = true;
	bNotifyActivation = true;
	bNotifyDeactivation = true;
	bNotifyProcessed = true;
}

bool UMS_BehaviorTreeDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory) const
{
	bool Result = Super::CalculateRawConditionValue(aOwnerComp, aNodeMemory);

	return Result;
}

void UMS_BehaviorTreeDecorator::OnBecomeRelevant(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory)
{
	Super::OnBecomeRelevant(aOwnerComp, aNodeMemory);

}

void UMS_BehaviorTreeDecorator::OnCeaseRelevant(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory)
{
	Super::OnCeaseRelevant(aOwnerComp, aNodeMemory);

}

void UMS_BehaviorTreeDecorator::OnNodeActivation(FBehaviorTreeSearchData& aSearchData)
{
	Super::OnNodeActivation(aSearchData);

}

void UMS_BehaviorTreeDecorator::OnNodeDeactivation(FBehaviorTreeSearchData& aSearchData, EBTNodeResult::Type aNodeResult)
{
	Super::OnNodeDeactivation(aSearchData, aNodeResult);

}

void UMS_BehaviorTreeDecorator::OnNodeProcessed(FBehaviorTreeSearchData& aSearchData, EBTNodeResult::Type& aNodeResult)
{
	Super::OnNodeProcessed(aSearchData, aNodeResult);

}