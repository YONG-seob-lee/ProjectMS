#pragma once

#include "CoreMinimal.h"
#include "AI/AIController/BehaviorTree/Task/MS_BehaviorTreeTask.h"
#include "Management/Manager_Client/MS_ItemManager.h"
#include "MS_CheckLoadingStorageStockTask.generated.h"

UCLASS() class PROJECTMS_API UMS_CheckLoadingStorageStockTask : public UMS_BehaviorTreeTask
{
	GENERATED_BODY()
	
public:
	UMS_CheckLoadingStorageStockTask();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory, float aDeltaSeconds) override;
};
