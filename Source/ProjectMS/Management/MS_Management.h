// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MS_Management.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_Management : public UObject
{
	GENERATED_BODY()
public:
	virtual void Initialize();
	virtual void Finalize();
	virtual void PostInitialize();
	virtual void Tick(float aDeltaTime);

	void InitManager();
	
private:

	// Manager Property
	UPROPERTY()
	TObjectPtr<class UMS_TableManager> TableManager = nullptr;

	UPROPERTY()
	TObjectPtr<class AMS_SceneManager> SceneManager = nullptr;

	UPROPERTY()
	TObjectPtr<class UMS_UnitManager> UnitManager = nullptr;
	
	UPROPERTY()
	TObjectPtr<class UMS_WidgetManager> WidgetManager = nullptr;

	UPROPERTY()
	TObjectPtr<class AMS_PlayerCameraManager> CameraManager = nullptr;

	UPROPERTY()
	TObjectPtr<class UMS_ModeManager> CommandManager = nullptr;
};