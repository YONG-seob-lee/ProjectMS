// Fill out your copyright notice in the Description page of Project Settings.


#include "../MS_LevelScriptActorBase.h"

#include "EngineUtils.h"
#include "Actor/SpawnPoint/MS_SpawnPoint.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "CoreClass/Controller/MS_PlayerController.h"
#include "LevelInstance/LevelInstanceActor.h"
#include "Management/Public/MS_UnitManager.h"
#include "Public/MS_WidgetManager.h"
#include "Unit/MS_BasePlayer.h"
#include "Utility/MS_Define.h"
#include "Widget/Persistent/MS_PersistentWidget.h"


// Sets default values
AMS_LevelScriptActorBase::AMS_LevelScriptActorBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AMS_LevelScriptActorBase::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	static bool DuplicatedFunctionCallFlag = false;
	FName ChangedMemberPropertyName = (PropertyChangedEvent.MemberProperty != nullptr ? PropertyChangedEvent.MemberProperty->GetFName() : NAME_None);
	if (ChangedMemberPropertyName == FName("BaseLayerLevelCollectionSwitch"))
	{
		DuplicatedFunctionCallFlag = DuplicatedFunctionCallFlag == false ? true : false;
		if (DuplicatedFunctionCallFlag == true)
		{
			OnBaseLayerLevelCollectionSwitchClick();
		}
	}
}

void AMS_LevelScriptActorBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	GetWorldSettings()->bAllowTickBeforeBeginPlay = false;
	
	TArray<TObjectPtr<AActor>>& ActorArray = GetLevel()->Actors;
	for (int i = 0; i < ActorArray.Num(); ++i)
	{
		if (ActorArray[i].Get() == nullptr)
			continue;

		if (ActorArray[i]->ActorHasTag(FName(TEXT("BaseLayerLevel"))) == true)
			ActorArray[i]->Destroy();
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
	MS_CHECK(PlayerController);

	PlayerController->RegisterManagement();
	
	UnitManager = PlayerController->GetUnitManager();
	MS_CHECK(UnitManager.IsValid());
	
	SceneManager = PlayerController->GetSceneManager();
	MS_CHECK(SceneManager);
}

// Called every frame
void AMS_LevelScriptActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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
				SpawnedBaseLayerLevelInstance->SetActorLabel(AssetDataArray[i].AssetName.ToString(), false);
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
	MS_CHECK(UnitManager.IsValid());
	
	const TObjectPtr<UMS_UnitBase> Player = UnitManager->CreateUnit(Practice::DefaultCharacterIndex, UMS_BasePlayer::StaticClass(), aSpawnPoint->GetActorLocation(), aSpawnPoint->GetActorRotation());
	MS_CHECK(Player);

	if(const TObjectPtr<AMS_CharacterBase> CharacterBase = Player->GetCharacterBase())
	{
		CharacterBase->GetCharacterRootComponent()->ComponentTags.Emplace(FName("Title"));
	}

	//UITT_InstUtil::AssignUnitHandle(gUnitMng.GetUnitHandle(Cody));

	return Player;
}
#endif
