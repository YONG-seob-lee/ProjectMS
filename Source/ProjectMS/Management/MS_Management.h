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

private:
	void InitManager();

	TObjectPtr<class UMS_TableManager> TableManager = nullptr;
	TObjectPtr<class UMS_CameraManager> CameraManager = nullptr;
};
