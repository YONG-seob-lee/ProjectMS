// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ExtensionButtonWidget.h"

#include "MS_ModeManager.h"
#include "MS_WidgetManager.h"
#include "Button/MS_Button.h"

void UMS_ExtensionButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	CPP_ExtensionButton->GetOnClickedDelegate().AddWeakLambda(this, [this]()
	{
		gModeMng.OnSetMode.Broadcast(static_cast<uint8>(Mode));
		gModeMng.SetMode(Mode);
		gWidgetMng.ShowToastMessage(TEXT(""));
	});
}