// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ManagerButtonWidget.h"

#include "MS_WidgetManager.h"
#include "Button/MS_Button.h"

void UMS_ManagerButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(CPP_ManagerButton)
	{
		CPP_ManagerButton->GetOnClickedDelegate().AddWeakLambda(this, [this]()
		{
			gWidgetMng.ShowToastMessage(TEXT(""));
		});
	}
}
