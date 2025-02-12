// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_TimeLineWidget.h"

#include "Button/MS_Button.h"
#include "Components/TextBlock.h"
#include "LevelScriptActors/MS_StageLevelScriptActor.h"
#include "Manager_Both/MS_TableManager.h"
#include "Manager_Client/MS_SceneManager.h"
#include "Manager_Client/MS_ScheduleManager.h"
#include "Manager_Client/MS_WidgetManager.h"
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
	CPP_SleepButton->SetVisibility(ESlateVisibility::Collapsed);
}

void UMS_TimeLineWidget::NativeDestruct()
{
	GetWorld()->GetTimerManager().ClearTimer(DotFlickerHandle);

	
	Super::NativeDestruct();
}

void UMS_TimeLineWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if(bStartPassDayTimer)
	{
		ProcessPassDayTimer(InDeltaTime);
	}
}

void UMS_TimeLineWidget::IsStartTimer(bool bStart)
{
	FlickerDot(bStart);
}

void UMS_TimeLineWidget::UpdateTimer(int32 aMinute) const
{
	const int32 Hour = aMinute / SecondPerOneMinute;
	const int32 Minute = aMinute % SecondPerOneMinute;
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

void UMS_TimeLineWidget::StartSleepButtonAnim()
{
	CPP_SleepButton->SetVisibility(ESlateVisibility::Visible);
	CPP_SleepButton->GetOnClickedDelegate().AddUObject(this, &UMS_TimeLineWidget::OnClickedSleepButton);
	PlayAnimationByName(Sleep::Animation, 0.f, 999999);
}

void UMS_TimeLineWidget::RequestPassTimer()
{
	bStartPassDayTimer = true;
	PassDayTimerMinute = 22 * 60;
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
		CPP_Dot->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		CPP_Dot->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
}

void UMS_TimeLineWidget::OnClickedSleepButton()
{
	gScheduleMng.TransferServer();
	if(const TObjectPtr<AMS_StageLevelScriptActor> TownLevelScriptActor = Cast<AMS_StageLevelScriptActor>(gSceneMng.GetCurrentLevelScriptActor()))
	{
		TownLevelScriptActor->SetDayAndNight(EMS_DayAndNight::Day);
	}
	
	CPP_SleepButton->GetOnClickedDelegate().RemoveAll(this);
	StopAllAnimations();
	CPP_SleepButton->SetVisibility(ESlateVisibility::Collapsed);
}

void UMS_TimeLineWidget::ProcessPassDayTimer(float InDeltaTime)
{
	PassDayTimerMinute += InDeltaTime * 170.f;
	if(PassDayTimerMinute >= 24 * 60)
	{
		PassDayTimerMinute = 0;
	}
	if(PassDayTimerMinute >= 6 * 60 && PassDayTimerMinute < 6 * 61)
	{
		UpdateTimer(6 * 60);
		gWidgetMng.ShowToastMessage(TEXT("아침이 밝았습니다~~"));
		bStartPassDayTimer = false;
		return;
	}
	UpdateTimer(PassDayTimerMinute);
}