// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_DefaultButton.h"

#include "Manager_Client/MS_WidgetManager.h"

void UMS_DefaultButton::NativeConstruct()
{
	Super::NativeConstruct();
	
	GetOnClickedDelegate().AddUObject(this, &UMS_DefaultButton::OnClickDefaultButton);
}

void UMS_DefaultButton::OnClickDefaultButton()
{
	gWidgetMng.ShowToastMessage(TEXT(""));
}
