// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelSequenceDirector.h"
#include "MS_LevelSequenceDirector.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_LevelSequenceDirector : public ULevelSequenceDirector
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable)
	void OnTrigger();

	UFUNCTION(BlueprintCallable)
	AActor* GetQuarterViewCamera();
};
