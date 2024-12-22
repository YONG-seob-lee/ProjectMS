#pragma once

#include "CoreMinimal.h"
#include "AI/AIController/BehaviorTree/BehaviorTreeTask/MS_BehaviorTreeTask.h"
#include "MS_PrintTextTask.generated.h"

UCLASS() class PROJECTMS_API UMS_PrintTextTask : public UMS_BehaviorTreeTask
{
	GENERATED_BODY()

public:
	UMS_PrintTextTask();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory) override;
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* aNodeMemory, float aDeltaSeconds) override;
	virtual void OnMessage(UBehaviorTreeComponent& OwnerComp, uint8* aNodeMemory, FName aMessage, int32 aRequestID, bool abSuccess) override;
	virtual void OnTaskFinished(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory, EBTNodeResult::Type aTaskResult) override;

	// Property
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FString StringToPrint = {};
};
