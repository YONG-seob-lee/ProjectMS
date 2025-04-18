﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_LevelScriptActorBase.h"

#include "EngineUtils.h"
#include "Actor/SpawnPoint/MS_SpawnPoint.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Character/MS_CharacterBase.h"
#include "CoreClass/Controller/MS_PlayerController.h"
#include "Engine/DirectionalLight.h"
#include "Kismet/GameplayStatics.h"
#include "LevelInstance/LevelInstanceActor.h"
#include "Manager_Both/MS_UnitManager.h"
#include "Units/MS_BasePlayerUnit.h"
#include "Utility/MS_Define.h"


// Sets default values
AMS_LevelScriptActorBase::AMS_LevelScriptActorBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

#if WITH_EDITOR
void AMS_LevelScriptActorBase::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	static bool DuplicatedFunctionCallFlag = false;
	const FName ChangedMemberPropertyName = (PropertyChangedEvent.MemberProperty != nullptr ? PropertyChangedEvent.MemberProperty->GetFName() : NAME_None);
	if (ChangedMemberPropertyName == FName("BaseLayerLevelCollectionSwitch"))
	{
		DuplicatedFunctionCallFlag = DuplicatedFunctionCallFlag == false ? true : false;
		if (DuplicatedFunctionCallFlag == true)
		{
			OnBaseLayerLevelCollectionSwitchClick();
		}
	}
}
#endif

void AMS_LevelScriptActorBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	GetWorldSettings()->bAllowTickBeforeBeginPlay = false;

	const TObjectPtr<ULevel> Level = GetLevel();
	Actors = Level->Actors;

	for (int i = 0; i < Actors.Num(); ++i)
	{
		TObjectPtr<AActor> Actor = Actors[i].Get();
		if (Actor == nullptr)
		{
			continue;
		}
		
		// if (ActorArray[i]->ActorHasTag(FName(TEXT("BaseLayerLevel"))) == true)
		// {
		// 	ActorArray[i]->Destroy();
		// }
	}

	for (int i = 0; i < BaseLayerLevelArray.Num(); ++i)
	{
		if (BaseLayerLevelArray[i].IsNull() == true)
		{
			BaseLayerLevelArray.RemoveAt(i);
			--i;
		}
	}
}

void AMS_LevelScriptActorBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

// Called when the game starts or when spawned
void AMS_LevelScriptActorBase::BeginPlay()
{
	Super::BeginPlay();

	const TObjectPtr<UWorld> World = GetWorld();
	MS_CHECK(World);

	const TObjectPtr<AMS_PlayerController> PlayerController = World->GetFirstPlayerController<AMS_PlayerController>();
	if(PlayerController)
	{
		PlayerController->RegisterManagement();
	}
	
}

// Called every frame
void AMS_LevelScriptActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

TWeakObjectPtr<AActor> AMS_LevelScriptActorBase::GetLevelSpecificActor(const FName& aKey) const
{
	if (LevelSpecificActors.Contains(aKey))
	{
		return *LevelSpecificActors.Find(aKey);
	}

	return nullptr;
}

