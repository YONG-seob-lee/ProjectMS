// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_GeneralWidget.h"

#include "MS_GeneralLeftExpanderWidget.h"
#include "MS_GeneralRightExpanderWidget.h"
#include "MS_MoneyWidget.h"
#include "Button/MS_DefaultButton.h"
#include "Button/MS_GeneralButton.h"
#include "Components/CanvasPanel.h"
#include "Manager_Client/MS_ItemManager.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "Table/Caches/MS_TutorialCacheTable.h"
#include "Widget/Schedule/Modal/MS_ScheduleModalWidget.h"
#include "Widget/System/Settings/Modal/MS_SettingModalWidget.h"
#include "Widget/WidgetComponent/MS_TileView.h"

void UMS_GeneralWidget::NativeConstruct()
{
	Super::NativeConstruct();

	FillDefaultAnimations();
	
	CPP_LeftButton->GetOnClickedDelegate().AddUObject(this, &UMS_GeneralWidget::OnClickedLeftButton);
	CPP_RightButton->GetOnClickedDelegate().AddUObject(this, &UMS_GeneralWidget::OnClickedRightButton);

	CPP_LeftExpanderWidget->SetVisibility(ESlateVisibility::Collapsed);
	CPP_RightExpanderWidget->SetVisibility(ESlateVisibility::Collapsed);

	InitializeGeneralWidgetType();
}

void UMS_GeneralWidget::InitializeGeneralWidgetType()
{
	switch (GeneralWidgetType)
	{
	case EMS_GeneralWidgetType::Town:
		{
			CPP_LeftPanel->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			CPP_RightPanel->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			CPP_MoneyWidget->SetVisibility(ESlateVisibility::Collapsed);
			
			CPP_LeftButton->SetButtonType(EMS_GeneralButtonType::Schedule);
			CPP_RightButton->SetButtonType(EMS_GeneralButtonType::Setting);
			LeftButtonType = EMS_GeneralButtonType::Schedule;
			RightButtonType = EMS_GeneralButtonType::Setting;
			CPP_RightExpanderWidget->UpdateButton();
			break;
		}
	case EMS_GeneralWidgetType::Market:
		{
			CPP_LeftPanel->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			CPP_RightPanel->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			
			CPP_LeftButton->SetButtonType(EMS_GeneralButtonType::Manage);
			CPP_RightButton->SetButtonType(EMS_GeneralButtonType::Setting);
			CPP_MoneyWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			LeftButtonType = EMS_GeneralButtonType::Manage;
			RightButtonType = EMS_GeneralButtonType::Setting;
			CPP_RightExpanderWidget->UpdateButton();
			break;
		}
	default:
		{
			CPP_LeftPanel->SetVisibility(ESlateVisibility::Collapsed);
			CPP_RightPanel->SetVisibility(ESlateVisibility::Collapsed);
			CPP_MoneyWidget->SetVisibility(ESlateVisibility::Collapsed);
			RightButtonType = EMS_GeneralButtonType::None;
			break;
		}
	}
}

void UMS_GeneralWidget::OnClickedLeftButton()
{
	if(LeftButtonType == EMS_GeneralButtonType::Schedule)
	{
		if(CPP_LeftButton->CheckIsTutorialFinished(EMS_TutorialType::Schedule) == false)
		{
			return;
		}
		
		FMS_ModalParameter Parameter;
		Parameter.InModalWidget = gWidgetMng.Create_Widget(UMS_ScheduleModalWidget::GetWidgetName());
		gWidgetMng.ShowModalWidget(Parameter);
	}
	else if(LeftButtonType ==EMS_GeneralButtonType::Manage)
	{
		if(CPP_LeftButton->CheckIsTutorialFinished(EMS_TutorialType::Manage) == false)
		{
			return;
		}

		if (CPP_LeftExpanderWidget->GetVisibility() != ESlateVisibility::SelfHitTestInvisible)
		{
			CPP_LeftExpanderWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		}
		else
		{
			CPP_LeftExpanderWidget->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
	else
	{
		gWidgetMng.ShowToastMessage(TEXT(""));
	}
}

void UMS_GeneralWidget::OnClickedRightButton()
{
	if(RightButtonType == EMS_GeneralButtonType::Setting)
	{
		FMS_ModalParameter Parameter;
		Parameter.InModalWidget = gWidgetMng.Create_Widget(UMS_SettingModalWidget::GetWidgetName());
		gWidgetMng.ShowModalWidget(Parameter);
	}
	else if(RightButtonType == EMS_GeneralButtonType::Menu)
	{
		if(CPP_RightExpanderWidget->IsVisible())
		{
			CPP_RightExpanderWidget->SetVisibility(ESlateVisibility::Collapsed);
		}
		else
		{
			CPP_RightExpanderWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}
	else
	{
		gWidgetMng.ShowToastMessage(TEXT(""));
	}
}