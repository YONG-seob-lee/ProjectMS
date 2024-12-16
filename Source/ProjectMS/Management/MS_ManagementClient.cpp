// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ManagementClient.h"

#include "MS_Define.h"
#include "Controller/MS_PlayerController.h"
#include "Manager_Client/MS_InputManager.h"
#include "Manager_Client/MS_PlayerCameraManager.h"
#include "Manager_Client/MS_WidgetManager.h"

void UMS_ManagementClient::Initialize()
{
	Super::Initialize();
	
	
	InputManager = MS_NewObject<UMS_InputManager>(this);
	MS_CHECK(InputManager);
	InputManager->Initialize();
	
	const TObjectPtr<AMS_PlayerController> PlayerController = Cast<AMS_PlayerController>(GetOuter());
	MS_CHECK(PlayerController);
	
	WidgetManager = MS_NewObject<UMS_WidgetManager>(this);
	MS_CHECK(WidgetManager);
	WidgetManager->Initialize();
	
	CameraManager = Cast<AMS_PlayerCameraManager>(PlayerController->PlayerCameraManager);
}
