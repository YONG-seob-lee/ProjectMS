// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_AccountWidget.h"

#include "MS_Define.h"
#include "MS_SceneManager.h"
#include "Button/MS_AccountButton.h"
#include "Button/MS_AccountStartButton.h"
#include "Controller/MS_PlayerController.h"
#include "Widget/WidgetComponent/MS_WidgetSwitcher.h"

namespace ButtonIndex
{
	constexpr int32 Google = 0;
	constexpr int32 Start = 1;
}

void UMS_AccountWidget::InitWidget(const FName& aTypeName, bool bManaged, bool bActivate)
{
	Super::InitWidget(aTypeName, bManaged, bActivate);

	if(CPP_AccountButton)
	{
		CPP_AccountButton->GetOnClickedDelegate().AddUObject(this, &UMS_AccountWidget::OnClickAccountButton);
	}

	if(CPP_StartButton)
	{
		CPP_StartButton->GetOnClickedDelegate().AddUObject(this, &UMS_AccountWidget::OnClickStartButton);
	}

	if(CPP_WidgetSwitcher)
	{
		CPP_WidgetSwitcher->SetActiveWidgetIndex(ButtonIndex::Google);
	}
}

void UMS_AccountWidget::OnClickAccountButton()
{
	if(CPP_WidgetSwitcher)
	{
		CPP_WidgetSwitcher->SetActiveWidgetIndex(ButtonIndex::Start);
	}
}

void UMS_AccountWidget::OnClickStartButton()
{
	const TObjectPtr<UWorld> World = GetWorld();
	MS_CHECK(World);

	const TObjectPtr<AMS_PlayerController> PlayerController = World->GetFirstPlayerController<AMS_PlayerController>();
	MS_CHECK(PlayerController);

	const TObjectPtr<AMS_SceneManager> SceneManager = PlayerController->GetSceneManager();
	
	CREATE_SCENE_COMMAND(Command);
	Command->SetLevelType(EMS_LevelType::TownLevel);
	Command->SetPreviousLevelType(EMS_LevelType::AccountLevel);
	Command->SetFadeOutTransitionType(EMS_TransitionStyle::GradationOut);
	Command->SetFadeInTransitionType(EMS_TransitionStyle::GradationIn);
	Command->SetFadeAnimationType(EMS_FadeAnimationCurveType::Linear);
	Command->SetLoadingWidgetType(EMS_LoadingWidgetType::Default);

	SceneManager->RequestChangeScene(Command);
}
