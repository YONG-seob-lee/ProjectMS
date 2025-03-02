// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Task/MS_AITask.h"
#include "MS_GotoHomeAITask.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_GotoHomeAITask : public UMS_AITask
{
	GENERATED_BODY()
	UMS_GotoHomeAITask(const FObjectInitializer& ObjectInitializer);
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
	
	void StaffTickTask(UBehaviorTreeComponent& OwnerComp, const TObjectPtr<class AMS_StaffAIController> AIController) const;
	void CustomerTickTask(UBehaviorTreeComponent& OwnerComp, const TObjectPtr<class AMS_CustomerAIController> AIController) const;
};
