// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_SoundManager.h"

#include "MS_Define.h"
#include "Components/AudioComponent.h"
#include "GameUserSettings/MS_GameUserSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundClass.h"
#include "Sound/SoundMix.h"

UMS_SoundManager::UMS_SoundManager()
{
	SoundManager = this;
	
	const ConstructorHelpers::FObjectFinder<USoundMix> SoundMixObjectFinder(TEXT("/Game/Sound/SoundMix/BP_SoundMix"));
	if(SoundMixObjectFinder.Succeeded() == false)
	{
		MS_ERROR(TEXT("Warning!"));
	}

	SoundMix = SoundMixObjectFinder.Object;
	
	// if(SoundMix->SoundClassEffects.IsValidIndex(0))
	// {
	// 	const float* DefaultMasterVolume = DefaultSoundVolume.Find(EMS_SoundClassType::Master);
	// 	if(DefaultMasterVolume == nullptr)
	// 	{
	// 		return;
	// 	}
	// 	
	// 	const FSoundClassAdjuster SoundClassAdjuster = SoundMix->SoundClassEffects[0];
	// 	USoundClass* MasterSoundClass = SoundClassAdjuster.SoundClassObject;
	// 	MasterSoundClass->Properties.Volume = *DefaultMasterVolume;
	//
	// 	for(const auto& ChildSoundClass : MasterSoundClass->ChildClasses)
	// 	{
	// 		ChildSoundClass->Properties.Volume = *DefaultMasterVolume;
	// 	}
	// }
}

void UMS_SoundManager::Initialize()
{
	Super::Initialize();

	const TObjectPtr<UMS_GameUserSettings> GameUserSettings = Cast<UMS_GameUserSettings>(GEngine->GetGameUserSettings());
	if(!GameUserSettings)
	{
		return;
	}
	
	TMap<EMS_SoundClassType, float> DefaultSoundVolume;
	GameUserSettings->GetDefaultSoundVolume(DefaultSoundVolume);
	for(const auto& DefaultVolume : DefaultSoundVolume)
	{
		AdjustSoundVolume(DefaultVolume.Key, DefaultVolume.Value);
	}
}

void UMS_SoundManager::Finalize()
{
	if(const TObjectPtr<UMS_GameUserSettings> GameUserSettings = Cast<UMS_GameUserSettings>(GEngine->GetGameUserSettings()))
	{
		GameUserSettings->ApplySettings(true);
	}
	Super::Finalize();
}

void UMS_SoundManager::AdjustSoundVolume(EMS_SoundClassType aSoundClassType, float aSoundVolume /* = -1.f */)
{
	if(!SoundMix)
	{
		return;
	}

	if(SoundMix->SoundClassEffects.IsValidIndex(0))
	{
		const FSoundClassAdjuster SoundClassAdjuster = SoundMix->SoundClassEffects[0];
		
		USoundClass* MasterSoundClass = SoundClassAdjuster.SoundClassObject;
		if(aSoundClassType == EMS_SoundClassType::Master)
		{
			if(aSoundVolume <= -1.f)
			{
				const float TargetSoundVolume = GetSoundVolume(aSoundClassType);
				
				MasterSoundClass->Properties.Volume = TargetSoundVolume; 				
			}
			else
			{
				MasterSoundClass->Properties.Volume = aSoundVolume;
			}
		}
		else
		{
			if(MasterSoundClass->ChildClasses.IsValidIndex(static_cast<int32>(aSoundClassType) - 2))
			{
				if(aSoundVolume <= -1.f)
				{
					const float TargetSoundVolume =GetSoundVolume(aSoundClassType);
					MasterSoundClass->ChildClasses[static_cast<int32>(aSoundClassType) - 2]->Properties.Volume = TargetSoundVolume; 				
				}
				else
				{
					MasterSoundClass->ChildClasses[static_cast<int32>(aSoundClassType) - 2]->Properties.Volume = aSoundVolume;
				}
			}
		}
	}
}

void UMS_SoundManager::PlaySound(EMS_SoundClassType aSoundClassType, EMS_LevelType aLevelType)
{
	TObjectPtr<USoundWave> MarketBGM = nullptr;
	
	switch(aSoundClassType)
	{
	case EMS_SoundClassType::BGM:
		{
			if(BGMComponent)
			{
				BGMComponent->Stop();
				MS_DeleteObject(BGMComponent);
				BGMComponent = nullptr;
			}
			
			switch(aLevelType)
			{
			case EMS_LevelType::Stage01:
			case EMS_LevelType::Stage02:
			case EMS_LevelType::Stage03:
			case EMS_LevelType::LobbyLevel:
				{
					MarketBGM = Cast<USoundWave>(StaticLoadObject(USoundWave::StaticClass(), nullptr, TEXT("/Game/Sound/SoundWave/LobbyBGM.LobbyBGM")));
					break;
				}
			case EMS_LevelType::MarketLevel:
				{
					MarketBGM = Cast<USoundWave>(StaticLoadObject(USoundWave::StaticClass(), nullptr, TEXT("/Game/Sound/SoundWave/MarketBGM.MarketBGM")));
					break;
				}
			default:
					break;
			}
			break;
		}
	default:
		break;
	}
	BGMComponent = UGameplayStatics::SpawnSound2D(GetWorld(), MarketBGM);
}

float UMS_SoundManager::GetSoundVolume(EMS_SoundClassType aSoundClassType) const
{
	if(!SoundMix)
	{
		return -1.f;
	}

	if(SoundMix->SoundClassEffects.IsValidIndex(0))
	{
		const FSoundClassAdjuster SoundClassAdjuster = SoundMix->SoundClassEffects[0];
		USoundClass* MasterSoundClass = SoundClassAdjuster.SoundClassObject;
		if(aSoundClassType == EMS_SoundClassType::Master)
		{
			return MasterSoundClass->Properties.Volume;
		}
		
		if(MasterSoundClass->ChildClasses.IsValidIndex(static_cast<int32>(aSoundClassType) - 2))
		{
			return MasterSoundClass->ChildClasses[static_cast<int32>(aSoundClassType) - 2]->Properties.Volume;
		}
	}

	return -1.f;
}

float UMS_SoundManager::GetDefaultVolume(EMS_SoundClassType aSoundClassType)
{
	const TObjectPtr<UMS_GameUserSettings> GameUserSettings = Cast<UMS_GameUserSettings>(GEngine->GetGameUserSettings());
	if(!GameUserSettings)
	{
		return -1.f;
	}
	
	TMap<EMS_SoundClassType, float> DefaultSoundVolume;
	GameUserSettings->GetDefaultSoundVolume(DefaultSoundVolume);
	
	if(const float* Volume = DefaultSoundVolume.Find(aSoundClassType))
	{
		return *Volume;
	}

	return -1.f;
}

void UMS_SoundManager::GetAllDefaultVolume(TMap<int32, float>& aDefaultSoundVolume)
{
	aDefaultSoundVolume.Empty();
	
	const TObjectPtr<UMS_GameUserSettings> GameUserSettings = Cast<UMS_GameUserSettings>(GEngine->GetGameUserSettings());
	if(!GameUserSettings)
	{
		return;
	}
	
	TMap<EMS_SoundClassType, float> DefaultSoundVolume;
	GameUserSettings->GetDefaultSoundVolume(DefaultSoundVolume);
	
	for(const auto& Volume : DefaultSoundVolume)
	{
		aDefaultSoundVolume.Emplace(static_cast<int32>(Volume.Key), Volume.Value);
	}
}

UMS_SoundManager* UMS_SoundManager::GetInstance()
{
	return SoundManager;
}
