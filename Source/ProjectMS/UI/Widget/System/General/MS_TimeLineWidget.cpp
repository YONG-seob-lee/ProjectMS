// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_TimeLineWidget.h"

#include "Button/MS_Button.h"
#include "Components/TextBlock.h"
#include "Manager_Both/MS_TableManager.h"
#include "Manager_Client/MS_SceneManager.h"
#include "Manager_Client/MS_ScheduleManager.h"
#include "Table/Caches/MS_CommonCacheTable.h"


namespace DotFlicker
{
	constexpr float IntervalTime = 0.5f;
}

void UMS_TimeLineWidget::NativeConstruct()
{
	Super::NativeConstruct();

	FillDefaultAnimations();

	const TObjectPtr<UMS_CommonCacheTable> CommonTable = Cast<UMS_CommonCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::Common));
	MS_CHECK(CommonTable);

	SecondPerOneMinute = CommonTable->GetParameter01(CommonContents::SECONDS_PER_ONEMINUTE);

	UpdateGameDate(gScheduleMng.GetGameDate());
	UpdateTimer(gScheduleMng.GetMinute());

	gScheduleMng.OnUpdateGameDateDelegate.AddUObject(this, &UMS_TimeLineWidget::UpdateGameDate);
	gScheduleMng.OnUpdateMinuteDelegate.AddUObject(this, &UMS_TimeLineWidget::UpdateTimer);
}

void UMS_TimeLineWidget::NativeDestruct()
{
	GetWorld()->GetTimerManager().ClearTimer(DotFlickerHandle);
	
	Super::NativeDestruct();
}

void UMS_TimeLineWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UMS_TimeLineWidget::UpdateGameDate(const FMS_GameDate& aGameDate)
{
	const bool bIsRunning = FMS_GameDate::IsRunningTimeZone(aGameDate.DailyTimeZone);
	FlickerDot(bIsRunning);

	CPP_Day->SetText(FText::FromString(FString::Format(TEXT("{0}년차 {1}월 {2}일"), {aGameDate.Year, aGameDate.Month, aGameDate.Day})));
}

void UMS_TimeLineWidget::UpdateTimer(int32 aMinute) const
{
	FMS_GameDate GameDate = gScheduleMng.GetGameDate();
	int32 StartMinute = FMS_GameDate::ConvertTimeZoneToMinute(GameDate.DailyTimeZone);
	int32 CurrentMinute = StartMinute + aMinute;
	
	const int32 Hour = CurrentMinute / SecondPerOneMinute;
	const int32 Minute = CurrentMinute % SecondPerOneMinute;
	FString HourString = FString::FromInt(Hour);
	if(Hour < 10)
	{
		HourString.AppendInt(0);
		HourString.ReverseString();
	}
	
	FString MinuteString = FString::FromInt(Minute);
	if(Minute < 10)
	{
		MinuteString.AppendInt(0);
		MinuteString.ReverseString();
	}
	CPP_Hour->SetText(FText::FromString(HourString));
	CPP_Minute->SetText(FText::FromString(MinuteString));
}

void UMS_TimeLineWidget::FlickerDot(bool bFlicker)
{
	if(bFlicker)
	{
		GetWorld()->GetTimerManager().SetTimer(DotFlickerHandle, this, &UMS_TimeLineWidget::InVisibilityDot, DotFlicker::IntervalTime, true);
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(DotFlickerHandle);
		CPP_Dot->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
}

void UMS_TimeLineWidget::InVisibilityDot() const
{
	if(CPP_Dot->IsVisible())
	{
		CPP_Dot->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		CPP_Dot->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
}