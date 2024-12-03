// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_Management.h"

#include "CoreClass/Controller/MS_PlayerController.h"
#include "MS_PlayerCameraManager.h"
#include "ProjectMS/Utility/MS_Define.h"
#include "MS_SceneManager.h"
#include "MS_TableManager.h"
#include "MS_UnitManager.h"
#include "MS_WidgetManager.h"

void UMS_Management::Initialize()
{
}

void UMS_Management::Finalize()
{
}

void UMS_Management::PostInitialize()
{
}

void UMS_Management::Tick(float aDeltaTime)
{
}

void UMS_Management::InitManager()
{
	// [Create Manager Instance]	MS_NewObject...
	
	TableManager = MS_NewObject<UMS_TableManager>(this);
	MS_CHECK(TableManager);
	TableManager->Initialize();
	
	AMS_PlayerController* PlayerController = Cast<AMS_PlayerController>(GetOuter());
	MS_CHECK(PlayerController);
	
	WidgetManager = MS_NewObject<UMS_WidgetManager>(this);
	MS_CHECK(WidgetManager);
	WidgetManager->Initialize();
	
	FActorSpawnParameters ManagerActorSpawnParameters = {};
	ManagerActorSpawnParameters.Owner = PlayerController;
	ManagerActorSpawnParameters.Instigator = PlayerController->GetInstigator();
	ManagerActorSpawnParameters.ObjectFlags |= RF_Transient;
	SceneManager = GetWorld()->SpawnActor<AMS_SceneManager>(AMS_SceneManager::StaticClass(), ManagerActorSpawnParameters);
	
	UnitManager = MS_NewObject<UMS_UnitManager>(this);
	MS_CHECK(UnitManager);
	UnitManager->Initialize();
	
	CameraManager = Cast<AMS_PlayerCameraManager>(PlayerController->PlayerCameraManager);
}
