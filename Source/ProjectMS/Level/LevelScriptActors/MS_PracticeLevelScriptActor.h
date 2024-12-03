// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Level/MS_LevelScriptActorBase.h"
#include "MS_PracticeLevelScriptActor.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API AMS_PracticeLevelScriptActor : public AMS_LevelScriptActorBase
{
	GENERATED_BODY()
public:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaSeconds) override;

private:
	
	TObjectPtr<class UMS_BasePlayer> Player;
	TObjectPtr<class AMS_SpawnPoint> PlayerSpawnPoint;
};