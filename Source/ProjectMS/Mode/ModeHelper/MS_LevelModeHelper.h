// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "MS_LevelModeHelper.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_LevelModeHelper : public UObject
{
	GENERATED_BODY()

public:
	UMS_LevelModeHelper();
	
	virtual void Initialize();
	virtual void Finalize();
	
	virtual void RegisterMode();
	virtual void UnregisterMode();
	
	virtual void BeginDefaultMode();
};
