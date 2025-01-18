// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "MS_AbilityElementData.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_AbilityElementData : public UObject
{
	GENERATED_BODY()
public:
	FORCEINLINE void SetAbilityName(FString aAbilityName) { AbilityName = aAbilityName; }
	FORCEINLINE void SetAbilityLevel(int32 aAbilityLevel) { AbilityLevel = aAbilityLevel; }

	FORCEINLINE FString GetAbilityName() const { return AbilityName; }
	FORCEINLINE int32 GetAbilityLevel() const { return AbilityLevel; }
	
private:
	FString AbilityName = FString();
	int32 AbilityLevel = 0;
};
