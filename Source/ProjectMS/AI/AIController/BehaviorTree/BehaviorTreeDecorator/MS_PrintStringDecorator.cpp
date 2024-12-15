#include "AI/AIController/BehaviorTree/BehaviorTreeDecorator/MS_PrintStringDecorator.h"

UMS_PrintStringDecorator::UMS_PrintStringDecorator()
{
	NodeName = FString(TEXT("Print String Decorator"));
}

bool UMS_PrintStringDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool Result = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	return Result;
}
void UMS_PrintStringDecorator::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

}
void UMS_PrintStringDecorator::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnCeaseRelevant(OwnerComp, NodeMemory);

}
void UMS_PrintStringDecorator::OnNodeActivation(FBehaviorTreeSearchData& SearchData)
{
	Super::OnNodeActivation(SearchData);

}
void UMS_PrintStringDecorator::OnNodeDeactivation(FBehaviorTreeSearchData& SearchData, EBTNodeResult::Type NodeResult)
{
	Super::OnNodeDeactivation(SearchData, NodeResult);

}
void UMS_PrintStringDecorator::OnNodeProcessed(FBehaviorTreeSearchData& SearchData, EBTNodeResult::Type& NodeResult)
{
	Super::OnNodeProcessed(SearchData, NodeResult);

}