// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_ManagementBase.h"
#include "MS_ManagementClient.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_ManagementClient : public UMS_ManagementBase
{
	GENERATED_BODY()
public:
	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void PostInitialize() override;
	virtual void Tick(float aDeltaTime) override;
	
private:
	UPROPERTY()
	TObjectPtr<class UMS_SceneManager> SceneManager = nullptr;
	
	UPROPERTY()
	TObjectPtr<class UMS_InputManager> InputManager = nullptr;

	UPROPERTY()
	TObjectPtr<class UMS_InteractionManager> InteractionManager = nullptr;

	UPROPERTY()
	TObjectPtr<class UMS_ItemManager> ItemManager = nullptr;
	
	UPROPERTY()
	TObjectPtr<class UMS_WidgetManager> WidgetManager = nullptr;

	UPROPERTY()
	TObjectPtr<class AMS_PlayerCameraManager> CameraManager = nullptr;

	UPROPERTY()
	TObjectPtr<class UMS_ModeManager> ModeManager = nullptr;

	UPROPERTY()
	TObjectPtr<class UMS_ScheduleManager> ScheduleManager = nullptr;
};
