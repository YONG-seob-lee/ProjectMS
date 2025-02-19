// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_NormalModeWidget.h"

#include "Button/MS_Button.h"
#include "Manager_Client/MS_ModeManager.h"
#include "Manager_Client/MS_PlayerCameraManager.h"
#include "Manager_Client/MS_SceneManager.h"
#include "Manager_Client/MS_WidgetManager.h"


void UMS_NormalModeWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if(CPP_TownButton)
	{
		CPP_TownButton->GetOnClickedDelegate().AddUObject(this, &UMS_NormalModeWidget::OnClickedTownButton);
		CPP_ConstructButton->GetOnClickedDelegate().AddUObject(this, &UMS_NormalModeWidget::OnClickedConstructButton);
	}
}

void UMS_NormalModeWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMS_NormalModeWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UMS_NormalModeWidget::OnClickedTownButton()
{
	CREATE_SCENE_COMMAND(Command);
	Command->SetLevelType(EMS_LevelType::LobbyLevel);
	Command->SetPreviousLevelType(EMS_LevelType::MarketLevel);
	Command->SetFadeOutTransitionType(EMS_TransitionStyle::GradationOut);
	Command->SetFadeInTransitionType(EMS_TransitionStyle::GradationIn);
	Command->SetFadeAnimationType(EMS_FadeAnimationCurveType::Linear);
	Command->SetLoadingWidgetType(EMS_LoadingWidgetType::Default);
	Command->SetNextWidget(TEXT("DoNotCreateNextWidget"));
	gSceneMng.OnFadeFinishedEventDelegate.AddWeakLambda(this, [this]
	{
		FViewTargetTransitionParams Param;
		Param.BlendTime = 0.f;
		gCameraMng.SwitchViewCamera(EMS_ViewCameraType::QuarterView, Param);
		gWidgetMng.SetGeneralWidget(EMS_LevelType::Stage01);
		gSceneMng.OnFadeFinishedEventDelegate.RemoveAll(this);
	});
	gSceneMng.RequestChangeScene(Command);
}

void UMS_NormalModeWidget::OnClickedConstructButton()
{
	gModeMng.ChangeState(EMS_ModeState::Construct);
}

void UMS_NormalModeWidget::OnChangeMode(EMS_ModeState aModeState)
{
	Super::OnChangeMode(aModeState);
}
