#include "AI/AIController/BehaviorTree/Task/MS_UpdateBehaviorPattern.h"

UMS_UpdateBehaviorPattern::UMS_UpdateBehaviorPattern()
{
	NodeName = TEXT("Update Behavior Pattern: Undefined");
}

#if WITH_EDITOR
void UMS_UpdateBehaviorPattern::PostEditChangeProperty(FPropertyChangedEvent& aPropertyChangedEvent)
{
	Super::PostEditChangeProperty(aPropertyChangedEvent);


}
#endif

EBTNodeResult::Type UMS_UpdateBehaviorPattern::ExecuteTask(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(aOwnerComp, aNodeMemory);

	return Result;
}