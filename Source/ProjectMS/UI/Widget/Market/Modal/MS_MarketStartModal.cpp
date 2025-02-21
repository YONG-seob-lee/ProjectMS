// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_MarketStartModal.h"

#include "Button/MS_Button.h"
#include "Manager_Client/MS_ModeManager.h"
#include "Manager_Client/MS_ScheduleManager.h"
#include "Manager_Client/MS_SequenceManager.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "Mode/ModeState/MS_ModeState_RunMarketBase.h"

void UMS_MarketStartModal::NativeConstruct()
{
	Super::NativeConstruct();

	CPP_OpeningPlayButton->GetOnClickedDelegate().AddUObject(this, &UMS_MarketStartModal::OnClickedOpeningPlayButton);

	CPP_FastButton->GetOnClickedDelegate().AddWeakLambda(this, [this]()
	{
		gModeMng.ChangeState(EMS_ModeState::RunMarket);
		gWidgetMng.CloseModalWidget();
	});

	
}

void UMS_MarketStartModal::OnClickedOpeningPlayButton()
{
	CPP_OpeningPlayButton->GetOnClickedDelegate().RemoveAll(this);

	gModeMng.ChangeState(EMS_ModeState::RunMarket);
	gWidgetMng.CloseModalWidget([]()
	{
		FMS_SequencePlayParameter Parameter;
		Parameter.OnFinishedSequenceCallback = []()
		{
			if(const UMS_ModeState_RunMarketBase* RunMarketMode = Cast<UMS_ModeState_RunMarketBase>(gModeMng.GetCurrentModeState()))
			{
				TMap<int32, int32> ScheduleEvent = {};
				RunMarketMode->GetScheduleEvent(ScheduleEvent);
				gScheduleMng.RunSchedule(ScheduleDefault::GamePlayMinute, ScheduleEvent);
			}
		};
		gSequenceMng.PlaySequence(EMS_SequenceType::Entrance, Parameter);
	});
}
