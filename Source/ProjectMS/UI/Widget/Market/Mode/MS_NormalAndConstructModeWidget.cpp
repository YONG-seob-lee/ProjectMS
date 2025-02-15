// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_NormalAndConstructModeWidget.h"

#include "Button/MS_Button.h"
#include "Manager_Client/MS_PlayerCameraManager.h"
#include "Manager_Client/MS_SceneManager.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "Widget/Market/Expander/MS_MarketExpanderWidget.h"
#include "Widget/Market/Modal/MS_MarketStartModal.h"
#include "Widget/System/Modal/MS_ModalWidget.h"


void UMS_NormalAndConstructModeWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if(CPP_RunButton)
	{
		CPP_RunButton->GetOnClickedDelegate().AddUObject(this, &UMS_NormalAndConstructModeWidget::OnClickedRunButton);
	}

	if(CPP_ExitButton)
	{
		CPP_ExitButton->GetOnClickedDelegate().AddUObject(this, &UMS_NormalAndConstructModeWidget::OnClickedExitButton);
	}
}

void UMS_NormalAndConstructModeWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMS_NormalAndConstructModeWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UMS_NormalAndConstructModeWidget::OnClickedRunButton()
{
	EMS_ModeState ModeState = gModeMng.GetCurrentModeStateId();
	if (ModeState != EMS_ModeState::Normal)
	{
		return;
	}

	FMS_ModalParameter ModalParameter;
	ModalParameter.InModalWidget = gWidgetMng.Create_Widget_NotManaging(UMS_MarketStartModal::GetWidgetPath());
	gWidgetMng.ShowModalWidget(ModalParameter);
}

void UMS_NormalAndConstructModeWidget::OnClickedExitButton()
{
	EMS_ModeState ModeState = gModeMng.GetCurrentModeStateId();
	if (ModeState == EMS_ModeState::Normal)
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
	else
	{
		gModeMng.ChangeState(EMS_ModeState::Normal);
	}
}

void UMS_NormalAndConstructModeWidget::OnChangeMode(EMS_ModeState aModeState)
{
	Super::OnChangeMode(aModeState);
	
	if (aModeState == EMS_ModeState::Normal)
	{
		CPP_RunButton->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		CPP_RunButton->SetVisibility(ESlateVisibility::Collapsed);
	}
}
