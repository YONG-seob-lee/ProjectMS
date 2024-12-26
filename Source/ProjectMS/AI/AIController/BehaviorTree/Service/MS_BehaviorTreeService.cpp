#include "AI/AIController/BehaviorTree/Service/MS_BehaviorTreeService.h"

UMS_BehaviorTreeService::UMS_BehaviorTreeService()
{
	bCallTickOnSearchStart = false;
	bNotifyBecomeRelevant = true;
	bNotifyCeaseRelevant = true;
	bRestartTimerOnEachActivation = false;
	bNotifyOnSearch = true;
}

void UMS_BehaviorTreeService::OnSearchStart(FBehaviorTreeSearchData& SearchData)
{
	Super::OnSearchStart(SearchData);
}

void UMS_BehaviorTreeService::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
}

void UMS_BehaviorTreeService::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnCeaseRelevant(OwnerComp, NodeMemory);
}

void UMS_BehaviorTreeService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
