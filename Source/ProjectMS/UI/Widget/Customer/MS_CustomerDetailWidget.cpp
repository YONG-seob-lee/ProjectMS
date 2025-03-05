// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_CustomerDetailWidget.h"

#include "MS_BehaviorWidget.h"
#include "MS_ChatWidget.h"
#include "MS_Define.h"
#include "MS_PurchaseWidget.h"
#include "Button/MS_CustomerButton.h"
#include "Widget/WidgetComponent/MS_WidgetSwitcher.h"

void UMS_CustomerDetailWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	ResetActivateCustomerDetailButton();
	CPP_ChatButton->SetActive(true);

	CPP_ChatButton->GetOnClickedDelegate().AddUObject(this, &UMS_CustomerDetailWidget::OnClickedDetailButton, EMS_CustomerDetailType::Chatting);
	CPP_BehaviorButton->GetOnClickedDelegate().AddUObject(this, &UMS_CustomerDetailWidget::OnClickedDetailButton, EMS_CustomerDetailType::Behavior);
	CPP_PurchaseButton->GetOnClickedDelegate().AddUObject(this, &UMS_CustomerDetailWidget::OnClickedDetailButton, EMS_CustomerDetailType::Purchase);
}

void UMS_CustomerDetailWidget::SetType(EMS_PopulationNumber aPopulationNumber, EMS_CustomerDetailType aDetailType)
{
	if(aPopulationNumber == EMS_PopulationNumber::One && PersonUnitHandle == INDEX_NONE)
	{
		MS_ERROR(TEXT("Warning : \'UMS_CustomerDetailWidget\' Do not have PersonUnitHandle MemberVariable. Please Check"));
		return;
	}
	
	PopulationNumber = aPopulationNumber;
	CustomerDetailType = aDetailType;
	ResetActivateCustomerDetailButton();
	
	if(aDetailType == EMS_CustomerDetailType::Chatting)
	{
		CPP_ChatButton->SetActive(true);
		CPP_ChatWidget->SetChat(PersonUnitHandle, aPopulationNumber);
	}
	else if(aDetailType == EMS_CustomerDetailType::Behavior)
	{
		CPP_BehaviorButton->SetActive(true);
		CPP_BehaviorWidget->SetBehavior(PersonUnitHandle, aPopulationNumber);
	}
	else if(aDetailType == EMS_CustomerDetailType::Purchase)
	{
		CPP_PurchaseButton->SetActive(true);
		CPP_PurchaseWidget->SetPurchase(PersonUnitHandle, aPopulationNumber);
	}
	else
	{
		MS_ERROR(TEXT("Warning!!!!!!!"));
		MS_ENSURE(false);
	}

	CPP_DetailWidgetSwitcher->SetActiveWidgetIndex(static_cast<int32>(aDetailType));
}

void UMS_CustomerDetailWidget::ResetActivateCustomerDetailButton() const
{
	CPP_ChatButton->SetActive(false);
	CPP_BehaviorButton->SetActive(false);
	CPP_PurchaseButton->SetActive(false);
}

void UMS_CustomerDetailWidget::OnClickedDetailButton(EMS_CustomerDetailType aCustomerDetailButtonType)
{
	ResetActivateCustomerDetailButton();
	
	CPP_DetailWidgetSwitcher->SetActiveWidgetIndex(static_cast<int32>(aCustomerDetailButtonType));
	CustomerDetailType = aCustomerDetailButtonType;
	if(aCustomerDetailButtonType == EMS_CustomerDetailType::Chatting)
	{
		CPP_ChatButton->SetActive(true);
		CPP_ChatWidget->SetChat(PersonUnitHandle, PopulationNumber);
	}
	else if(aCustomerDetailButtonType == EMS_CustomerDetailType::Behavior)
	{
		CPP_BehaviorButton->SetActive(true);
		CPP_BehaviorWidget->SetBehavior(PersonUnitHandle, PopulationNumber);
	}
	else if(aCustomerDetailButtonType == EMS_CustomerDetailType::Purchase)
	{
		CPP_PurchaseButton->SetActive(true);
		CPP_PurchaseWidget->SetPurchase(PersonUnitHandle, PopulationNumber);
	}
	else
	{
		return;
	}

	if(OnUpdateCustomerDetailTypeCallback)
	{
		OnUpdateCustomerDetailTypeCallback(CustomerDetailType);
	}
}
