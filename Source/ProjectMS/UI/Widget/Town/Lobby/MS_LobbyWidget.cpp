// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_LobbyWidget.h"

#include "MS_PlayerCameraManager.h"
#include "MS_SceneManager.h"
#include "Button/MS_Button.h"
#include "Widget/Town/MS_TownWidget.h"

void UMS_LobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CPP_StartButton->GetOnClickedDelegate().AddUObject(this, &UMS_LobbyWidget::OnClickedStartButton);
}

void UMS_LobbyWidget::OnClickedStartButton()
{
	CREATE_SCENE_COMMAND(Command)
	Command->SetFadeOutTransitionType(EMS_TransitionStyle::Undefined);
	Command->SetFadeInTransitionType(EMS_TransitionStyle::Undefined);
	Command->SetNextWidget(UMS_TownWidget::GetWidgetName());
	Command->OnFadeEventDelegate = FMS_FadeEventDelegate::CreateWeakLambda(this, []
	{
		gCameraMng.SwitchViewCamera(EMS_ViewCameraType::QuarterView);
	});

	gSceneMng.RequestChangeScene(Command);
}
