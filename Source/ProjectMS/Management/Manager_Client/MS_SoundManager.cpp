// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_SoundManager.h"

#include "MS_Define.h"
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
	// 	const FSoundClassAdjuster SoundClassAdjuster = SoundMix->SoundClassEffects[0];
	// 	USoundClass* MasterSoundClass = SoundClassAdjuster.SoundClassObject;
	// 	MasterSoundClass->Properties.Volume = 1.f;
	//
	// 	for(const auto& ChildSoundClass : MasterSoundClass->ChildClasses)
	// 	{
	// 		ChildSoundClass->Properties.Volume = 1.f;
	// 	}
	// }
}

void UMS_SoundManager::AdjustSoundVolume(EMS_SoundClassType aSoundClassType, float aSoundVolume)
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
			MasterSoundClass->Properties.Volume = aSoundVolume;
		}
		else
		{
			if(MasterSoundClass->ChildClasses.IsValidIndex(static_cast<int32>(aSoundClassType) - 2))
			{
				MasterSoundClass->ChildClasses[static_cast<int32>(aSoundClassType) - 2]->Properties.Volume = aSoundVolume;
			}
		}
	}
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

UMS_SoundManager* UMS_SoundManager::GetInstance()
{
	return SoundManager;
}
