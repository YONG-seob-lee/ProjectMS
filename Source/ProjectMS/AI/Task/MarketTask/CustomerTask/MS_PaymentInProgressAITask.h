// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Task/MS_AITask.h"
#include "MS_PaymentInProgressAITask.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_PaymentInProgressAITask : public UMS_AITask
{
	GENERATED_BODY()
	
public:
	UMS_PaymentInProgressAITask(const FObjectInitializer& ObjectInitializer);
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	
private:
	float PaidTime = 0.f;
	float PaidProcessTime = 0.f;
};
