// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_TownWidget.h"

#include "MS_ModeManager.h"
#include "MS_WidgetManager.h"
#include "Widget/System/MS_ContentsPartWidget.h"

void UMS_TownWidget::NativeConstruct()
{
	Super::NativeConstruct();

	gModeMng.OnSetMode.AddUObject(this, &UMS_TownWidget::OnSetMode);

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
		GetWorld()->GetTimerManager().SetTimer(OnSetTimerHandle, [this]
		{
			PlayAnimationByName(ModePanelAnimation::UnSetMode);
		}, 3.f, false);	
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

void UMS_TownWidget::OnSetMode(uint8 aMode)
{
	if(IsShowModePanel == true)
	{
		return;
	}
	
	PlayAnimationByName(ModePanelAnimation::SetMode);
	IsShowModePanel = true;
}