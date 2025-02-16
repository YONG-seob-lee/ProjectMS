// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_MarketEndModal.h"

#include "MS_Define.h"
#include "Button/MS_Button.h"
#include "Manager_Client/MS_InputManager.h"
#include "Manager_Client/MS_ModeManager.h"
#include "Manager_Client/MS_PlayerCameraManager.h"
#include "Manager_Client/MS_SceneManager.h"
#include "Manager_Client/MS_ScheduleManager.h"
#include "Manager_Client/MS_WidgetManager.h"

void UMS_MarketEndModal::NativeConstruct()
{
	Super::NativeConstruct();

	CPP_ClosingPlayButton->GetOnClickedDelegate().AddUObject(this, &UMS_MarketEndModal::OnClickedClosingPlayButton);
}

void UMS_MarketEndModal::OnClickedClosingPlayButton()
{
	gWidgetMng.CloseModalWidget();
}
