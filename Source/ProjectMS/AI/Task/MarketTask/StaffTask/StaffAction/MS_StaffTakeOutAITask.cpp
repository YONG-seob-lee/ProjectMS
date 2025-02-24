#include "MS_StaffTakeOutAITask.h"

UMS_StaffTakeOutAITask::UMS_StaffTakeOutAITask(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Staff Take Out";
	bNotifyTick = false;
}

EBTNodeResult::Type UMS_StaffTakeOutAITask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
