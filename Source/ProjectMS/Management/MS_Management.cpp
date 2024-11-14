// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_Management.h"

#include "BasicClass/Controller/MS_PlayerController.h"
#include "CameraManager/MS_PlayerCameraManager.h"
#include "ProjectMS/Utility/MS_Define.h"
#include "TableManager/MS_TableManager.h"
#include "WidgetManager/MS_WidgetManager.h"

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

	const AMS_PlayerController* PlayerController = Cast<AMS_PlayerController>(GetOuter());
	MS_CHECK(PlayerController);
	CameraManager = PlayerController->PlayerCameraManager;

	WidgetManager = MS_NewObject<UMS_WidgetManager>(this);
	MS_CHECK(WidgetManager);
}
