// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ZoneOpenWidget.h"

#include "Button/MS_Button.h"

void UMS_ZoneOpenWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	CPP_ZoneOpenButton->GetOnClickedDelegate().AddUObject(this, &UMS_ZoneOpenWidget::OnClickZoneOpenButton);
}

void UMS_ZoneOpenWidget::OnClickZoneOpenButton()
{
	OnClickZoneOpenButtonDelegate.ExecuteIfBound(this);
}
