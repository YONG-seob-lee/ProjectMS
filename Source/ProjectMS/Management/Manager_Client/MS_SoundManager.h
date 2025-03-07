// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_ManagerBase.h"
#include "Command/SceneCommand/MS_SceneCommand.h"
#include "MS_SoundManager.generated.h"

UENUM(BlueprintType)
enum class EMS_SoundClassType : uint8
{
	Undefined		UMETA(DisplayName = "Undefined"),
	Master			UMETA(DisplayName = "Master"),
	BGM				UMETA(DisplayName = "BGM"),
	Ambient			UMETA(DisplayName = "Ambient"),
	Voice			UMETA(DisplayName = "Voice"), 
	UserInterface	UMETA(DisplayName = "UserInterface"),
};

UENUM()
enum class EMS_SoundWaveType
{
	None = 0,
	DoorBell,
};
/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_SoundManager : public UMS_ManagerBase
{
	GENERATED_BODY()
public:
	UMS_SoundManager();

	virtual void Initialize() override;
	virtual void Finalize() override;
	
	UFUNCTION(BlueprintCallable)
	void AdjustSoundVolume(EMS_SoundClassType aSoundClassType, float aSoundVolume = -1.f);

	void PlaySound(EMS_SoundClassType aSoundClassType, EMS_LevelType aLevelType);
	void PlaySound(EMS_SoundClassType aSoundClassType, EMS_SoundWaveType aSoundWaveType);
	
	float GetSoundVolume(EMS_SoundClassType aSoundClassType) const;
	float GetDefaultVolume(EMS_SoundClassType aSoundClassType);
	void GetAllDefaultVolume(TMap<int32, float>& aDefaultSoundVolume);

private:
	UPROPERTY(EditAnywhere) TObjectPtr<class USoundMix> SoundMix = nullptr;

	UPROPERTY()
	TObjectPtr<UAudioComponent> BGMComponent = nullptr;

	UPROPERTY()
	TObjectPtr<UAudioComponent> UserInterfaceComponent = nullptr;
	
public:
	static UMS_SoundManager* GetInstance();
	inline static TObjectPtr<UMS_SoundManager> SoundManager = nullptr;
	
#define gSoundMng (*UMS_SoundManager::GetInstance())
};
