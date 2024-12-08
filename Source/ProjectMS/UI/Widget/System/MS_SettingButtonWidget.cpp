// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_SettingButtonWidget.h"

#include "MS_WidgetManager.h"
#include "Button/MS_Button.h"

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
