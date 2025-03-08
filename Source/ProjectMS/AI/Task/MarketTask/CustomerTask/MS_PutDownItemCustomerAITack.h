// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Task/MS_AITask.h"
#include "MS_PutDownItemCustomerAITack.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_PutDownItemCustomerAITack : public UMS_AITask
{
	GENERATED_BODY()
	
public:
	UMS_PutDownItemCustomerAITack(const FObjectInitializer& ObjectInitializer);
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	TWeakObjectPtr<class UMS_CounterUnit> CounterUnit;
	
	float PutDownProcessTime = 0.f;
	float PutDownTime = 0.f;
};
