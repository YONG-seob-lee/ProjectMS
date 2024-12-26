#include "AI/AIController/BehaviorTree/Decorator/MS_PrintStringDecorator.h"

UMS_PrintStringDecorator::UMS_PrintStringDecorator()
{
	NodeName = FString(TEXT("Print String Decorator"));
}


bool UMS_PrintStringDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory) const
{
	bool Result = Super::CalculateRawConditionValue(aOwnerComp, aNodeMemory);

	return Result;
}

void UMS_PrintStringDecorator::OnBecomeRelevant(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory)
{
	Super::OnBecomeRelevant(aOwnerComp, aNodeMemory);

}

void UMS_PrintStringDecorator::OnCeaseRelevant(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory)
{
	Super::OnCeaseRelevant(aOwnerComp, aNodeMemory);

}

void UMS_PrintStringDecorator::OnNodeActivation(FBehaviorTreeSearchData& aSearchData)
{
	Super::OnNodeActivation(aSearchData);

}

void UMS_PrintStringDecorator::OnNodeDeactivation(FBehaviorTreeSearchData& aSearchData, EBTNodeResult::Type aNodeResult)
{
	Super::OnNodeDeactivation(aSearchData, aNodeResult);

}

void UMS_PrintStringDecorator::OnNodeProcessed(FBehaviorTreeSearchData& aSearchData, EBTNodeResult::Type& aNodeResult)
{
	Super::OnNodeProcessed(aSearchData, aNodeResult);

}