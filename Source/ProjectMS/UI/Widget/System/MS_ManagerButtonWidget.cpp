// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ManagerButtonWidget.h"

#include "Button/MS_Button.h"
#include "Manager_Client/MS_WidgetManager.h"

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
