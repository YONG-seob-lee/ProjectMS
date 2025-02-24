#include "MS_StaffTakeInAITask.h"

UMS_StaffTakeInAITask::UMS_StaffTakeInAITask(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Staff Take In";
	bNotifyTick = false;
}

EBTNodeResult::Type UMS_StaffTakeInAITask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
