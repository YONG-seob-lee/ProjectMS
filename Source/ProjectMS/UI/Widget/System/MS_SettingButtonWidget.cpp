// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_SettingButtonWidget.h"

#include "Button/MS_Button.h"
#include "Manager_Client/MS_WidgetManager.h"

void UMS_SettingButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if(CPP_SettingButton)
	{
		CPP_SettingButton->GetOnClickedDelegate().AddWeakLambda(this, [this]()
		{
			gWidgetMng.ShowToastMessage(TEXT(""));
		});
	}
}
