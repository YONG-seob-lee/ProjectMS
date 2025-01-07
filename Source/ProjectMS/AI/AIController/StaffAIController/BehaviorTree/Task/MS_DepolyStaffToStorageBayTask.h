#pragma once

#include "CoreMinimal.h"
#include "AI/AIController/BehaviorTree/Task/MS_BehaviorTreeTask.h"
#include "MS_DepolyStaffToStorageBayTask.generated.h"

UCLASS() class PROJECTMS_API UMS_DepolyStaffToStorageBayTask : public UMS_BehaviorTreeTask
{
	GENERATED_BODY()
	
public:
	UMS_DepolyStaffToStorageBayTask();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory) override;

	// Property
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FBlackboardKeySelector TargetStorageKey = {};
};
