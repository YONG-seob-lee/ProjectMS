﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_LogoWidget.h"

#include "MS_AccountWidget.h"
#include "MS_Define.h"
#include "Button/MS_Button.h"
#include "Manager_Client/MS_SceneManager.h"

void UMS_LogoWidget::InitWidget(const FName& aTypeName, bool bManaged, bool bActivate)
{
	Super::InitWidget(aTypeName, bManaged, bActivate);

	CPP_SkipButton->GetOnClickedDelegate().AddUObject(this, &UMS_LogoWidget::OnClickSkipButton);
}

void UMS_LogoWidget::FinishWidget()
{
	Super::FinishWidget();
}

void UMS_LogoWidget::OnAnimFinished(const FName& aAnimName)
{
	Super::OnAnimFinished(aAnimName);

	if(aAnimName == DefaultWidgetAnimation::Appearance)
	{
		PlayAnimationByName(DefaultWidgetAnimation::Idle);
	}
	else if(aAnimName == DefaultWidgetAnimation::Idle)
	{
		PlayAnimationByName(DefaultWidgetAnimation::DisAppearance);
		CPP_SkipButton->GetOnClickedDelegate().RemoveAll(this);
	}
	else if(aAnimName == DefaultWidgetAnimation::DisAppearance)
	{
		
		CREATE_SCENE_COMMAND(Command);
		Command->SetFadeOutTransitionType(EMS_TransitionStyle::Undefined);
		Command->SetFadeInTransitionType(EMS_TransitionStyle::Undefined);
		Command->SetNextWidget(UMS_AccountWidget::GetWidgetName());
		gSceneMng.RequestChangeScene(Command);
	}
}

void UMS_LogoWidget::OnClickSkipButton()
{
	if(IsPlayingAnimation())
	{
		StopAllAnimations();
	}
}
