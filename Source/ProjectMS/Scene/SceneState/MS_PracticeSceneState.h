// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Scene/MS_SceneStateBase.h"
#include "MS_PracticeSceneState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_PracticeSceneState : public UMS_SceneStateBase
{
	GENERATED_BODY()
protected:
	virtual void Begin() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Exit() override;
	virtual bool LoadingPostProcess(float DeltaTime) override;

private:
	virtual TObjectPtr<class UMS_BasePlayer> CreatePlayer(const TObjectPtr<class AMS_SpawnPoint> aSpawnPoint) override;
	
	TObjectPtr<class UMS_BasePlayer> Player;
	TObjectPtr<class AMS_SpawnPoint> PlayerSpawnPoint;
};
