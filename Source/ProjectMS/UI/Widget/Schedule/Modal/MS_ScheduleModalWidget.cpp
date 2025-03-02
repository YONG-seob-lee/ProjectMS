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
	constexpr int32 ChangePreviousMonth = -1;
	constexpr int32 ChangeNextMonth = 1;

	constexpr int32 MinMonth = 1;
	constexpr int32 MaxMonth = 12;
}

void UMS_ScheduleModalWidget::InitWidget(const FName& aTypeName, bool bManaged, bool bAttachToRoot)
{
	Super::InitWidget(aTypeName, bManaged, bAttachToRoot);

	if(CPP_MonthChangeLeftButton && CPP_MonthChangeRightButton)
	{
		CPP_MonthChangeLeftButton->GetOnClickedDelegate().AddUObject(this, &UMS_ScheduleModalWidget::OnClickedChangeMonthButton, Schedule::ChangePreviousMonth);
		CPP_MonthChangeRightButton->GetOnClickedDelegate().AddUObject(this, &UMS_ScheduleModalWidget::OnClickedChangeMonthButton, Schedule::ChangeNextMonth);
	}
	
	CurrentMonth = gScheduleMng.GetGameDate().Month;

	UpdateSchedule();
}

void UMS_ScheduleModalWidget::UpdateSchedule()
{
	CPP_MonthScheduleText->SetText(FText::FromString(FString::Format(*Schedule::MonthString, {CurrentMonth})));
	
	if(CPP_DaysTileView)
	{
		TArray<UMS_ScheduleDayElementData*> ScheduleDayElementDatas;

		for(int32 i = 1 ; i <= 28; i++)
		{
			UMS_ScheduleDayElementData* Data = MS_NewObject<UMS_ScheduleDayElementData>(this);
			Data->SetDate(FMS_GameDate(0, CurrentMonth, i));
			if( i % 7 == 6)
			{
				Data->SetColor(FLinearColor::Blue);
			}
			else if( i % 7 == 0)
			{
				Data->SetColor(FLinearColor::Red);
			}
			else
			{
				Data->SetColor(FLinearColor::Black);
			}
			ScheduleDayElementDatas.Emplace(Data);
		}
		
		CPP_DaysTileView->SetElements(TArray<UObject*>(ScheduleDayElementDatas));
	}
}

void UMS_ScheduleModalWidget::OnClickedChangeMonthButton(int32 aChangeMonthProperty)
{
	
	if(aChangeMonthProperty == Schedule::ChangePreviousMonth)
	{
		if(CurrentMonth == Schedule::MinMonth)
		{
			return;
		}
		CurrentMonth -= 1;
		UpdateSchedule();
	}
	else if(aChangeMonthProperty == Schedule::ChangeNextMonth)
	{
		if(CurrentMonth == Schedule::MaxMonth)
		{
			return;
		}
		CurrentMonth += 1;
		UpdateSchedule();
	}
}
