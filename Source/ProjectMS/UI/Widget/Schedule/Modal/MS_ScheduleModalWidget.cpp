// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ScheduleModalWidget.h"

#include "Button/MS_Button.h"
#include "Components/TextBlock.h"
#include "Manager_Client/MS_ScheduleManager.h"
#include "Widget/ListViewElement/ElementData/MS_ScheduleDayElementData.h"
#include "Widget/WidgetComponent/MS_TileView.h"

namespace Schedule
{
	const FString MonthString = TEXT("\" {0}월 스케줄 \"");
	constexpr int32 DefaultMonth = 1;
	constexpr int32 ChangePreviousMonth = -1;
	constexpr int32 ChangeNextMonth = 1;
}

void UMS_ScheduleModalWidget::InitWidget(const FName& aTypeName, bool bManaged, bool bAttachToRoot)
{
	Super::InitWidget(aTypeName, bManaged, bAttachToRoot);

	SetMonth(Schedule::DefaultMonth);

	if(CPP_MonthChangeLeftButton && CPP_MonthChangeRightButton)
	{
		CPP_MonthChangeLeftButton->GetOnClickedDelegate().AddUObject(this, &UMS_ScheduleModalWidget::OnClickedChangeMonthButton, Schedule::ChangePreviousMonth);
		CPP_MonthChangeRightButton->GetOnClickedDelegate().AddUObject(this, &UMS_ScheduleModalWidget::OnClickedChangeMonthButton, Schedule::ChangeNextMonth);
	}
	
	if(CPP_DaysTileView)
	{
		TArray<UMS_ScheduleDayElementData*> Data;
		 gScheduleMng.GetScheduleData(Data);
		CPP_DaysTileView->SetElements(TArray<UObject*>(Data));
	}
}

void UMS_ScheduleModalWidget::SetMonth(int32 aMonth) const
{
	CPP_MonthScheduleText->SetText(FText::FromString(FString::Format(*Schedule::MonthString, {aMonth})));
}

void UMS_ScheduleModalWidget::OnClickedChangeMonthButton(int32 aChangeMonthProperty)
{
	if(aChangeMonthProperty == Schedule::ChangePreviousMonth)
	{
		SetMonth(--Month);
	}
	else if(aChangeMonthProperty == Schedule::ChangeNextMonth)
	{
		SetMonth(++Month);
	}
}
