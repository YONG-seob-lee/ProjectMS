// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ScheduleDayElementWidget.h"

#include "Components/TextBlock.h"
#include "ElementData/MS_ScheduleDayElementData.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "Widget/Schedule/MS_ScheduleDetailWidget.h"
#include "Widget/System/Modal/MS_ModalWidget.h"

void UMS_ScheduleDayElementWidget::NativeOnListItemObjectSet(UObject* aListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(aListItemObject);

	const UMS_ScheduleDayElementData* Data = Cast<UMS_ScheduleDayElementData>(aListItemObject);
	if(!Data)
	{
		return;
	}

	Day = Data->GetDays();
	
	if(CPP_Days)
	{
		CPP_Days->SetText(FText::FromString(FString::Format(TEXT("{0} 일"), {Day})));
		CPP_Days->SetColorAndOpacity(Data->GetColor());
	}
}

FReply UMS_ScheduleDayElementWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	gWidgetMng.SetCustomPositionWidget(gWidgetMng.Create_Widget(UMS_ScheduleDetailWidget::GetWidgetName(), false), InMouseEvent.GetScreenSpacePosition());
	
	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}
