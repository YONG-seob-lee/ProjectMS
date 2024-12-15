#pragma once

#include "CoreMinimal.h"
#include "AI/AIController/BehaviorTree/BehaviorTreeTask/MS_BehaviorTreeTask.h"
#include "MS_PrintTextTask.generated.h"

UCLASS() class PROJECTMS_API UMS_PrintTextTask : public UMS_BehaviorTreeTask
{
	GENERATED_BODY()

public:
	UMS_PrintTextTask();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual void OnMessage(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, FName Message, int32 RequestID, bool bSuccess) override;
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;

	// Property
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FString StringToPrint = {};

	FTimerHandle TimerHandle;
	void StopBehaviorTree(UBehaviorTreeComponent* OwnerComp);
};
