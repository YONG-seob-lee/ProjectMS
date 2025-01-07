#pragma once

#include "CoreMinimal.h"
#include "AI/AIController/BehaviorTree/Task/MS_BehaviorTreeTask.h"
#include "MS_SeekUntilAvailableBayTask.generated.h"

UCLASS() class PROJECTMS_API UMS_SeekUntilAvailableBayTask : public UMS_BehaviorTreeTask
{
	GENERATED_BODY()
	
public:
	UMS_SeekUntilAvailableBayTask();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory) override;
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory, float aDeltaSeconds) override;
	virtual void OnMessage(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory, FName aMessage, int32 aRequestID, bool abSuccess) override;
	virtual void OnTaskFinished(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory, EBTNodeResult::Type aTaskResult) override;

	// Property
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FBlackboardKeySelector StorageKey = {};
};
