// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_AccountButton.h"

#include "Widget/WidgetComponent/MS_WidgetSwitcher.h"

void UMS_AccountButton::SetAccountButton(bool bAlreadyLogin) const
{
	if(bAlreadyLogin == false)
	{
		CPP_AccountButtonSwitcher->SetActiveWidgetIndex(0);
	}
	else
	{
		CPP_AccountButtonSwitcher->SetActiveWidgetIndex(1);	
	}
}
