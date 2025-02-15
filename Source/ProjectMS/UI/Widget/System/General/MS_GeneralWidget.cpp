// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_GeneralWidget.h"

#include "MS_TimeLineWidget.h"
#include "Button/MS_DefaultButton.h"
#include "Button/MS_GeneralButton.h"
#include "Components/CanvasPanel.h"
#include "Components/NamedSlot.h"
#include "Manager_Client/MS_ScheduleManager.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "Table/Caches/MS_MenuElementCacheTable.h"
#include "Widget/ListViewElement/ElementData/MS_MenuElementData.h"
#include "Widget/Staff/Modal/MS_HireStaffWidget.h"
#include "Widget/Staff/Modal/MS_StaffManagementWidget.h"
#include "Widget/Customer/Modal/MS_CustomerManagementWidget.h"
#include "Widget/Finance/Modal/MS_FinancialManagementWidget.h"
#include "Widget/Market/BuyThings/MS_BuyFurnitureWidget.h"
#include "Widget/Market/BuyThings/MS_BuyItemWidget.h"
#include "Widget/Schedule/Modal/MS_ScheduleModalWidget.h"
#include "Widget/System/Settings/Modal/MS_SettingModalWidget.h"
#include "Widget/System/Toturial/MS_DescriptionWidget.h"
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
	
	gScheduleMng.OnUpdateScheduleEventDelegate.AddUObject(this, &UMS_GeneralWidget::OnUpdateTimer);

	InitLeftExpander();

	//CPP_NamedSlot->
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
			CPP_LeftPanel->SetVisibility(ESlateVisibility::Visible);
			CPP_RightPanel->SetVisibility(ESlateVisibility::Visible);
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

	if(gScheduleMng.IsNight())
	{
		CPP_TimeLineWidget->StartSleepButtonAnim();
	}
}

void UMS_GeneralWidget::RequestPassTimer() const
{
	CPP_TimeLineWidget->RequestPassTimer();
}

void UMS_GeneralWidget::Test() const
{
	CPP_LeftButton->PlayTutorial(TEXT("해당 대화창은 튜토리얼 및 퀘스트 진행을 위한 창입니다."), TEXT("글루따띠온~"));
}


void UMS_GeneralWidget::InitLeftExpander()
{
	CPP_LeftExpanderPanel->SetVisibility(ESlateVisibility::Collapsed);
	if(CPP_LeftExpanderButton01)
	{
		CPP_LeftExpanderButton01->SetButtonType(EMS_GeneralButtonType::BuyItem);
		CPP_LeftExpanderButton01->GetOnClickedDelegate().AddUObject(this, &UMS_GeneralWidget::OnClickedBuyItemButton);
	}
	if(CPP_LeftExpanderButton02)
	{
		CPP_LeftExpanderButton02->SetButtonType(EMS_GeneralButtonType::BuyFurniture);
		CPP_LeftExpanderButton02->GetOnClickedDelegate().AddUObject(this, &UMS_GeneralWidget::OnClickedBuyFurnitureButton);
	}
	if(CPP_LeftExpanderButton03)
	{
		CPP_LeftExpanderButton03->SetButtonType(EMS_GeneralButtonType::HireStaff);
		CPP_LeftExpanderButton03->GetOnClickedDelegate().AddUObject(this, &UMS_GeneralWidget::OnClickedHireStaffButton);
	}
	if(CPP_LeftExpanderButton04)
	{
		CPP_LeftExpanderButton04->SetButtonType(EMS_GeneralButtonType::StaffManage);
		CPP_LeftExpanderButton04->GetOnClickedDelegate().AddUObject(this, &UMS_GeneralWidget::OnClickedManageStaffButton);
	}
	if(CPP_LeftExpanderButton05)
	{
		CPP_LeftExpanderButton05->SetButtonType(EMS_GeneralButtonType::CustomerManage);
		CPP_LeftExpanderButton05->GetOnClickedDelegate().AddUObject(this, &UMS_GeneralWidget::OnClickedManageCustomerButton);
	}
	if(CPP_LeftExpanderButton06)
	{
		CPP_LeftExpanderButton06->SetButtonType(EMS_GeneralButtonType::SalesDetail);
		CPP_LeftExpanderButton06->GetOnClickedDelegate().AddUObject(this, &UMS_GeneralWidget::OnClickedFinancialIndicatorButton);
	}
}

void UMS_GeneralWidget::OnClickedLeftButton()
{
	if(LeftButtonType == EMS_GeneralButtonType::Schedule)
	{
		FMS_ModalParameter Parameter;
		Parameter.InModalWidget = gWidgetMng.Create_Widget(UMS_ScheduleModalWidget::GetWidgetName());
		gWidgetMng.ShowModalWidget(Parameter);
	}
	else if(LeftButtonType ==EMS_GeneralButtonType::Manage)
	{
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
}

void UMS_GeneralWidget::OnClickedBuyItemButton()
{
	FMS_ModalParameter Parameter;
	Parameter.InModalWidget = gWidgetMng.Create_Widget(UMS_BuyItemWidget::GetWidgetName());
	gWidgetMng.ShowModalWidget(Parameter);

	CPP_LeftExpanderPanel->SetVisibility(ESlateVisibility::Collapsed);
}

void UMS_GeneralWidget::OnClickedBuyFurnitureButton()
{
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

void UMS_GeneralWidget::OnUpdateTimer(int32 ScheduleType)
{
	switch(static_cast<EMS_MarketNormalScheduleEvent>(ScheduleType))
	{
	case EMS_MarketNormalScheduleEvent::Prepare:
	case EMS_MarketNormalScheduleEvent::Deadline:
	/*case EMS_MarketNormalScheduleEvent::Night:
		{
			CPP_TimeLineWidget->IsStartTimer(false);
			break;
		}*/
	case EMS_MarketNormalScheduleEvent::LoadingUnloading:
	case EMS_MarketNormalScheduleEvent::OpenMarket:
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

void UMS_GeneralWidget::OpenLeftExpander() const
{
	CPP_LeftExpanderPanel->SetVisibility(CPP_LeftExpanderPanel->IsVisible() ? ESlateVisibility::Collapsed : ESlateVisibility::SelfHitTestInvisible);
}
