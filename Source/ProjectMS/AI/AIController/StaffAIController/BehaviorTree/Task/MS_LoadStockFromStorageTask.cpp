#include "AI/AIController/StaffAIController/BehaviorTree/Task/MS_LoadStockFromStorageTask.h"

UMS_LoadStockFromStorageTask::UMS_LoadStockFromStorageTask()
{
	NodeName = FString(TEXT("Load Stock From Storage Task"));
}

EBTNodeResult::Type UMS_LoadStockFromStorageTask::ExecuteTask(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(aOwnerComp, aNodeMemory);



	return Result;
}
