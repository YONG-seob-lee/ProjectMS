// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ScheduleDayElementWidget.h"

#include "Components/TextBlock.h"
#include "ElementData/MS_ScheduleDayElementData.h"
#include "Manager_Client/MS_InputManager.h"
#include "Manager_Client/MS_ScheduleManager.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "Widget/Schedule/MS_ScheduleDetailWidget.h"

void UMS_ScheduleDayElementWidget::NativeOnListItemObjectSet(UObject* aListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(aListItemObject);

	const UMS_ScheduleDayElementData* Data = Cast<UMS_ScheduleDayElementData>(aListItemObject);
	if(!Data)
	{
		return;
	}

	Date = Data->GetDate();
	
	if(CPP_Days)
	{
		CPP_Days->SetText(FText::FromString(FString::Format(TEXT("{0} 일"), {Date.Day})));
		CPP_Days->SetColorAndOpacity(Data->GetColor());
	}
}

void UMS_ScheduleDayElementWidget::NativeOnItemSelectionChanged(bool bIsSelected)
{
	IUserObjectListEntry::NativeOnItemSelectionChanged(bIsSelected);
	
	if(UMS_ScheduleDetailWidget* DetailWidget = Cast<UMS_ScheduleDetailWidget>(gWidgetMng.Create_Widget(UMS_ScheduleDetailWidget::GetWidgetName(), false)))
	{
		FMS_SettlementSheet Sheet;
		if(gScheduleMng.GetSettlementSheet(Date, Sheet) == false)
		{
			return;
		}

		DetailWidget->SetDetail(Sheet);
		gWidgetMng.SetCustomPositionWidget(DetailWidget, gInputMng.AcquirePointerPositionOnViewport());
	}
}