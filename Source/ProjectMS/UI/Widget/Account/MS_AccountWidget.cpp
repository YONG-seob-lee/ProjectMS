// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_AccountWidget.h"

#include "MS_Define.h"
#include "Button/MS_AccountButton.h"
#include "Button/MS_AccountStartButton.h"
#include "Manager_Client/MS_SceneManager.h"
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
	CREATE_SCENE_COMMAND(Command);
	// TODO : all : 서버 데이터에서 클리어한 위치를 찾아서 레벨 타입 적용.
	Command->SetLevelType(EMS_LevelType::Stage01);
	Command->SetPreviousLevelType(EMS_LevelType::AccountLevel);
	Command->SetFadeOutTransitionType(EMS_TransitionStyle::GradationOut);
	Command->SetFadeInTransitionType(EMS_TransitionStyle::GradationIn);
	Command->SetFadeAnimationType(EMS_FadeAnimationCurveType::Linear);
	Command->SetLoadingWidgetType(EMS_LoadingWidgetType::Default);

	gSceneMng.RequestChangeScene(Command);
}