#if WITH_EDITOR
void AMS_LevelScriptActorBase::OnBaseLayerLevelCollectionSwitchClick()
{
	FString LevelFolderPath = GetLevel()->GetPathName();
	for (int i = LevelFolderPath.Len() - 1; i >= 0; --i)
	{
		if (LevelFolderPath[i] == '/')
			break;
		else
			LevelFolderPath.RemoveAt(i);
	}
	LevelFolderPath.Append(TEXT("BaseLayerLevel/"));
	const FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	const IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();
	TArray<FAssetData> AssetDataArray = {};
	AssetRegistry.GetAssetsByPath(FName(*LevelFolderPath), AssetDataArray);

	const UClass* LevelScriptActorClass = this->GetClass();
	AMS_LevelScriptActorBase* CDOLevelScriptActor = LevelScriptActorClass->GetDefaultObject<AMS_LevelScriptActorBase>();
	const FBoolProperty* BaseLayerLevelCollectionSwitchBoolProperty = CastField<FBoolProperty>(LevelScriptActorClass->FindPropertyByName(FName(TEXT("BaseLayerLevelCollectionSwitch"))));
	const FArrayProperty* BaseLayerLevelArrayArrayProperty = CastField<FArrayProperty>(LevelScriptActorClass->FindPropertyByName(FName(TEXT("BaseLayerLevelArray"))));
	TArray<TSoftObjectPtr<UWorld>>* CDOBaseLayerLevelArray = BaseLayerLevelArrayArrayProperty->ContainerPtrToValuePtr<TArray<TSoftObjectPtr<UWorld>>>(CDOLevelScriptActor);

	if (BaseLayerLevelCollectionSwitchBoolProperty->GetPropertyValue_InContainer(CDOLevelScriptActor) == true)
	{
		if (AssetDataArray.Num() == 0)
		{
			BaseLayerLevelCollectionSwitchBoolProperty->SetPropertyValue_InContainer(CDOLevelScriptActor, false);
			FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(FString(TEXT("Please place the base layer level in the './BaseLayerLevel' folder."))));
			return;
		}

		if (CDOBaseLayerLevelArray->Num() > 0)
			CDOBaseLayerLevelArray->Empty();

		for (int i = 0; i < AssetDataArray.Num(); ++i)
		{
			if (AssetDataArray[i].GetClass()->IsChildOf(UWorld::StaticClass()) == true)
			{
				CDOBaseLayerLevelArray->Add(TSoftObjectPtr<UWorld>(AssetDataArray[i].ToSoftObjectPath()));

				ALevelInstance* SpawnedBaseLayerLevelInstance = Cast<UWorld>(GetLevel()->GetOuter())->SpawnActor<ALevelInstance>();
				//SpawnedBaseLayerLevelInstance->SetActorLabel(AssetDataArray[i].AssetName.ToString(), false);
				SpawnedBaseLayerLevelInstance->Tags.Add(FName(TEXT("BaseLayerLevel")));
				SpawnedBaseLayerLevelInstance->SetWorldAsset(TSoftObjectPtr<UWorld>(AssetDataArray[i].ToSoftObjectPath()));
				SpawnedBaseLayerLevelInstance->UpdateLevelInstanceFromWorldAsset();
			}
		}
	}
	else
	{
		CDOBaseLayerLevelArray->Empty();
		TArray<TObjectPtr<AActor>>& ActorArray = GetLevel()->Actors;
		for (int i = 0; i < ActorArray.Num(); ++i)
		{
			if (ActorArray[i].Get() == nullptr)
				continue;

			if (ActorArray[i]->ActorHasTag(FName(TEXT("BaseLayerLevel"))) == true)
				ActorArray[i]->Destroy();
		}
	}
}
#endif

void AMS_LevelScriptActorBase::CashingDirectionalLight()
{
	TArray<AActor*> DirectionalLightActors;
	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADirectionalLight::StaticClass(), DirectionalLightActors);
	
	if(DirectionalLightActors.Num() > 1)
	{
		MS_ENSURE(false);
	}

	if(DirectionalLightActors.IsValidIndex(0))
	{
		DirectionalLight = Cast<ADirectionalLight>(DirectionalLightActors[0]);
	}
}

TObjectPtr<AMS_SpawnPoint> AMS_LevelScriptActorBase::GetSpawnPoint(const FName& aCharacterName) const
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

TObjectPtr<UMS_UnitBase> AMS_LevelScriptActorBase::CreatePlayer(const TObjectPtr<AMS_SpawnPoint> aSpawnPoint)
{
	const TObjectPtr<UMS_BasePlayerUnit> Player = Cast<UMS_BasePlayerUnit>(gUnitMng.CreateUnit(EMS_UnitType::BasePlayer, 1, true, aSpawnPoint->GetActorLocation(), aSpawnPoint->GetActorRotation()));
	MS_CHECK(Player);

	TWeakObjectPtr<AMS_CharacterBase> CharacterBase = Player->GetCharacter();
	if (CharacterBase != nullptr)
	{
		CharacterBase->GetCharacterRootComponent()->ComponentTags.Emplace(FName("Title"));
	}

	return Player;
}