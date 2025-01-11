// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_TimeLineWidget.h"
#include "Components/TextBlock.h"
#include "Manager_Both/MS_TableManager.h"
#include "Table/Caches/MS_CommonCacheTable.h"

namespace DotFlicker
{
	constexpr float IntervalTime = 0.5f;
}
void UMS_TimeLineWidget::NativeConstruct()
{
	Super::NativeConstruct();

	const TObjectPtr<UMS_CommonCacheTable> CommonTable = Cast<UMS_CommonCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::Common));
	MS_CHECK(CommonTable);

	SecondPerOneMinute = CommonTable->GetParameter01(CommonContents::SECONDS_PER_ONEMINUTE);
}

void UMS_TimeLineWidget::NativeDestruct()
{
	GetWorld()->GetTimerManager().ClearTimer(DotFlickerHandle);

	
	Super::NativeDestruct();
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
