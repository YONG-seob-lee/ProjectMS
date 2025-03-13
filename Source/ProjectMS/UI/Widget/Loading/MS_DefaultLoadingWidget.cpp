// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_DefaultLoadingWidget.h"
#include "Widget/WidgetComponent/MS_WidgetSwitcher.h"

void UMS_DefaultLoadingWidget::UpdateLoadingImage() const
{
	if(CPP_LoadingSwitch)
	{
		CPP_LoadingSwitch->SetActiveWidgetIndex(FMath::RandRange(0, CPP_LoadingSwitch->GetChildrenCount() - 1));
	}
}
