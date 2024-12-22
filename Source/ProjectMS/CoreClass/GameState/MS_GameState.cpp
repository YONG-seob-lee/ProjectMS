// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_GameState.h"

#include "MS_Define.h"
#include "MS_ManagementBoth.h"
#include "GameFramework/GameSession.h"
#include "Manager_Client/MS_SceneManager.h"
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
}

void AMS_GameState::BeginPlay()
{
	Super::BeginPlay();
}

void AMS_GameState::Destroyed()
{
	DestroyManagement();
	
	Super::Destroyed();
}

void AMS_GameState::RegisterManagement()
{
	if (IsValid(ManagementBoth))
	{
		return;
	}
	
	ManagementBoth = MS_NewObject<UMS_ManagementBoth>(this);
	ManagementBoth->Initialize();
}

void AMS_GameState::DestroyManagement()
{
	if(IsValid(ManagementBoth))
	{
		ManagementBoth->Finalize();
		ManagementBoth = nullptr;
	}
}