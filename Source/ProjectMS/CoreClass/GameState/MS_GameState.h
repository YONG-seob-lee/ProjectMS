// Fill out your copyright notice in the Description page of Project Settings.

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

protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	
private:
	void RegisterManagement();
	
	UPROPERTY()
	TObjectPtr<class UMS_ManagementBoth> ManagementBoth = nullptr;
};
