// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ManagementClient.h"

#include "MS_Define.h"
#include "Controller/MS_PlayerController.h"
#include "Manager_Client/MS_InputManager.h"
#include "Manager_Client/MS_InteractionManager.h"
#include "Manager_Client/MS_ItemManager.h"
#include "Manager_Client/MS_ModeManager.h"
#include "Manager_Client/MS_PlayerCameraManager.h"
#include "Manager_Client/MS_SceneManager.h"
#include "Manager_Client/MS_ScheduleManager.h"
#include "Manager_Client/MS_SoundManager.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "Tutorial/MS_TutorialHelper.h"

void UMS_ManagementClient::Initialize()
{
	Super::Initialize();

	SceneManager = MS_NewObject<UMS_SceneManager>(this);
	MS_CHECK(SceneManager);
	SceneManager->Initialize();
	
	ModeManager = MS_NewObject<UMS_ModeManager>(this);
	MS_CHECK(ModeManager);
	ModeManager->Initialize();

	InteractionManager = MS_NewObject<UMS_InteractionManager>(this);
	MS_CHECK(InteractionManager);
	InteractionManager->Initialize();

	ItemManager = MS_NewObject<UMS_ItemManager>(this);
	MS_CHECK(ItemManager);
	ItemManager->Initialize();
	
	InputManager = MS_NewObject<UMS_InputManager>(this);
	MS_CHECK(InputManager);
	InputManager->Initialize();
	
	const TObjectPtr<AMS_PlayerController> PlayerController = Cast<AMS_PlayerController>(GetOuter());
	MS_CHECK(PlayerController);
	
	WidgetManager = MS_NewObject<UMS_WidgetManager>(this);
	MS_CHECK(WidgetManager);
	WidgetManager->Initialize();
	
	CameraManager = Cast<AMS_PlayerCameraManager>(PlayerController->PlayerCameraManager);

	ScheduleManager = MS_NewObject<UMS_ScheduleManager>(this);
	MS_CHECK(ScheduleManager);
	ScheduleManager->Initialize();

	SoundManager = MS_NewObject<UMS_SoundManager>(this);
	MS_CHECK(SoundManager);
	SoundManager->Initialize();
	
	TutorialHelper = MS_NewObject<UMS_TutorialHelper>(this);
	MS_CHECK(TutorialHelper);
	TutorialHelper->Initialize();
}

void UMS_ManagementClient::Finalize()
{
	if(TutorialHelper)
	{
		TutorialHelper->Destroyed();
		TutorialHelper = nullptr;
	}

	if(SoundManager)
	{
		SoundManager->Finalize();
		SoundManager = nullptr;
	}
	
	if(CameraManager)
	{
		CameraManager->Destroyed();
		CameraManager = nullptr;
	}
	
	if(WidgetManager)
	{
		WidgetManager->Finalize();
		WidgetManager = nullptr;
	}

	if(InputManager)
	{
		InputManager->Finalize();
		InputManager = nullptr;
	}
	
	if(InteractionManager)
	{
		InteractionManager->Finalize();
		InteractionManager = nullptr;
	}
	
	if(ModeManager)
	{
		ModeManager->Finalize();
		ModeManager = nullptr;
	}
	
	if(SceneManager)
	{
		SceneManager->Finalize();
		SceneManager = nullptr;
	}
	
	Super::Finalize();
}

void UMS_ManagementClient::PostInitialize()
{
	Super::PostInitialize();

	if(SceneManager)
	{
		SceneManager->PostInitialize();
	}
	
	if(ModeManager)
	{
		ModeManager->PostInitialize();
	}
	
	if(InputManager)
	{
		InputManager->PostInitialize();
	}
	
	if(WidgetManager)
	{
		WidgetManager->PostInitialize();
	}
}

void UMS_ManagementClient::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
	
	if(ModeManager)
	{
		ModeManager->Tick(aDeltaTime);
	}
	
	if(InputManager)
	{
		InputManager->Tick(aDeltaTime);
	}

	if (WidgetManager)
	{
		WidgetManager->Tick(aDeltaTime);
	}
}

void UMS_ManagementClient::BeginPlay()
{
	Super::BeginPlay();

	if(ScheduleManager)
	{
		ScheduleManager->BeginPlay();
	}
}
