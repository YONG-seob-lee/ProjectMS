// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ExtensionButtonWidget.h"

#include "Button/MS_Button.h"
#include "Manager_Both/MS_ModeManager.h"
#include "Manager_Client/MS_WidgetManager.h"

void UMS_ExtensionButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	CPP_ExtensionButton->GetOnClickedDelegate().AddWeakLambda(this, [this]()
	{
		gModeMng.ChangeState(ModeState);
		gWidgetMng.ShowToastMessage(TEXT(""));
	});
}

void UMS_ExtensionButtonWidget::SetModeType(EMS_ModeState aModeState)
{
	ModeState = aModeState;
}
