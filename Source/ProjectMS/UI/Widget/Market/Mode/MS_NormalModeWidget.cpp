// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_NormalModeWidget.h"

#include "Button/MS_Button.h"
#include "Manager_Both/MS_UnitManager.h"
#include "Manager_Client/MS_ModeManager.h"
#include "Manager_Client/MS_PlayerCameraManager.h"
#include "Manager_Client/MS_SceneManager.h"
#include "Manager_Client/MS_ScheduleManager.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "Widget/Market/Modal/MS_MarketStartModal.h"
#include "Widget/WidgetComponent/MS_WidgetSwitcher.h"

namespace ButtonType
{
	constexpr int32 Open = 0;
	constexpr int32 Close = 1;
}

void UMS_NormalModeWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if(CPP_TownButton)
	{
		CPP_TownButton->GetOnClickedDelegate().AddUObject(this, &UMS_NormalModeWidget::OnClickedTownButton);
	}
	if(CPP_ConstructButton)
	{
		CPP_ConstructButton->GetOnClickedDelegate().AddUObject(this, &UMS_NormalModeWidget::OnClickedConstructButton);
	}

	if(CPP_OpenButton)
	{
		CPP_OpenButton->GetOnClickedDelegate().AddUObject(this, &UMS_NormalModeWidget::OnClickedOpenMarketButton);
	}
	if(CPP_CloseButton)
	{
		CPP_CloseButton->GetOnClickedDelegate().AddUObject(this, &UMS_NormalModeWidget::OnClickedCloseMarketButton);
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
	Command->SetLevelType(EMS_LevelType::Stage01, GetWorld());
	Command->SetPreviousLevelType(EMS_LevelType::MarketLevel);
	Command->SetFadeOutTransitionType(EMS_TransitionStyle::GradationOut);
	Command->SetFadeInTransitionType(EMS_TransitionStyle::GradationIn);
	Command->SetFadeAnimationType(EMS_FadeAnimationCurveType::Linear);
	Command->SetLoadingWidgetType(EMS_LoadingWidgetType::Default);
	Command->OnFadeInFinishedCallback =  []
	{
		FViewTargetTransitionParams Param;
		Param.BlendTime = 0.f;
		gCameraMng.SwitchViewCamera(EMS_ViewCameraType::QuarterView, Param);
	};
	gSceneMng.RequestChangeScene(Command);
}

void UMS_NormalModeWidget::OnClickedConstructButton()
{
	gModeMng.ChangeState(EMS_ModeState::Construct);
}

void UMS_NormalModeWidget::OnClickedOpenMarketButton()
{
	FMS_ModalParameter ModalParameter;
	ModalParameter.InModalWidget = gWidgetMng.Create_Widget_NotManaging(UMS_MarketStartModal::GetWidgetPath());
	gWidgetMng.ShowModalWidget(ModalParameter);
}

void UMS_NormalModeWidget::OnClickedCloseMarketButton()
{
	const FMS_GameDate& GameDate = gScheduleMng.GetGameDate();
	if (FMS_GameDate::IsNight(GameDate.DailyTimeZone))
	{
		// Town으로 이동
		CREATE_SCENE_COMMAND(Command);
		Command->SetLevelType(EMS_LevelType::Stage01, GetWorld());
		Command->SetPreviousLevelType(EMS_LevelType::MarketLevel);
		Command->SetFadeOutTransitionType(EMS_TransitionStyle::GradationOut);
		Command->SetFadeInTransitionType(EMS_TransitionStyle::GradationIn);
		Command->SetFadeAnimationType(EMS_FadeAnimationCurveType::Linear);
		Command->SetLoadingWidgetType(EMS_LoadingWidgetType::Default);
		Command->OnFadeInFinishedCallback =  []
		{
			FViewTargetTransitionParams Param;
			Param.BlendTime = 0.f;
			gCameraMng.SwitchViewCamera(EMS_ViewCameraType::QuarterView, Param);
		};
		gSceneMng.RequestChangeScene(Command);
	}
}

void UMS_NormalModeWidget::OnChangeMode(EMS_ModeState aModeState)
{
	Super::OnChangeMode(aModeState);

	if(aModeState == EMS_ModeState::Normal)
	{
		const FMS_GameDate& GameDate = gScheduleMng.GetGameDate();
		if (FMS_GameDate::IsNight(GameDate.DailyTimeZone))
		{
			CPP_PlayButtonSwitcher->SetActiveWidgetIndex(ButtonType::Close);
			CPP_TownButton->SetVisibility(ESlateVisibility::Collapsed);	
		}
		else
		{
			CPP_PlayButtonSwitcher->SetActiveWidgetIndex(ButtonType::Open);
			CPP_TownButton->SetVisibility(ESlateVisibility::Visible);	
		}
	}
}
