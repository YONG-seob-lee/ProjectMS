#pragma once

#include "CoreMinimal.h"
#include "AI/AIController/BehaviorTree/Task/MS_BehaviorTreeTask.h"
#include "MS_CheckAllStorageStockTask.generated.h"

UCLASS() class PROJECTMS_API UMS_CheckAllStorageStockTask : public UMS_BehaviorTreeTask
{
	GENERATED_BODY()
	
public:
	UMS_CheckAllStorageStockTask();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory) override;

};
