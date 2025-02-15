// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_LevelModeHelper.h"
#include "MS_LevelModeHelper_Market.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_LevelModeHelper_Market : public UMS_LevelModeHelper
{
	GENERATED_BODY()

public:
	UMS_LevelModeHelper_Market();
	
	virtual void RegisterMode() override;
	virtual void UnregisterMode() override;
	
	virtual void BeginDefaultMode() override;
};
