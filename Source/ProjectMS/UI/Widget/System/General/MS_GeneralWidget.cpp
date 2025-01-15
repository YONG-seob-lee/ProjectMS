// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_GeneralWidget.h"

#include "MS_TimeLineWidget.h"
#include "Button/MS_GeneralButton.h"
#include "Components/CanvasPanel.h"
#include "Manager_Client/MS_ScheduleManager.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "Table/Caches/MS_MenuElementCacheTable.h"
#include "Widget/ListViewElement/ElementData/MS_MenuElementData.h"
#include "Widget/WidgetComponent/MS_TileView.h"

void UMS_GeneralWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CPP_LeftButton->SetVisibility(ESlateVisibility::Visible);
	CPP_LeftButton->GetOnClickedDelegate().AddUObject(this, &UMS_GeneralWidget::OnClickedLeftButton);
	CPP_RightButton->SetVisibility(ESlateVisibility::Visible);
	CPP_RightButton->GetOnClickedDelegate().AddUObject(this, &UMS_GeneralWidget::OnClickedRightButton);

	gScheduleMng.OnUpdateScheduleDelegate.AddUObject(this, &UMS_GeneralWidget::OnUpdateTimer);
	gScheduleMng.OnUpdateMinuteDelegate.AddUObject(this, &UMS_GeneralWidget::OnUpdateMinute);
}

void UMS_GeneralWidget::SetType(EMS_GeneralWidgetType aType)
{
	switch (aType)
	{
	case EMS_GeneralWidgetType::Lobby:
		{
			CPP_LeftPanel->SetVisibility(ESlateVisibility::Collapsed);
			CPP_RightPanel->SetVisibility(ESlateVisibility::Visible);
			CPP_RightButton->SetButtonType(EMS_GeneralButtonType::Setting);
			RightButtonType = EMS_GeneralButtonType::Setting;
			CPP_MenuExpanderPanel->SetVisibility(ESlateVisibility::Collapsed);
			break;
		}
	case EMS_GeneralWidgetType::Town:
		{
			CPP_LeftPanel->SetVisibility(ESlateVisibility::Visible);
			CPP_RightPanel->SetVisibility(ESlateVisibility::Visible);
			CPP_LeftButton->SetButtonType(EMS_GeneralButtonType::Schedule);
			CPP_RightButton->SetButtonType(EMS_GeneralButtonType::Menu);
			RightButtonType = EMS_GeneralButtonType::Menu;
			CPP_MenuExpanderPanel->SetVisibility(ESlateVisibility::Collapsed);
			CPP_ExpanderButton->SetButtonType(EMS_GeneralButtonType::Setting);
			
			if(CPP_MenuTileView)
			{
				const TObjectPtr<UMS_MenuElementCacheTable> MenuElement = Cast<UMS_MenuElementCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::MenuElement));
				MS_CHECK(MenuElement);

				TArray<TObjectPtr<UMS_MenuElementData>> MenuElementDatas;
				MenuElement->GetMenuData(MenuElementDatas);
				CPP_MenuTileView->SetListItems(TArray<UObject*>(MenuElementDatas));
				for(const auto& MenuElementData : MenuElementDatas)
				{
					MenuElementData->OnClickMenuElementDelegate.AddUObject(this, &UMS_GeneralWidget::OnClickedMenuElementButton);
				}
				
			}
			break;
		}
	case EMS_GeneralWidgetType::Market:
		{
			CPP_LeftPanel->SetVisibility(ESlateVisibility::Visible);
			CPP_RightPanel->SetVisibility(ESlateVisibility::Visible);
			CPP_LeftButton->SetButtonType(EMS_GeneralButtonType::Manage);
			CPP_RightButton->SetButtonType(EMS_GeneralButtonType::Menu);
			RightButtonType = EMS_GeneralButtonType::Menu;
			CPP_MenuExpanderPanel->SetVisibility(ESlateVisibility::Collapsed);
			CPP_ExpanderButton->SetButtonType(EMS_GeneralButtonType::Setting);
			
			if(CPP_MenuTileView)
			{
				const TObjectPtr<UMS_MenuElementCacheTable> MenuElement = Cast<UMS_MenuElementCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::MenuElement));
				MS_CHECK(MenuElement);

				TArray<TObjectPtr<UMS_MenuElementData>> Elements;
				MenuElement->GetMenuData(Elements);
				CPP_MenuTileView->SetListItems(TArray<UObject*>(Elements));
			}
			break;
		}
	default:
		{
			CPP_LeftPanel->SetVisibility(ESlateVisibility::Collapsed);
			CPP_RightPanel->SetVisibility(ESlateVisibility::Collapsed);
			CPP_MenuExpanderPanel->SetVisibility(ESlateVisibility::Collapsed);
			RightButtonType = EMS_GeneralButtonType::None;
			break;
		}
	}
}

void UMS_GeneralWidget::OnClickedLeftButton()
{
	if(LeftButtonType == EMS_GeneralButtonType::Schedule)
	{
		gWidgetMng.ShowModalWidget();
	}
	else if(LeftButtonType ==EMS_GeneralButtonType::Manage)
	{
		gWidgetMng.ShowModalWidget();
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
		gWidgetMng.ShowModalWidget();
	}
	else if(RightButtonType == EMS_GeneralButtonType::Menu)
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
	else
	{
		gWidgetMng.ShowToastMessage(TEXT(""));
	}
}

void UMS_GeneralWidget::OnClickedMenuElementButton()
{
	CPP_MenuExpanderPanel->SetVisibility(ESlateVisibility::Collapsed);
}

void UMS_GeneralWidget::OnUpdateTimer(int32 ScheduleType)
{
	switch(static_cast<EMS_ScheduleType>(ScheduleType))
	{
	case EMS_ScheduleType::Prepare:
	case EMS_ScheduleType::Deadline:
		{
			CPP_TimeLineWidget->IsStartTimer(false);
			break;
		}
	case EMS_ScheduleType::UpAndDown:
	case EMS_ScheduleType::OpenMarket:
		{
			CPP_TimeLineWidget->IsStartTimer(true);
			break;
		}
		default:
		{
			break;
		}
	}
}

void UMS_GeneralWidget::OnUpdateMinute(int32 aMinute)
{
	if(CPP_TimeLineWidget)
	{
		CPP_TimeLineWidget->UpdateTimer(aMinute);
	}
}
