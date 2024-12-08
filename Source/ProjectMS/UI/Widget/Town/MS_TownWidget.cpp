// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_TownWidget.h"

#include "MS_WidgetManager.h"
#include "Widget/System/MS_ContentsPartWidget.h"

void UMS_TownWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMS_TownWidget::OnClickedDefaultButton()
{
	gWidgetMng.ShowToastMessage(TEXT(""));
}
