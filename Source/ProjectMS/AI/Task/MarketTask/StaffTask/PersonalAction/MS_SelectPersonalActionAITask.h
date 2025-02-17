// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Task/MS_AITask.h"
#include "MS_SelectPersonalActionAITask.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_SelectPersonalActionAITask : public UMS_AITask
{
	GENERATED_BODY()

public:
	UMS_SelectPersonalActionAITask(const FObjectInitializer& ObjectInitializer);
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
