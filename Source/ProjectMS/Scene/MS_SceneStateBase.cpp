// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_SceneStateBase.h"

#include "EngineUtils.h"
#include "Actor/Character/MS_CharacterBase.h"
#include "Actor/SpawnPoint/MS_SpawnPoint.h"
#include "Unit/MS_BasePlayer.h"
#include "Utility/MS_Define.h"

void UMS_SceneStateBase::Begin()
{
	Super::Begin();

	LoadingProcessDelegates.Empty();
	LoadingProcessDelegates.Add(FMS_LoadingProcessDelegate::CreateUObject(this, &UMS_SceneStateBase::LoadingPreProcess));
	LoadingProcessDelegates.Add(FMS_LoadingProcessDelegate::CreateUObject(this, &UMS_SceneStateBase::LoadingProcess));
	LoadingProcessDelegates.Add(FMS_LoadingProcessDelegate::CreateUObject(this, &UMS_SceneStateBase::LoadingPostProcess));
}

void UMS_SceneStateBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void UMS_SceneStateBase::Exit()
{
	Super::Exit();

	LoadingProcessDelegates.Empty();
}

void UMS_SceneStateBase::TickLoading(float DeltaTime)
{
	if (LoadingProcessDelegates.IsValidIndex(0) == true)
	{
		if (LoadingProcessDelegates[0].Execute(DeltaTime) == true)
		{
			LoadingProcessDelegates.RemoveAt(0);
		}
	}
}

bool UMS_SceneStateBase::IsCompleteLoading() const
{
	return LoadingProcessDelegates.Num() <= 0;
}

bool UMS_SceneStateBase::LoadingPreProcess(float DeltaTime)
{
	return true;
}

bool UMS_SceneStateBase::LoadingProcess(float DeltaTime)
{
	return true;
}

bool UMS_SceneStateBase::LoadingPostProcess(float DeltaTime)
{
	return true;
}

TObjectPtr<AMS_SpawnPoint> UMS_SceneStateBase::GetSpawnPoint(const FName& aCharacterName) const
{
	const TObjectPtr<UWorld> World = GetWorld();
	for(TActorIterator<AActor> Iter(World); Iter; ++Iter)
	{
		if(const TObjectPtr<AMS_SpawnPoint> SpawnPoint = Cast<AMS_SpawnPoint>(*Iter))
		{
			if(SpawnPoint->GetSpawnName() == aCharacterName)
			{
				return SpawnPoint;
			}
		}
	}

	return nullptr;
}

TObjectPtr<UMS_BasePlayer> UMS_SceneStateBase::CreatePlayer(const TObjectPtr<AMS_SpawnPoint> aSpawnPoint)
{
	MS_CHECK(UnitManager.IsValid());
	
	const TObjectPtr<UMS_BasePlayer> Player = Cast<UMS_BasePlayer>(UnitManager->CreateUnit(Practice::DefaultCharacterIndex, UMS_BasePlayer::StaticClass(), aSpawnPoint->GetActorLocation(), aSpawnPoint->GetActorRotation()));
	MS_CHECK(Player);

	if(const TObjectPtr<AMS_CharacterBase> CharacterBase = Player->GetCharacterBase())
	{
		CharacterBase->GetCharacterRootComponent()->ComponentTags.Emplace(FName("Title"));
	}

	//UITT_InstUtil::AssignUnitHandle(gUnitMng.GetUnitHandle(Cody));

	return Player;
}