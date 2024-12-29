#include "AI/AIController/StaffAIController/BehaviorTree/BehaviorTreeTask/MS_CheckAllStorageStockTask.h"

UMS_CheckAllStorageStockTask::UMS_CheckAllStorageStockTask()
{
	NodeName = FString(TEXT("Check All Storage Stock"));
}

EBTNodeResult::Type UMS_CheckAllStorageStockTask::ExecuteTask(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory)
{
	EBTNodeResult::Type Result = ExecuteTask(aOwnerComp, aNodeMemory);



	return Result;
}
