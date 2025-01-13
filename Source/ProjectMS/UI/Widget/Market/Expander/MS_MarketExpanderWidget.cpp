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
	PlayAnimationByName(ArrowAnimation::OpenMode);
	CPP_ModeSelectWidget->SwitchWidget(aModeState);
}

void UMS_MarketExpanderWidget::OnClickedArrowButton()
{
	EMS_ModeState ModeState = gModeMng.GetCurrentModeStateId();
	
	if(ModeState != EMS_ModeState::Normal)
	{
		PlayAnimationByName(ArrowAnimation::CloseMode);
		ModeState = EMS_ModeState::Normal;
		CPP_ModeSelectWidget->SwitchWidget(EMS_ModeState::Normal);
		bOpen = false;
		return;
	}
	
	if(bOpen)
	{
		PlayAnimationByName(ArrowAnimation::Close);
	}
	else
	{
		PlayAnimationByName(ArrowAnimation::Open);
	}

	bOpen = !bOpen;
}
