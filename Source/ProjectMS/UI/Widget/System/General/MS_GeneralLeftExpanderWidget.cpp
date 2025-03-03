// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_GeneralLeftExpanderWidget.h"

#include "Button/MS_GeneralButton.h"
#include "Manager_Client/MS_ItemManager.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "Widget/Customer/Modal/MS_CustomerManagementWidget.h"
#include "Widget/Finance/Modal/MS_FinancialManagementWidget.h"
#include "Widget/Market/BuyThings/MS_BuyFurnitureWidget.h"
#include "Widget/Market/Modal/MS_MarketOrderCheckModalWidget.h"
#include "Widget/Market/Modal/MS_MarketOrderModalWidget.h"
#include "Widget/Staff/Modal/MS_HireStaffWidget.h"
#include "Widget/Staff/Modal/MS_StaffManagementWidget.h"
#include "Widget/System/Modal/MS_ModalWidget.h"

void UMS_GeneralLeftExpanderWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(CPP_LeftExpanderButton01)
	{		
		CPP_LeftExpanderButton01->SetButtonType(EMS_GeneralButtonType::OrderItem);
		CPP_LeftExpanderButton01->GetOnClickedDelegate().AddUObject(this, &UMS_GeneralLeftExpanderWidget::OnClickedOrderItemButton);
	}
	if(CPP_LeftExpanderButton02)
	{
		CPP_LeftExpanderButton02->SetButtonType(EMS_GeneralButtonType::CheckOrderItem);
		CPP_LeftExpanderButton02->GetOnClickedDelegate().AddUObject(this, &UMS_GeneralLeftExpanderWidget::OnClickedCheckOrderButton);
	}
	if(CPP_LeftExpanderButton03)
	{
		CPP_LeftExpanderButton03->SetButtonType(EMS_GeneralButtonType::OrderFurniture);
		CPP_LeftExpanderButton03->GetOnClickedDelegate().AddUObject(this, &UMS_GeneralLeftExpanderWidget::OnClickedOrderFurnitureButton);
	}
	if(CPP_LeftExpanderButton04)
	{
		CPP_LeftExpanderButton04->SetButtonType(EMS_GeneralButtonType::HireStaff);
		CPP_LeftExpanderButton04->GetOnClickedDelegate().AddUObject(this, &UMS_GeneralLeftExpanderWidget::OnClickedHireStaffButton);
	}
	if(CPP_LeftExpanderButton05)
	{
		CPP_LeftExpanderButton05->SetButtonType(EMS_GeneralButtonType::StaffManage);
		CPP_LeftExpanderButton05->GetOnClickedDelegate().AddUObject(this, &UMS_GeneralLeftExpanderWidget::OnClickedManageStaffButton);
	}
	if(CPP_LeftExpanderButton06)
	{
		CPP_LeftExpanderButton06->SetButtonType(EMS_GeneralButtonType::CustomerManage);
		CPP_LeftExpanderButton06->GetOnClickedDelegate().AddUObject(this, &UMS_GeneralLeftExpanderWidget::OnClickedManageCustomerButton);
	}
	if(CPP_LeftExpanderButton07)
	{
		CPP_LeftExpanderButton07->SetButtonType(EMS_GeneralButtonType::SalesDetail);
		CPP_LeftExpanderButton07->GetOnClickedDelegate().AddUObject(this, &UMS_GeneralLeftExpanderWidget::OnClickedFinancialIndicatorButton);
	}
}

void UMS_GeneralLeftExpanderWidget::OnClickedOrderItemButton()
{
	if(gItemMng.IsAvailablePurchase() == false)
	{
		gWidgetMng.ShowToastMessage(TEXT("이용 가능한 시간대가 아닙니다."));
		return;
	}
	
	FMS_ModalParameter Parameter;
	Parameter.InModalWidget = gWidgetMng.Create_Widget_NotManaging(UMS_MarketOrderModalWidget::GetWidgetPath());
	gWidgetMng.ShowModalWidget(Parameter);

	SetVisibility(ESlateVisibility::Collapsed);
}

void UMS_GeneralLeftExpanderWidget::OnClickedCheckOrderButton()
{
	FMS_ModalParameter Parameter;
	Parameter.InModalWidget = gWidgetMng.Create_Widget_NotManaging(UMS_MarketOrderCheckModalWidget::GetWidgetPath());
	gWidgetMng.ShowModalWidget(Parameter);

	SetVisibility(ESlateVisibility::Collapsed);
}

void UMS_GeneralLeftExpanderWidget::OnClickedOrderFurnitureButton()
{
	if(gItemMng.IsAvailablePurchase() == false)
	{
		gWidgetMng.ShowToastMessage(TEXT("이용 가능한 시간대가 아닙니다."));
		return;
	}
	
	FMS_ModalParameter Parameter;
	Parameter.InModalWidget = gWidgetMng.Create_Widget(UMS_BuyFurnitureWidget::GetWidgetName());
	gWidgetMng.ShowModalWidget(Parameter);

	SetVisibility(ESlateVisibility::Collapsed);
}

void UMS_GeneralLeftExpanderWidget::OnClickedHireStaffButton()
{
	FMS_ModalParameter Parameter;
	Parameter.InModalWidget = gWidgetMng.Create_Widget(UMS_HireStaffWidget::GetWidgetName());
	gWidgetMng.ShowModalWidget(Parameter);

	SetVisibility(ESlateVisibility::Collapsed);
}

void UMS_GeneralLeftExpanderWidget::OnClickedManageStaffButton()
{
	FMS_ModalParameter Parameter;
	Parameter.InModalWidget = gWidgetMng.Create_Widget(UMS_StaffManagementWidget::GetWidgetName());
	gWidgetMng.ShowModalWidget(Parameter);
	
	SetVisibility(ESlateVisibility::Collapsed);
}

void UMS_GeneralLeftExpanderWidget::OnClickedManageCustomerButton()
{
	FMS_ModalParameter Parameter;
	Parameter.InModalWidget = gWidgetMng.Create_Widget(UMS_CustomerManagementWidget::GetWidgetName());
	gWidgetMng.ShowModalWidget(Parameter);

	SetVisibility(ESlateVisibility::Collapsed);
}

void UMS_GeneralLeftExpanderWidget::OnClickedFinancialIndicatorButton()
{
	FMS_ModalParameter Parameter;
	Parameter.InModalWidget = gWidgetMng.Create_Widget(UMS_FinancialManagementWidget::GetWidgetName());
	gWidgetMng.ShowModalWidget(Parameter);

	SetVisibility(ESlateVisibility::Collapsed);
}
