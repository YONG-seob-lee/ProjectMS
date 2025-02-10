// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Manager_Client/MS_SoundManager.h"
#include "MS_SliderSystemElementData.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_SliderSystemElementData : public UObject
{
	GENERATED_BODY()
public:
	FORCEINLINE void SetSettingName(const FString& aName) { SettingName = aName; }
	FORCEINLINE void SetValue(float aValue) { Value = aValue; }
	FORCEINLINE void SetSoundType(EMS_SoundClassType aSoundType) { SoundType = aSoundType; }

	FORCEINLINE FString GetSettingName() { return SettingName; }
	FORCEINLINE float GetValue() const { return Value; }
	FORCEINLINE EMS_SoundClassType GetSoundType() const { return SoundType; }

private:
	FString SettingName = FString();
	float Value = 0.f;
	EMS_SoundClassType SoundType = EMS_SoundClassType::Undefined;
};
