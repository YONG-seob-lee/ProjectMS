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

	FORCEINLINE TObjectPtr<class UMS_TableManager> GetTableManager() { return TableManager; }
private:
	void InitManager();

	// Manager Property
	UPROPERTY()
	TObjectPtr<class UMS_TableManager> TableManager = nullptr;
	
	TWeakObjectPtr<class APlayerCameraManager> CameraManager = nullptr;

	UPROPERTY()
	TObjectPtr<class UMS_WidgetManager> WidgetManager = nullptr;
};
