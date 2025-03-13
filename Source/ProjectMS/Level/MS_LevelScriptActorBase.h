// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "MS_LevelScriptActorBase.generated.h"

namespace Practice
{
	const FName DefaultCharacter = TEXT("asdf");
	constexpr int32 DefaultCharacterIndex = 1;
}

UCLASS()
class PROJECTMS_API AMS_LevelScriptActorBase : public ALevelScriptActor
{
	GENERATED_BODY()
	
public:
	AMS_LevelScriptActorBase();
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaSeconds) override;

	TWeakObjectPtr<AActor> GetLevelSpecificActor(const FName& aKey) const;
	
#if WITH_EDITOR
	UFUNCTION(BlueprintCallable, CallInEditor) void OnBaseLayerLevelCollectionSwitchClick();
#endif

protected:
	void CashingDirectionalLight();
	
	virtual TObjectPtr<class AMS_SpawnPoint> GetSpawnPoint(const FName& aCharacterName) const;
	virtual TObjectPtr<class UMS_UnitBase> CreatePlayer(const TObjectPtr<class AMS_SpawnPoint> aSpawnPoint);

	UPROPERTY()
	TObjectPtr<class ADirectionalLight> DirectionalLight = nullptr;
	
public:
	
	// Property
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TArray<TSoftObjectPtr<UWorld>> BaseLayerLevelArray = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool BaseLayerLevelCollectionSwitch = false;

	TArray<TObjectPtr<AActor>> Actors;

	UPROPERTY(EditAnywhere)
	TMap<FName, TWeakObjectPtr<AActor>> LevelSpecificActors;
};
