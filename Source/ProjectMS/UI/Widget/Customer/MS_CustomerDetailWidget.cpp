// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_CustomerDetailWidget.h"

#include "MS_BehaviorWidget.h"
#include "MS_ChatWidget.h"
#include "MS_Define.h"
#include "MS_PurchaseWidget.h"
#include "Button/MS_CustomerButton.h"
#include "Widget/WidgetComponent/MS_WidgetSwitcher.h"

void UMS_CustomerDetailWidget::SetType(EMS_PopulationNumber aPopulationNumber, EMS_CustomerDetailType aDetailType) const
{
	if(PersonUnitHandle == INDEX_NONE)
	{
		MS_ERROR(TEXT("Warning : \'UMS_CustomerDetailWidget\' Do not have PersonUnitHandle MemberVariable. Please Check"));
		return;
	}
	
	ResetActivateButton();
	
	if(aDetailType == EMS_CustomerDetailType::Chatting)
	{
		CPP_ChatButton->SetActive(true);
		CPP_ChatWidget->SetChat(PersonUnitHandle, aPopulationNumber);
	}
	else if(aDetailType == EMS_CustomerDetailType::Behavior)
	{
		CPP_BehaviorButton->SetActive(true);
		//CPP_BehaviorWidget->SetBehavior(aPopulationNumber);
	}
	else if(aDetailType == EMS_CustomerDetailType::Purchase)
	{
		CPP_PurchaseButton->SetActive(true);
		//CPP_PurchaseWidget->SetPurchase(aPopulationNumber);
	}
	else
	{
		MS_ERROR(TEXT("Warning!!!!!!!"));
		MS_Ensure(false);
	}

	CPP_DetailWidgetSwitcher->SetActiveWidgetIndex(static_cast<int32>(aDetailType));
}

void UMS_CustomerDetailWidget::ResetActivateButton() const
{
	CPP_ChatButton->SetActive(false);
	CPP_BehaviorButton->SetActive(false);
	CPP_PurchaseButton->SetActive(false);
}
