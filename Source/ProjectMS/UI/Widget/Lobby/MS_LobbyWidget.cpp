// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_LobbyWidget.h"

#include "MS_Define.h"
#include "Button/MS_Button.h"
#include "Manager_Client/MS_SceneManager.h"
#include "Manager_Client/MS_PlayerCameraManager.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "Widget/Town/MS_TownWidget.h"

void UMS_LobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CPP_StartButton->GetOnClickedDelegate().AddUObject(this, &UMS_LobbyWidget::OnClickedStartButton);
	gCameraMng.SwitchViewCamera(EMS_ViewCameraType::SideView);
}

void UMS_LobbyWidget::OnClickedStartButton()
{
	gCameraMng.GetOnFinishedCameraTransitionDelegate().BindWeakLambda(this, []()
	{
		gWidgetMng.Create_Widget(UMS_TownWidget::GetWidgetName());
		gWidgetMng.ShowGeneralWidget(true);
	});
	
	CREATE_SCENE_COMMAND(Command)
	Command->SetFadeOutTransitionType(EMS_TransitionStyle::Undefined);
	Command->SetFadeInTransitionType(EMS_TransitionStyle::Undefined);
	Command->OnFadeEventDelegate.AddWeakLambda(this, [this]
	{
		FViewTargetTransitionParams Param;
		Param.BlendTime = 1.f;
		gCameraMng.SwitchViewCamera(EMS_ViewCameraType::QuarterView, Param);
	});

	gSceneMng.RequestChangeScene(Command);
}
