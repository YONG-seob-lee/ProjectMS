#include "AI/AIController/BehaviorTree/BehaviorTreeDecorator/MS_BehaviorTreeDecorator.h"

UMS_BehaviorTreeDecorator::UMS_BehaviorTreeDecorator()
{
	bNotifyBecomeRelevant = true;
	bNotifyCeaseRelevant = true;
	bNotifyActivation = true;
	bNotifyDeactivation = true;
	bNotifyProcessed = true;
}

bool UMS_BehaviorTreeDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool Result = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	return Result;
}

void UMS_BehaviorTreeDecorator::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

}

void UMS_BehaviorTreeDecorator::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnCeaseRelevant(OwnerComp, NodeMemory);

}

void UMS_BehaviorTreeDecorator::OnNodeActivation(FBehaviorTreeSearchData& SearchData)
{
	Super::OnNodeActivation(SearchData);

}

void UMS_BehaviorTreeDecorator::OnNodeDeactivation(FBehaviorTreeSearchData& SearchData, EBTNodeResult::Type NodeResult)
{
	Super::OnNodeDeactivation(SearchData, NodeResult);

}

void UMS_BehaviorTreeDecorator::OnNodeProcessed(FBehaviorTreeSearchData& SearchData, EBTNodeResult::Type& NodeResult)
{
	Super::OnNodeProcessed(SearchData, NodeResult);

}