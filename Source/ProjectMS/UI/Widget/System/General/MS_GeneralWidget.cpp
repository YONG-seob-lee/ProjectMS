// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_GeneralWidget.h"

#include "Button/MS_DefaultButton.h"
#include "Button/MS_GeneralButton.h"
#include "Components/CanvasPanel.h"
#include "Manager_Client/MS_ItemManager.h"
#include "Manager_Client/MS_ScheduleManager.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "Table/Caches/MS_MenuElementCacheTable.h"
#include "Table/Caches/MS_TutorialCacheTable.h"
#include "Widget/ListViewElement/ElementData/MS_MenuElementData.h"
#include "Widget/Staff/Modal/MS_HireStaffWidget.h"
#include "Widget/Staff/Modal/MS_StaffManagementWidget.h"
#include "Widget/Customer/Modal/MS_CustomerManagementWidget.h"
#include "Widget/Finance/Modal/MS_FinancialManagementWidget.h"
#include "Widget/Market/BuyThings/MS_BuyFurnitureWidget.h"
#include "Widget/Market/Modal/MS_MarketOrderCheckModalWidget.h"
#include "Widget/Market/Modal/MS_MarketOrderModalWidget.h"
#include "Widget/Schedule/Modal/MS_ScheduleModalWidget.h"
#include "Widget/System/Settings/Modal/MS_SettingModalWidget.h"
#include "Widget/WidgetComponent/MS_TileView.h"

void UMS_GeneralWidget::NativeConstruct()
{
	Super::NativeConstruct();

	FillDefaultAnimations();

	CPP_LeftButton->SetVisibility(ESlateVisibility::Visible);
	CPP_LeftButton->GetOnClickedDelegate().AddUObject(this, &UMS_GeneralWidget::OnClickedLeftButton);
	CPP_RightButton->SetVisibility(ESlateVisibility::Visible);
	CPP_RightButton->GetOnClickedDelegate().AddUObject(this, &UMS_GeneralWidget::OnClickedRightButton);
	CPP_ExpanderButton->GetOnClickedDelegate().AddUObject(this, &UMS_GeneralWidget::OnClickedExpanderButton);

	InitLeftExpander();
}

