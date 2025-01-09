#pragma once

#include "CoreMinimal.h"
#include "AI/AIController/BehaviorTree/Task/MS_BehaviorTreeTask.h"
#include "MS_CheckStorageStockTask.generated.h"

UCLASS() class PROJECTMS_API UMS_CheckStorageStockTask : public UMS_BehaviorTreeTask
{
	GENERATED_BODY()

public:
	UMS_CheckStorageStockTask();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory, float aDeltaSeconds) override;
};
