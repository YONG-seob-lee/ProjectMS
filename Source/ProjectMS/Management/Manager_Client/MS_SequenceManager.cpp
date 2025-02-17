// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_SequenceManager.h"

#include "LevelSequence.h"
#include "LevelSequencePlayer.h"
#include "MS_Define.h"
#include "MS_PlayerCameraManager.h"
#include "MS_WidgetManager.h"

UMS_SequenceManager::UMS_SequenceManager()
{
	SequenceManager = this;

	if(const ConstructorHelpers::FObjectFinder<ULevelSequence> LEVELSEQUENCE(TEXT("/Game/Blueprints/Sequence/InToTruckSequence")); LEVELSEQUENCE.Succeeded())
	{
		Sequence = LEVELSEQUENCE.Object;
	}
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

void UMS_SequenceManager::PlaySequence()
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
	
	if (const TObjectPtr<ULevelSequencePlayer> LevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), Sequence, FMovieSceneSequencePlaybackSettings(), SequenceActor))
	{
		gCameraMng.SetViewTarget(SequenceActor);
		SequenceActor->SetActorLocationAndRotation(FVector(518.f, 1392.f, 1003.f), FRotator(-45.f, -90.f, 0.f));
		// Play the level sequence
		LevelSequencePlayer->Play();
		LevelSequencePlayer->OnFinished.AddUniqueDynamic(this, &UMS_SequenceManager::OnFinishedSequence);
		gWidgetMng.HideAllWidget(true);
	}
	else
	{
		MS_LOG_VERBOSITY(Error, TEXT("Unable to create level sequence player"));
	}
}

void UMS_SequenceManager::OnSignatureChangedEvent()
{
	gWidgetMng.ShowMessageOnScreen(TEXT("OnSignatureChangedEvent"));
}

void UMS_SequenceManager::OnFinishedSequence()
{
	gWidgetMng.HideAllWidget(false);
	gCameraMng.ReturnTarget();
}

UMS_SequenceManager* UMS_SequenceManager::GetInstance()
{
	return SequenceManager;
}
