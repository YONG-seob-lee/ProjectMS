// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/Public/LevelScriptActors/MS_PracticeLevelScriptActor.h"

void AMS_PracticeLevelScriptActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AMS_PracticeLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();

	PlayerSpawnPoint = GetSpawnPoint(Practice::DefaultCharacter);
	if(PlayerSpawnPoint)
	{
		CreatePlayer(PlayerSpawnPoint);
	}
}

void AMS_PracticeLevelScriptActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AMS_PracticeLevelScriptActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}