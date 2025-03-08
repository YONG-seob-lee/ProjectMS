// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Task/MS_AITask.h"
#include "MS_StaffPaymentWaitingAITask.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_StaffPaymentWaitingAITask : public UMS_AITask
{
	GENERATED_BODY()

public:
	UMS_StaffPaymentWaitingAITask(const FObjectInitializer& ObjectInitializer);
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;
	
private:
	TWeakObjectPtr<class UMS_CounterUnit> CounterUnit;
};
