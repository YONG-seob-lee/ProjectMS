// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_TownWidget.h"

#include "Manager_Both/MS_ModeManager.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "Widget/System/MS_ContentsPartWidget.h"

void UMS_TownWidget::NativeConstruct()
{
	Super::NativeConstruct();

	gModeMng.OnChangeModeDelegate.AddUObject(this, &UMS_TownWidget::OnChangeMode);

	PlayAnimationByName(ModePanelAnimation::SetMode);

	if(CPP_ContentsPart)
	{
		CPP_ContentsPart->SetOnClickMarketButtonFunc([this]()
		{
			StopAllAnimations();
		});
	}
}

void UMS_TownWidget::OnAnimFinished(const FName& aAnimName)
{
	Super::OnAnimFinished(aAnimName);
	
	if(aAnimName == ModePanelAnimation::SetMode)
	{
		PlayAnimationByName(ModePanelAnimation::IdleMode);
	}
	else if(aAnimName == ModePanelAnimation::IdleMode)
	{
		PlayAnimationByName(ModePanelAnimation::UnSetMode);
	}
	else if(aAnimName == ModePanelAnimation::UnSetMode)
	{
		IsShowModePanel = false;
	}
}

void UMS_TownWidget::OnClickedDefaultButton()
{
	gWidgetMng.ShowToastMessage(TEXT(""));
}

void UMS_TownWidget::OnChangeMode(EMS_ModeState aMode, EMS_ControllerModeType)
{
	if(IsShowModePanel == true)
	{
		return;
	}
	
	PlayAnimationByName(ModePanelAnimation::SetMode);
	IsShowModePanel = true;
}