﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "MS_GameState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API AMS_GameState : public AGameState
{
	GENERATED_BODY()
	
public:
	AMS_GameState(const FObjectInitializer& aObjectInitializer);

	virtual void PreInitializeComponents() override;
	virtual void PostInitializeComponents() override;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	

private:
	void RegisterManagement();
	void DestroyManagement();
	

private:
	UPROPERTY()
	TObjectPtr<class UMS_ManagementBoth> ManagementBoth = nullptr;
};
