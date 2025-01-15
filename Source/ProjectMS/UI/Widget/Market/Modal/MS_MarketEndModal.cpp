// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_MarketEndModal.h"

#include "MS_Define.h"
#include "Button/MS_Button.h"
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

	gScheduleMng.TransferServer();
	
	CREATE_SCENE_COMMAND(Command);
	Command->SetLevelType(EMS_LevelType::Stage01);
	Command->SetPreviousLevelType(EMS_LevelType::MarketLevel);
	Command->SetFadeOutTransitionType(EMS_TransitionStyle::GradationOut);
	Command->SetFadeInTransitionType(EMS_TransitionStyle::GradationIn);
	Command->SetFadeAnimationType(EMS_FadeAnimationCurveType::Linear);
	Command->SetLoadingWidgetType(EMS_LoadingWidgetType::Default);
	Command->SetNextWidget(TEXT("DoNotCreateNextWidget"));
	gSceneMng.OnFadeFinishedEventDelegate.AddWeakLambda(this, [this]
	{
		FViewTargetTransitionParams Param;
		Param.BlendTime = 1.f;
		gCameraMng.SwitchViewCamera(EMS_ViewCameraType::QuarterView, Param);
		gSceneMng.OnFadeFinishedEventDelegate.RemoveAll(this);
	});
	gSceneMng.RequestChangeScene(Command);
}
