﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Task/MarketTask/MS_MoveToTargetAITask.h"
#include "MS_StaffMoveToRandomTargetAITask.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_StaffMoveToRandomTargetAITask : public UMS_MoveToTargetAITask
{
	GENERATED_BODY()

public:
	UMS_StaffMoveToRandomTargetAITask(const FObjectInitializer& ObjectInitializer);
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
