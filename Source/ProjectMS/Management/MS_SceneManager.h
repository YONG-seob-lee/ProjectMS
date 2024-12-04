// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Utility/Command/SceneCommand/MS_SceneCommand.h"
#include "MS_SceneManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMS_OnLevelLoadedDelegate);

UENUM()
enum class EMS_SceneType
{
	None = 0,
	
};

UENUM()
enum class EMS_FadeStep
{
	Undefined = 0,
	EnterFadeOut,
	ExitFadeOut,
	Loading,
	EnterFadeIn,
	ExitFadeIn,
	Finished,
};

/**
 * 
 */
UCLASS()
class PROJECTMS_API AMS_SceneManager : public AActor
{
	GENERATED_BODY()
public:
	AMS_SceneManager();
	
	virtual void PostInitializeComponents() override;
	virtual void Tick(float DeltaSeconds) override;
	
	void RequestChangeScene(const TObjectPtr<class UMS_SceneCommand>& aCommand);
private:
	void StartFade();
	void ProcessFade();
	void EndFade();
	
	void RequestLevel();
	UFUNCTION()
	void HandleUnloadLevel(const FName& aLevelName);
	UFUNCTION()
	void HandleLevelInstanceLoading();
	UFUNCTION()
	void HandleLevelInstanceUnLoading();
	UFUNCTION()
	void HandleLoadLevel();

	UFUNCTION()
	void HandleLoadingLevel();

	UPROPERTY()
	TObjectPtr<UWorld> PersistentLevelWorld = nullptr;
	UPROPERTY()
	TObjectPtr<UMS_SceneCommand> NewCommand = nullptr;
	UPROPERTY()
	TObjectPtr<ULevelStreaming> LevelStreamingInst = nullptr;
	EMS_FadeStep LevelChangeStep= EMS_FadeStep::Undefined;
	
	// UUID(Universally Unique IDentifier)란 네트워크 상에서 중복되지 않는 ID를 만들기 위한 표준 규약이다.
	int32 LatentActionInfoUUIDCounter = 0;
	
	FTimerHandle FadeTimerHandle = {};
	float FadeProgressRate = 0.0f;

	TWeakObjectPtr<class UMS_RootWidget> RootWidget = nullptr;
	
	FMS_OnLevelLoadedDelegate OnLevelLoadedDelegate = {};

	UPROPERTY()
	TObjectPtr<class UMS_LevelCacheTable> LevelTable = nullptr;
};
