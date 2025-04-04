﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_LobbyWidget.h"

#include "MS_Define.h"
#include "Button/MS_Button.h"
#include "Manager_Client/MS_InputManager.h"
#include "Manager_Client/MS_SceneManager.h"
#include "Manager_Client/MS_PlayerCameraManager.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "Widget/Town/MS_TownWidget.h"

void UMS_LobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CPP_StartButton->SetVisibility(ESlateVisibility::Collapsed);
	gSceneMng.OnFadeFinishedEventDelegate.AddWeakLambda(this, [this]()
	{
		CPP_StartButton->SetVisibility(ESlateVisibility::Visible);
		gCameraMng.RestrictCameraMovement(true);
	});
	
	CPP_StartButton->GetOnClickedDelegate().AddUObject(this, &UMS_LobbyWidget::OnClickedStartButton);
	gCameraMng.SwitchViewCamera(EMS_ViewCameraType::SideView);
	PlayAnimationByName(DefaultWidgetAnimation::Idle, 0, 100);
}

void UMS_LobbyWidget::OnClickedStartButton()
{	
	CREATE_SCENE_COMMAND(Command)
	Command->SetFadeOutTransitionType(EMS_TransitionStyle::Undefined);
	Command->SetFadeInTransitionType(EMS_TransitionStyle::Undefined);
	Command->SetAllowInteractActor(false);
	Command->OnFadeEventDelegate.AddWeakLambda(this, [this]
	{
		FViewTargetTransitionParams Param;
		Param.BlendTime = 1.f;
		gCameraMng.SwitchViewCamera(EMS_ViewCameraType::QuarterView, Param);
		gCameraMng.GetOnFinishedCameraTransitionDelegate().BindWeakLambda(this, []()
		{
			gInputMng.SetAllowInteractActor(true);
			gWidgetMng.Create_Widget(UMS_TownWidget::GetWidgetName());
		});
	});

	gSceneMng.RequestChangeScene(Command);
}
