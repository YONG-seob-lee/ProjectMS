// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_GameState.h"

#include "MS_Define.h"
#include "MS_ManagementBoth.h"
#include "Manager_Both/MS_SceneManager.h"
#include "Mode/ModeHelper/MS_LevelModeHelper.h"
#include "Table/RowBase/MS_Level.h"


AMS_GameState::AMS_GameState(const FObjectInitializer& aObjectInitializer)
	: Super(aObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMS_GameState::PreInitializeComponents()
{
	Super::PreInitializeComponents();
	
	RegisterManagement();
}

void AMS_GameState::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	BindOnLevelLoadComplete();
}

void AMS_GameState::BeginPlay()
{
	Super::BeginPlay();
}

void AMS_GameState::Destroyed()
{
	if(ManagementBoth)
	{
		ManagementBoth->Finalize();
		ManagementBoth = nullptr;
	}
	Super::Destroyed();
}

void AMS_GameState::RegisterManagement()
{
	if (ManagementBoth)
	{
		return;
	}
	
	ManagementBoth = MS_NewObject<UMS_ManagementBoth>(this);
	ManagementBoth->Initialize();
}

void AMS_GameState::BindOnLevelLoadComplete()
{
	gSceneMng.OnLevelLoadedDelegate.AddDynamic(this, &AMS_GameState::OnLevelLoadComplete);
}

void AMS_GameState::OnLevelLoadComplete()
{
	ChangeModeHelper();
}

void AMS_GameState::ChangeModeHelper()
{
	if (LevelModeHelper)
	{
		LevelModeHelper->Finalize();
		MS_DeleteObject(LevelModeHelper);
		return;
	}
	
	FMS_Level* LevelData = gSceneMng.GetCurrentLevelData();
	if (LevelData && LevelData->LevelModeHelperClass != nullptr)
	{
		LevelModeHelper = MS_NewObject<UMS_LevelModeHelper>(this, LevelData->LevelModeHelperClass);
		LevelModeHelper->Initialize();
	}
}