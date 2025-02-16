// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_MarketExpanderWidget.h"

#include "MS_ModeSelectWidget.h"
#include "Button/MS_Button.h"

namespace ArrowAnimation
{
	const FName Open = TEXT("Open");
	const FName Close = TEXT("Close");
	const FName OpenMode = TEXT("OpenMode");
	const FName CloseMode = TEXT("CloseMode");
}

void UMS_MarketExpanderWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	gModeMng.OnChangeModeDelegate.AddUObject(this, &UMS_MarketExpanderWidget::OnChangeModeState);
}

void UMS_MarketExpanderWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	FillDefaultAnimations();

	if(CPP_ModeSelectWidget)
	{
		CPP_ModeSelectWidget->GetOnClickedModeButtonFunc([this](EMS_ModeState aModeState)
		{
			gModeMng.ChangeState(aModeState);
		});
	}

	if(CPP_ArrowButton)
	{
		CPP_ArrowButton->GetOnClickedDelegate().AddUObject(this, &UMS_MarketExpanderWidget::OnClickedArrowButton);
		CPP_ArrowButton->SetVisibility(ESlateVisibility::Visible);
	}
}

void UMS_MarketExpanderWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UMS_MarketExpanderWidget::OnChangeModeState(EMS_ModeState aModeState, EMS_ControllerModeType aControllerModeType)
{
	// TODO 용섭 : 나중에 모드 완성되면 추가 작업
	if (aModeState == EMS_ModeState::Construct)
	{
		if(bOpen && bOpenExpander)
		{
			return;
		}
	
		PlayAnimationByName(ArrowAnimation::OpenMode);
		bOpen = true;
		bOpenExpander = true;
	}
	else
	{
		if(!bOpen && !bOpenExpander)
		{
			return;
		}
		
		PlayAnimationByName(ArrowAnimation::Close);
		bOpen = false;
		bOpenExpander = false;
	}
}

void UMS_MarketExpanderWidget::OnClickedArrowButton()
{
	if(bOpen)
	{
		if(bOpenExpander)
		{
			PlayAnimationByName(ArrowAnimation::CloseMode);
			bOpenExpander = false;
		}
		else
		{
			PlayAnimationByName(ArrowAnimation::Close);
		}
		bOpen = false;
	}
	else
	{
		PlayAnimationByName(ArrowAnimation::Open);
		bOpen = true;
	}
}
