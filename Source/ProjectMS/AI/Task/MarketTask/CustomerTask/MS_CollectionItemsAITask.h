// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Task/MS_AITask.h"
#include "Component/Actor/MS_AIParameterComponent.h"
#include "MS_CollectionItemsAITask.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_CollectionItemsAITask : public UMS_AITask
{
	GENERATED_BODY()
	
public:
	UMS_CollectionItemsAITask(const FObjectInitializer& ObjectInitializer);
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	EMS_ChattingType ChattingType = EMS_ChattingType::Undefined;
	float ConsiderTime = 0.f;
	float ConsiderProcessTime = 0.f;
};
