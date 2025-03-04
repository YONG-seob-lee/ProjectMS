// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_SequenceManager.h"

#include "LevelSequence.h"
#include "LevelSequencePlayer.h"
#include "MS_Define.h"
#include "MS_PlayerCameraManager.h"
#include "MS_SceneManager.h"
#include "MS_WidgetManager.h"
#include "Camera/ViewCamera/MS_ViewCamera.h"

UMS_SequenceManager::UMS_SequenceManager()
{
	SequenceManager = this;
}

void UMS_SequenceManager::Initialize()
{
	Super::Initialize();
}

void UMS_SequenceManager::Finalize()
{
	Super::Finalize();
}

void UMS_SequenceManager::PostInitialize()
{
	Super::PostInitialize();
}

void UMS_SequenceManager::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
}

void UMS_SequenceManager::BeginPlay()
{
	Super::BeginPlay();
}

void UMS_SequenceManager::PlaySequence(EMS_SequenceType SequenceType, const FMS_SequencePlayParameter& Parameter)
{
	if(Parameter.bCheckedSequencePlay)
	{
		const TObjectPtr<UMS_GameUserSettings> GameUserSettings = Cast<UMS_GameUserSettings>(GEngine->GetGameUserSettings());
		if(!GameUserSettings)
		{
			return;
		}
		if(GameUserSettings->IsPlaySequence() == false)
		{
			return;
		}	
	}

	const TObjectPtr<ULevelSequence> Sequence = LoadSequence(SequenceType);
	if(!Sequence)
	{
		MS_LOG_VERBOSITY(Error, TEXT("Sequence Is Null. Please Check Sequence Path [ MS_SequenceManager.h Namespace : SequencePath ]"));
		return;
	}

	if (SequenceType == EMS_SequenceType::Entrance || SequenceType == EMS_SequenceType::Truck)
	{
		if (const TObjectPtr<ULevelSequencePlayer> LevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), Sequence, FMovieSceneSequencePlaybackSettings(), SequenceActor))
		{
			bSetBlendCamera = Parameter.bSetBlendCamera; 
			if(Parameter.bSetBlendCamera)
			{
				gCameraMng.SetViewTarget(SequenceActor);
				FVector QuarterCameraLocation;
				FRotator QuarterCameraRotator;
				gCameraMng.GetViewCamera(EMS_ViewCameraType::QuarterView)->GetCameraPosition(QuarterCameraLocation, QuarterCameraRotator);
				SequenceActor->SetActorLocationAndRotation(QuarterCameraLocation, QuarterCameraRotator);
			}
	
			if(Parameter.OnFinishedSequenceCallback)
			{
				OnFinishedSequenceCallback = Parameter.OnFinishedSequenceCallback;
				LevelSequencePlayer->OnFinished.AddUniqueDynamic(this, &UMS_SequenceManager::OnFinishedSequence);
			}
			
			// Play the level sequence
			LevelSequencePlayer->Play();
			if(Parameter.bHideWidget)
			{
				gWidgetMng.HideAllWidget(true);
			}
		}
	}
	else
	{
		MS_LOG_VERBOSITY(Error, TEXT("Unable to create level sequence player"));
	}
}

void UMS_SequenceManager::StopSequence()
{
	if(!SequenceActor)
	{
		return;
	}
	
	if(const TObjectPtr<ULevelSequencePlayer> SequencePlayer = SequenceActor->GetSequencePlayer())
	{
		SequencePlayer->GoToEndAndStop();
	}

	gWidgetMng.HideAllWidget(false);

	if(bSetBlendCamera)
	{
		gCameraMng.ReturnTarget();
	}
	
	if(OnFinishedSequenceCallback)
	{
		OnFinishedSequenceCallback();
	}

	GetWorld()->DestroyActor(SequenceActor);
	SequenceActor = nullptr;
}

bool UMS_SequenceManager::IsPlayingSequence() const
{
	if(SequenceActor)
	{
		if(const TObjectPtr<ULevelSequencePlayer> SequencePlayer = SequenceActor->GetSequencePlayer())
		{
			return SequencePlayer->IsPlaying();
		}
	}

	return false;
}

TObjectPtr<ULevelSequence> UMS_SequenceManager::LoadSequence(EMS_SequenceType SequenceType) const
{
	switch(SequenceType)
	{
	case EMS_SequenceType::Truck:
		return Cast<ULevelSequence>(StaticLoadObject(ULevelSequence::StaticClass(), nullptr, *SequencePath::Truck));
	case EMS_SequenceType::Entrance:
		return Cast<ULevelSequence>(StaticLoadObject(ULevelSequence::StaticClass(), nullptr, *SequencePath::Entrance));
	case EMS_SequenceType::OpenDoorTown:
		{
			const EMS_LevelType TownType = gSceneMng.GetCurrentLevelType();
			if(TownType == EMS_LevelType::Stage01)
			{
				return Cast<ULevelSequence>(StaticLoadObject(ULevelSequence::StaticClass(), nullptr, *SequencePath::OpenDoor_Town1));	
			}
			if(TownType == EMS_LevelType::Stage02)
			{
				return Cast<ULevelSequence>(StaticLoadObject(ULevelSequence::StaticClass(), nullptr, *SequencePath::OpenDoor_Town2));
			}
			if(TownType == EMS_LevelType::Stage03)
			{
				return Cast<ULevelSequence>(StaticLoadObject(ULevelSequence::StaticClass(), nullptr, *SequencePath::OpenDoor_Town3));
			}
		}
	case EMS_SequenceType::CloseDoorTown:
		{
			const EMS_LevelType TownType = gSceneMng.GetCurrentLevelType();
			if(TownType == EMS_LevelType::Stage01)
			{
				return Cast<ULevelSequence>(StaticLoadObject(ULevelSequence::StaticClass(), nullptr, *SequencePath::CloseDoor_Town1));	
			}
			if(TownType == EMS_LevelType::Stage02)
			{
				return Cast<ULevelSequence>(StaticLoadObject(ULevelSequence::StaticClass(), nullptr, *SequencePath::CloseDoor_Town2));
			}
			if(TownType == EMS_LevelType::Stage03)
			{
				return Cast<ULevelSequence>(StaticLoadObject(ULevelSequence::StaticClass(), nullptr, *SequencePath::CloseDoor_Town3));
			}
		}
	case EMS_SequenceType::OpenDoorMarket:
		return Cast<ULevelSequence>(StaticLoadObject(ULevelSequence::StaticClass(), nullptr, *SequencePath::OpenDoor_Market));
	case EMS_SequenceType::CloseDoorMarket:
		return Cast<ULevelSequence>(StaticLoadObject(ULevelSequence::StaticClass(), nullptr, *SequencePath::CloseDoor_Market));
	default:
		return nullptr;
	}
}

void UMS_SequenceManager::OnSignatureChangedEvent()
{
	gWidgetMng.ShowMessageOnScreen(TEXT("OnSignatureChangedEvent"));
}

void UMS_SequenceManager::OnFinishedSequence()
{
	gWidgetMng.HideAllWidget(false);

	if(OnFinishedSequenceCallback)
	{
		OnFinishedSequenceCallback();
	}
	
	if(bSetBlendCamera)
	{
		gCameraMng.ReturnTarget(2.f);
	}

	GetWorld()->DestroyActor(SequenceActor);
}

UMS_SequenceManager* UMS_SequenceManager::GetInstance()
{
	return SequenceManager;
}
