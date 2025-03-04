// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Task/MS_AITask.h"
#include "MS_SetDisplaysAsSearchTargetsAITask.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_SetDisplaysAsSearchTargetsAITask : public UMS_AITask
{
	GENERATED_BODY()

public:
	UMS_SetDisplaysAsSearchTargetsAITask(const FObjectInitializer& ObjectInitializer);
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
