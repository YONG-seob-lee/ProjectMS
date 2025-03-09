// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Task/MS_AITask.h"
#include "MS_StaffIdleWaitingAITask.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_StaffIdleWaitingAITask : public UMS_AITask
{
	GENERATED_BODY()

public:
	UMS_StaffIdleWaitingAITask(const FObjectInitializer& ObjectInitializer);
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere)
	float MaxIdleTime = 5.f;

	UPROPERTY()
	float RemainIdleTime = 5.f;
};
