// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/AIController/MS_AIController.h"
#include "MS_OutsideAIController.generated.h"

UCLASS()
class PROJECTMS_API AMS_OutsideAIController : public AMS_AIController
{
	GENERATED_BODY()

public:
	AMS_OutsideAIController();
	
	virtual void Initialize() override;
	virtual void PostInitializeComponents() override;
	virtual void OnPossess(APawn* aInPawn) override;
	virtual void OnUnPossess() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type aEndPlayReason) override;
	
private:	
	UPROPERTY()
	TObjectPtr<class UBehaviorTree> OutsideBehaviorTree = nullptr;

	UPROPERTY()
	TObjectPtr<class UBlackboardData> OutsideBlackboardData = nullptr;
};
