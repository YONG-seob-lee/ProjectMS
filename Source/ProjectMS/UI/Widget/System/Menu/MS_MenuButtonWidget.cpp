// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_MenuButtonWidget.h"

#include "Button/MS_Button.h"
#include "Components/CanvasPanel.h"
#include "Manager_Client/MS_WidgetManager.h"

void UMS_MenuButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if(CPP_SettingButton)
	{
		CPP_SettingButton->GetOnClickedDelegate().AddUObject(this, &UMS_MenuButtonWidget::OnClickSettingButton);
	}

	CPP_MenuExpanderPanel->SetVisibility(ESlateVisibility::Collapsed);
}

void UMS_MenuButtonWidget::OnClickSettingButton()
{
	if(CPP_MenuExpanderPanel->IsVisible())
	{
		CPP_MenuExpanderPanel->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		CPP_MenuExpanderPanel->SetVisibility(ESlateVisibility::Visible);
	}
}
