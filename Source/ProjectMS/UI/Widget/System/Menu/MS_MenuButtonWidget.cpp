// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_MenuButtonWidget.h"

#include "Button/MS_Button.h"
#include "Components/CanvasPanel.h"
#include "Manager_Both/MS_TableManager.h"
#include "Widget/ListViewElement/ElementData/MS_MenuElementData.h"
#include "Widget/WidgetComponent/MS_TileView.h"

void UMS_MenuButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if(CPP_MenuButton)
	{
		CPP_MenuButton->GetOnClickedDelegate().AddUObject(this, &UMS_MenuButtonWidget::OnClickSettingButton);
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
		CPP_MenuExpanderPanel->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
}