void UMS_GeneralWidget::SetType(EMS_GeneralWidgetType aType)
{
	switch (aType)
	{
	case EMS_GeneralWidgetType::Lobby:
		{
			CPP_LeftPanel->SetVisibility(ESlateVisibility::Collapsed);
			CPP_RightPanel->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			CPP_RightButton->SetButtonType(EMS_GeneralButtonType::Setting);
			RightButtonType = EMS_GeneralButtonType::Setting;
			CPP_MenuExpanderPanel->SetVisibility(ESlateVisibility::Collapsed);
			break;
		}
	case EMS_GeneralWidgetType::Town:
		{
			CPP_LeftPanel->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			CPP_RightPanel->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			CPP_LeftButton->SetButtonType(EMS_GeneralButtonType::Schedule);
			CPP_RightButton->SetButtonType(EMS_GeneralButtonType::Menu);
			LeftButtonType = EMS_GeneralButtonType::Schedule;
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
			CPP_LeftPanel->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			CPP_RightPanel->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			CPP_LeftButton->SetButtonType(EMS_GeneralButtonType::Manage);
			CPP_RightButton->SetButtonType(EMS_GeneralButtonType::Menu);
			LeftButtonType = EMS_GeneralButtonType::Manage;
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

void UMS_GeneralWidget::InitLeftExpander()
{
	CPP_LeftExpanderPanel->SetVisibility(ESlateVisibility::Collapsed);
	if(CPP_LeftExpanderButton01)
	{		
		CPP_LeftExpanderButton01->SetButtonType(EMS_GeneralButtonType::OrderItem);
		CPP_LeftExpanderButton01->GetOnClickedDelegate().AddUObject(this, &UMS_GeneralWidget::OnClickedOrderItemButton);
	}
	if(CPP_LeftExpanderButton02)
	{
		CPP_LeftExpanderButton02->SetButtonType(EMS_GeneralButtonType::CheckOrderItem);
		CPP_LeftExpanderButton02->GetOnClickedDelegate().AddUObject(this, &UMS_GeneralWidget::OnClickedCheckOrderButton);
	}
	if(CPP_LeftExpanderButton03)
	{
		CPP_LeftExpanderButton03->SetButtonType(EMS_GeneralButtonType::OrderFurniture);
		CPP_LeftExpanderButton03->GetOnClickedDelegate().AddUObject(this, &UMS_GeneralWidget::OnClickedOrderFurnitureButton);
	}
	if(CPP_LeftExpanderButton04)
	{
		CPP_LeftExpanderButton04->SetButtonType(EMS_GeneralButtonType::HireStaff);
		CPP_LeftExpanderButton04->GetOnClickedDelegate().AddUObject(this, &UMS_GeneralWidget::OnClickedHireStaffButton);
	}
	if(CPP_LeftExpanderButton05)
	{
		CPP_LeftExpanderButton05->SetButtonType(EMS_GeneralButtonType::StaffManage);
		CPP_LeftExpanderButton05->GetOnClickedDelegate().AddUObject(this, &UMS_GeneralWidget::OnClickedManageStaffButton);
	}
	if(CPP_LeftExpanderButton06)
	{
		CPP_LeftExpanderButton06->SetButtonType(EMS_GeneralButtonType::CustomerManage);
		CPP_LeftExpanderButton06->GetOnClickedDelegate().AddUObject(this, &UMS_GeneralWidget::OnClickedManageCustomerButton);
	}
	if(CPP_LeftExpanderButton07)
	{
		CPP_LeftExpanderButton07->SetButtonType(EMS_GeneralButtonType::SalesDetail);
		CPP_LeftExpanderButton07->GetOnClickedDelegate().AddUObject(this, &UMS_GeneralWidget::OnClickedFinancialIndicatorButton);
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
		OpenLeftExpander();
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

void UMS_GeneralWidget::OnClickedExpanderButton()
{
	FMS_ModalParameter Parameter;
	Parameter.InModalWidget = gWidgetMng.Create_Widget(UMS_SettingModalWidget::GetWidgetName());
	gWidgetMng.ShowModalWidget(Parameter);
	CPP_MenuExpanderPanel->SetVisibility(ESlateVisibility::Collapsed);
}

void UMS_GeneralWidget::OnClickedOrderItemButton()
{
	if(gItemMng.IsAvailablePurchase() == false)
	{
		gWidgetMng.ShowToastMessage(TEXT("이용 가능한 시간대가 아닙니다."));
		return;
	}
	
	FMS_ModalParameter Parameter;
	Parameter.InModalWidget = gWidgetMng.Create_Widget_NotManaging(UMS_MarketOrderModalWidget::GetWidgetPath());
	gWidgetMng.ShowModalWidget(Parameter);

	CPP_LeftExpanderPanel->SetVisibility(ESlateVisibility::Collapsed);
}

void UMS_GeneralWidget::OnClickedCheckOrderButton()
{
	FMS_ModalParameter Parameter;
	Parameter.InModalWidget = gWidgetMng.Create_Widget_NotManaging(UMS_MarketOrderCheckModalWidget::GetWidgetPath());
	gWidgetMng.ShowModalWidget(Parameter);

	CPP_LeftExpanderPanel->SetVisibility(ESlateVisibility::Collapsed);
}

void UMS_GeneralWidget::OnClickedOrderFurnitureButton()
{
	if(gItemMng.IsAvailablePurchase() == false)
	{
		gWidgetMng.ShowToastMessage(TEXT("이용 가능한 시간대가 아닙니다."));
		return;
	}
	
	FMS_ModalParameter Parameter;
	Parameter.InModalWidget = gWidgetMng.Create_Widget(UMS_BuyFurnitureWidget::GetWidgetName());
	gWidgetMng.ShowModalWidget(Parameter);

	CPP_LeftExpanderPanel->SetVisibility(ESlateVisibility::Collapsed);
}

void UMS_GeneralWidget::OnClickedHireStaffButton()
{
	FMS_ModalParameter Parameter;
	Parameter.InModalWidget = gWidgetMng.Create_Widget(UMS_HireStaffWidget::GetWidgetName());
	gWidgetMng.ShowModalWidget(Parameter);

	CPP_LeftExpanderPanel->SetVisibility(ESlateVisibility::Collapsed);
}

void UMS_GeneralWidget::OnClickedManageStaffButton()
{
	FMS_ModalParameter Parameter;
	Parameter.InModalWidget = gWidgetMng.Create_Widget(UMS_StaffManagementWidget::GetWidgetName());
	gWidgetMng.ShowModalWidget(Parameter);
	
	CPP_LeftExpanderPanel->SetVisibility(ESlateVisibility::Collapsed);
}

void UMS_GeneralWidget::OnClickedManageCustomerButton()
{
	FMS_ModalParameter Parameter;
	Parameter.InModalWidget = gWidgetMng.Create_Widget(UMS_CustomerManagementWidget::GetWidgetName());
	gWidgetMng.ShowModalWidget(Parameter);

	CPP_LeftExpanderPanel->SetVisibility(ESlateVisibility::Collapsed);
}

void UMS_GeneralWidget::OnClickedFinancialIndicatorButton()
{
	FMS_ModalParameter Parameter;
	Parameter.InModalWidget = gWidgetMng.Create_Widget(UMS_FinancialManagementWidget::GetWidgetName());
	gWidgetMng.ShowModalWidget(Parameter);

	CPP_LeftExpanderPanel->SetVisibility(ESlateVisibility::Collapsed);
}

void UMS_GeneralWidget::OpenLeftExpander() const
{
	CPP_LeftExpanderPanel->SetVisibility(CPP_LeftExpanderPanel->IsVisible() ? ESlateVisibility::Collapsed : ESlateVisibility::SelfHitTestInvisible);
}
