// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_DialogPortraitWidget.h"

#include "Widget/WidgetComponent/MS_WidgetSwitcher.h"

void UMS_DialogPortraitWidget::PlayMouse()
{
	GetWorld()->GetTimerManager().SetTimer(MouseTimeHandle, this, &UMS_DialogPortraitWidget::ChangeMouse, FMath::RandRange(0.1f, 0.6f), true);
}

void UMS_DialogPortraitWidget::StopMouse()
{
	GetWorld()->GetTimerManager().ClearTimer(MouseTimeHandle);
	CPP_MouseSwitcher->SetActiveWidgetIndex(static_cast<int32>(EMS_MouseType::e));
}

void UMS_DialogPortraitWidget::ChangeMouse() const
{
	if(static_cast<EMS_MouseType>(CPP_MouseSwitcher->GetActiveWidgetIndex()) == EMS_MouseType::e)
	{
		CPP_MouseSwitcher->SetActiveWidgetIndex(static_cast<int32>(EMS_MouseType::o));
	}
	else
	{
		CPP_MouseSwitcher->SetActiveWidgetIndex(static_cast<int32>(EMS_MouseType::e));
	}
}
