﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Task/MS_AITask.h"
#include "MS_GotoMarketAITask.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_GotoMarketAITask : public UMS_AITask
{
	GENERATED_BODY()
	
	UMS_GotoMarketAITask(const FObjectInitializer& ObjectInitializer);
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
