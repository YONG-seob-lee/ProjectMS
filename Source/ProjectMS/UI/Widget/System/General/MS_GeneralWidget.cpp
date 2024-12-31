// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_GeneralWidget.h"

#include "Button/MS_GeneralButton.h"
#include "Components/CanvasPanel.h"
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

				TArray<TObjectPtr<UMS_MenuElementData>> Elements;
				MenuElement->GetMenuData(Elements);
				CPP_MenuTileView->SetListItems(TArray<UObject*>(Elements));
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
		gWidgetMng.ShowModalWidget(nullptr, true);
	}
	else if(LeftButtonType ==EMS_GeneralButtonType::Manage)
	{
		gWidgetMng.ShowModalWidget(nullptr, true);
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
		gWidgetMng.ShowModalWidget(nullptr, true);
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

void UMS_GeneralWidget::OnClickedExpanderButton()
{
	gWidgetMng.ShowModalWidget(nullptr, true);
}
