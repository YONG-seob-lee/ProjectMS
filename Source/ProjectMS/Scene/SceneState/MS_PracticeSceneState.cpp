// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_PracticeSceneState.h"

void UMS_PracticeSceneState::Begin()
{
	Super::Begin();
}

void UMS_PracticeSceneState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void UMS_PracticeSceneState::Exit()
{
	Super::Exit();
}

bool UMS_PracticeSceneState::LoadingPostProcess(float DeltaTime)
{
	Super::LoadingPostProcess(DeltaTime);
	
	PlayerSpawnPoint = GetSpawnPoint(Practice::DefaultCharacter);
	MS_CHECK(PlayerSpawnPoint);

	const TObjectPtr<UMS_BasePlayer> aPlayer = CreatePlayer(PlayerSpawnPoint);
	
	return aPlayer != nullptr;
}

TObjectPtr<UMS_BasePlayer> UMS_PracticeSceneState::CreatePlayer(const TObjectPtr<AMS_SpawnPoint> aSpawnPoint)
{
	return Super::CreatePlayer(aSpawnPoint);
}
