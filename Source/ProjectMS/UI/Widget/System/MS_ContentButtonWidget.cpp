// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ContentButtonWidget.h"

#include "MS_WidgetManager.h"
#include "Button/MS_Button.h"

void UMS_ContentButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if(CPP_ContentButton)
	{
		CPP_ContentButton->GetOnClickedDelegate().AddWeakLambda(this, [this]()
		{
			gWidgetMng.ShowToastMessage(TEXT(""));
		});
	}
}
