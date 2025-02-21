// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_TownWidget.h"

#include "Button/MS_Button.h"
#include "ContentsUtilities/MS_GameProcessDefine.h"
#include "LevelScriptActors/MS_StageLevelScriptActor.h"
#include "Manager_Client/MS_SceneManager.h"
#include "Manager_Client/MS_ScheduleManager.h"


void UMS_TownWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if(CPP_SleepButton)
	{
		CPP_SleepButton->GetOnClickedDelegate().AddUObject(this, &UMS_TownWidget::OnClickedSleepButton);
	}

	gScheduleMng.OnUpdateGameDateDelegate.AddUObject(this, &UMS_TownWidget::OnUpdateGameDate);
}

void UMS_TownWidget::NativeConstruct()
{
	Super::NativeConstruct();

	const FMS_GameDate& GameDate = gScheduleMng.GetGameDate();
	OnUpdateGameDate(GameDate);
}

void UMS_TownWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UMS_TownWidget::OnUpdateGameDate(const FMS_GameDate& aGameDate)
{
	const FMS_GameDate& GameDate = gScheduleMng.GetGameDate();
	
	if (FMS_GameDate::IsNight(GameDate.DailyTimeZone))
	{
		CPP_SleepButton->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		CPP_SleepButton->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UMS_TownWidget::OnClickedSleepButton()
{
	const FMS_GameDate& GameDate = gScheduleMng.GetGameDate();

	if (FMS_GameDate::IsNight(GameDate.DailyTimeZone))
	{
		gScheduleMng.PassTheDay();
	
		if(const TObjectPtr<AMS_StageLevelScriptActor> TownLevelScriptActor = Cast<AMS_StageLevelScriptActor>(gSceneMng.GetCurrentLevelScriptActor()))
		{
			TownLevelScriptActor->SetDayAndNight(EMS_DayAndNight::Day);
		}
	}
}
