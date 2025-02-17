// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "Manager_Client/MS_SoundManager.h"
#include "Table/Caches/MS_TutorialCacheTable.h"
#include "MS_GameUserSettings.generated.h"

UENUM()
enum class EMS_TiltType
{
	Default,
	VeryVeryLow,
	VeryLow,
	Low,
	High,
	VeryHigh,
	VeryVeryHigh
};
/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_GameUserSettings : public UGameUserSettings
{
	GENERATED_BODY()
public:
	UMS_GameUserSettings();
	
	void UpdateDefaultSoundVolume(EMS_SoundClassType aSoundType, float aVolume);
	void GetDefaultSoundVolume(TMap<EMS_SoundClassType, float>& aDefaultSoundVolume) const;

	void UpdateTiltType(EMS_TiltType aTilt);
	FORCEINLINE EMS_TiltType GetQuarterViewCameraTiltType() const { return QuarterViewCameraTilt; }

	// Process Tutorial
	void ResetProcessTutorial();
	void AllSkipProcessTutorial();
	bool IsAllProcessTutorialFinished() const;
	bool IsTutorialFinished(EMS_TutorialType aTutorialKey);

	FORCEINLINE void SetIsPlaySequence(bool bNewPlaySequence) { bPlaySequence = bNewPlaySequence; }
	FORCEINLINE bool IsPlaySequence() const { return bPlaySequence; }

private:
	UPROPERTY(config)
	TMap<EMS_SoundClassType, float> DefaultSoundVolume;

	UPROPERTY(config)
	EMS_TiltType QuarterViewCameraTilt = EMS_TiltType::Default;

	UPROPERTY(config)
	TArray<EMS_TutorialType> ProcessTutorial;

	UPROPERTY(config)
	bool bPlaySequence = true;
};
