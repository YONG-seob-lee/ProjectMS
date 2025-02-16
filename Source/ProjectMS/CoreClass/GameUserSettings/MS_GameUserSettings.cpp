// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_GameUserSettings.h"

#include "MS_Define.h"

UMS_GameUserSettings::UMS_GameUserSettings()
{
	DefaultSoundVolume.Emplace(EMS_SoundClassType::Master, 0.5f);
	DefaultSoundVolume.Emplace(EMS_SoundClassType::Music, 0.5f);
	DefaultSoundVolume.Emplace(EMS_SoundClassType::Ambient, 0.5f);
	DefaultSoundVolume.Emplace(EMS_SoundClassType::Voice, 0.5f);
	DefaultSoundVolume.Emplace(EMS_SoundClassType::UserInterface, 0.5f);
}

void UMS_GameUserSettings::UpdateDefaultSoundVolume(EMS_SoundClassType aSoundType, float aVolume)
{
	DefaultSoundVolume.Emplace(aSoundType, aVolume);
	FString SoundTypeStr = ConvertEnumToString(TEXT("EMS_SoundClassType"), aSoundType);
	MS_LOG(TEXT("UpdateDefaultSoundVolume ( %s ) : %f"), *SoundTypeStr, aVolume);
}

void UMS_GameUserSettings::GetDefaultSoundVolume(TMap<EMS_SoundClassType, float>& aDefaultSoundVolume) const
{
	aDefaultSoundVolume = DefaultSoundVolume;
}

void UMS_GameUserSettings::UpdateTiltType(EMS_TiltType aTilt)
{
	QuarterViewCameraTilt = aTilt;
	const FString CameraTiltType = ConvertEnumToString(TEXT("EMS_TiltType"), QuarterViewCameraTilt);
	MS_LOG(TEXT("UpdateTileType : %s"), *CameraTiltType);
}

void UMS_GameUserSettings::ResetProcessTutorial()
{
	ProcessTutorial.Empty();
}

void UMS_GameUserSettings::AllSkipProcessTutorial()
{
	for(int32 i = static_cast<int32>(EMS_TutorialType::Schedule) ; i <= static_cast<int32>(EMS_TutorialType::ConstructMode); i++)
	{
		ProcessTutorial.Emplace(static_cast<EMS_TutorialType>(i));
	}
}

bool UMS_GameUserSettings::IsAllProcessTutorialFinished() const
{
	int32 FinishedTutorialCount = 0;
	for(int32 i = static_cast<int32>(EMS_TutorialType::Schedule) ; i <= static_cast<int32>(EMS_TutorialType::ConstructMode); i++)
	{
		FinishedTutorialCount++;
	}
	if(ProcessTutorial.Num() == FinishedTutorialCount)
	{
		return true;
	}
	
	return false;
}

bool UMS_GameUserSettings::IsProcessTutorial(EMS_TutorialType aTutorialKey)
{
	if(ProcessTutorial.Contains(aTutorialKey))
	{
		return true;
	}
	
	ProcessTutorial.Emplace(aTutorialKey);
	return false;
}
