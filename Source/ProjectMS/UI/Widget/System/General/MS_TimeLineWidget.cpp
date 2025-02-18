// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_TimeLineWidget.h"

#include "Button/MS_Button.h"
#include "Components/TextBlock.h"
#include "LevelScriptActors/MS_StageLevelScriptActor.h"
#include "Manager_Both/MS_TableManager.h"
#include "Manager_Client/MS_PlayerCameraManager.h"
#include "Manager_Client/MS_SceneManager.h"
#include "Manager_Client/MS_ScheduleManager.h"
#include "Manager_Client/MS_SequenceManager.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "Table/Caches/MS_CommonCacheTable.h"
#include "Widget/Market/Modal/MS_MarketStartModal.h"


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
	CPP_RunTimeButton->SetVisibility(ESlateVisibility::Collapsed);

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
	bool bIsRunning = FMS_GameDate::IsRunningTimeZone(aGameDate.DailyTimeZone);
	FlickerDot(bIsRunning);

	CPP_Day->SetText(FText::FromString(FString::Format(TEXT("{0}년차 : {1}월 {2}일"), {aGameDate.Year, aGameDate.Month, aGameDate.Day})));
	
	// Run Time Widget
	const FMS_GameDate& GameDate = gScheduleMng.GetGameDate();
	EMS_LevelType LevelType = gSceneMng.GetCurrentLevelType();

	if (!bIsRunning)
	{
		if (LevelType == EMS_LevelType::MarketLevel)
		{
			
			if (FMS_GameDate::IsNight(GameDate.DailyTimeZone))
			{
				CPP_RunTimeButton->SetVisibility(ESlateVisibility::Visible);
				StartRunTimeButtonAnim();
			}
			else
			{
				CPP_RunTimeButton->SetVisibility(ESlateVisibility::Visible);
				StartRunTimeButtonAnim();
			}
		}
		else
		{
			if (FMS_GameDate::IsNight(GameDate.DailyTimeZone))
			{
				CPP_RunTimeButton->SetVisibility(ESlateVisibility::Visible);
				StartRunTimeButtonAnim();
			}
			else
			{
				CPP_RunTimeButton->SetVisibility(ESlateVisibility::Collapsed);
				StopRunTimeButtonAnim();
			}
		}
	}
	else
	{
		CPP_RunTimeButton->SetVisibility(ESlateVisibility::Collapsed);
		StopRunTimeButtonAnim();
	}
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

void UMS_TimeLineWidget::StartRunTimeButtonAnim()
{
	CPP_RunTimeButton->GetOnClickedDelegate().AddUObject(this, &UMS_TimeLineWidget::OnClickedRunTimeButton);
	PlayAnimationByName(RunTime::Animation, 0.f, 999999);
}

void UMS_TimeLineWidget::StopRunTimeButtonAnim()
{
	CPP_RunTimeButton->UnbindClickedDelegate();
	StopAnimationByName(RunTime::Animation);
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

void UMS_TimeLineWidget::OnClickedRunTimeButton()
{
	const FMS_GameDate& GameDate = gScheduleMng.GetGameDate();
	const EMS_LevelType LevelType = gSceneMng.GetCurrentLevelType();

	if (LevelType == EMS_LevelType::None)
	{
		return;
	}
	
	if (LevelType == EMS_LevelType::MarketLevel)
	{
		if (FMS_GameDate::IsNight(GameDate.DailyTimeZone))
		{
			// Town으로 이동
			CREATE_SCENE_COMMAND(Command);
			Command->SetLevelType(EMS_LevelType::Stage01);
			Command->SetPreviousLevelType(EMS_LevelType::MarketLevel);
			Command->SetFadeOutTransitionType(EMS_TransitionStyle::GradationOut);
			Command->SetFadeInTransitionType(EMS_TransitionStyle::GradationIn);
			Command->SetFadeAnimationType(EMS_FadeAnimationCurveType::Linear);
			Command->SetLoadingWidgetType(EMS_LoadingWidgetType::Default);
			gSceneMng.OnFadeFinishedEventDelegate.AddWeakLambda(this, [this]
			{
				FViewTargetTransitionParams Param;
				Param.BlendTime = 0.f;
				gCameraMng.SwitchViewCamera(EMS_ViewCameraType::QuarterView, Param);
				gWidgetMng.SetGeneralWidget(EMS_LevelType::Stage01);
				gSceneMng.OnFadeFinishedEventDelegate.RemoveAll(this);
			});
			gSceneMng.RequestChangeScene(Command);
			
		}
		else
		{
			// MarketStartModal Open
			FMS_ModalParameter ModalParameter;
			ModalParameter.InModalWidget = gWidgetMng.Create_Widget_NotManaging(UMS_MarketStartModal::GetWidgetPath());
			ModalParameter.OnCloseWidgetCallback = []()
			{
				gSequenceMng.PlaySequence(EMS_SequenceType::Entrance);
			};
			gWidgetMng.ShowModalWidget(ModalParameter);
		}
	}
	else
	{
		if (FMS_GameDate::IsNight(GameDate.DailyTimeZone))
		{
			// 수면
			gScheduleMng.PassTheDay();
	
			if(const TObjectPtr<AMS_StageLevelScriptActor> TownLevelScriptActor = Cast<AMS_StageLevelScriptActor>(gSceneMng.GetCurrentLevelScriptActor()))
			{
				TownLevelScriptActor->SetDayAndNight(EMS_DayAndNight::Day);
			}
		}
	}
	CPP_RunTimeButton->GetOnClickedDelegate().RemoveAll(this);
	StopAllAnimations();
	CPP_RunTimeButton->SetVisibility(ESlateVisibility::Collapsed);
}