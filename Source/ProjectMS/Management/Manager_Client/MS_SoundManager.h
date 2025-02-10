// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_ManagerBase.h"
#include "MS_SoundManager.generated.h"

UENUM(BlueprintType) enum class EMS_SoundClassType : uint8
{
	Undefined		UMETA(DisplayName = "Undefined"),
	Master			UMETA(DisplayName = "Master"),
	Music			UMETA(DisplayName = "Music"),
	Ambient			UMETA(DisplayName = "Ambient"),
	Voice			UMETA(DisplayName = "Voice"), 
	UserInterface	UMETA(DisplayName = "UserInterface"),
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
	
	float GetSoundVolume(EMS_SoundClassType aSoundClassType) const;
	float GetDefaultVolume(EMS_SoundClassType aSoundClassType);
	void GetAllDefaultVolume(TMap<int32, float>& aDefaultSoundVolume);

private:
	UPROPERTY(EditAnywhere) TObjectPtr<class USoundMix> SoundMix = nullptr;


	
public:
	static UMS_SoundManager* GetInstance();
	inline static TObjectPtr<UMS_SoundManager> SoundManager = nullptr;
	
#define gSoundMng (*UMS_SoundManager::GetInstance())
};
