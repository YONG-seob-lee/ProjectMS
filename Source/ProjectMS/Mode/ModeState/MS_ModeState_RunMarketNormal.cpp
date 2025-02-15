// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ModeState_RunMarketNormal.h"

#include "ContentsUtilities/MS_GameProcessDefine.h"
#include "Manager_Client/MS_ScheduleManager.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "Widget/Market/Modal/MS_MarketEndModal.h"


UMS_ModeState_RunMarketNormal::UMS_ModeState_RunMarketNormal()
{
}

void UMS_ModeState_RunMarketNormal::Initialize(uint8 aIndex, const FName& aName)
{
	Super::Initialize(aIndex, aName);

	ScheduleEvent.Emplace(static_cast<int32>(EMS_MarketNormalScheduleEvent::Prepare, 0));
	ScheduleEvent.Emplace(static_cast<int32>(EMS_MarketNormalScheduleEvent::LoadingUnloading, 20));
	ScheduleEvent.Emplace(static_cast<int32>(EMS_MarketNormalScheduleEvent::OpenMarket, 140));
	ScheduleEvent.Emplace(static_cast<int32>(EMS_MarketNormalScheduleEvent::Deadline, 770));
	ScheduleEvent.Emplace(static_cast<int32>(EMS_MarketNormalScheduleEvent::CloseMarket, 800));
}

void UMS_ModeState_RunMarketNormal::Finalize()
{
	Super::Finalize();
}

void UMS_ModeState_RunMarketNormal::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
}

void UMS_ModeState_RunMarketNormal::Begin()
{
	Super::Begin();
}

void UMS_ModeState_RunMarketNormal::Exit()
{
	Super::Exit();
}

void UMS_ModeState_RunMarketNormal::RunSchedule()
{
	gScheduleMng.RunSchedule(800, TMap<int32, int32>());
}

void UMS_ModeState_RunMarketNormal::UpdateMinute(int32 aCurrentMinute)
{
	Super::UpdateMinute(aCurrentMinute);
}

void UMS_ModeState_RunMarketNormal::UpdateScheduleEvent(int32 aScheduleEvent)
{
	Super::UpdateScheduleEvent(aScheduleEvent);

	EMS_MarketNormalScheduleEvent MarketNormalScheduleEvent = static_cast<EMS_MarketNormalScheduleEvent>(aScheduleEvent);
	
	switch(MarketNormalScheduleEvent)
	{
	case EMS_MarketNormalScheduleEvent::Prepare:
		{
			gWidgetMng.ShowToastMessage(TEXT("준비 단계!"));
			break;
		}
	case EMS_MarketNormalScheduleEvent::LoadingUnloading:
		{
			gWidgetMng.ShowToastMessage(TEXT("상하차가 시작되었습니다!"));
			break;
		}
	case EMS_MarketNormalScheduleEvent::OpenMarket:
		{
			gWidgetMng.ShowToastMessage(TEXT("매장 오픈~!! 달려보자고!"));
			break;
		}
	/*case EMS_MarketNormalScheduleEvent::Morning:
		{
			gWidgetMng.ShowToastMessage(TEXT("Zzz  Zzz  Zzzzz"));
			gWidgetMng.RequestPassTimerWidget();
		}
	case EMS_MarketNormalScheduleEvent::Night:
		{
			//OnUpdateMinuteDelegate.Broadcast(TimeSchedule->GetMinute());
			break;
		}*/
	case EMS_MarketNormalScheduleEvent::Deadline:
		{
			// 타이머 없어도 돼
			gWidgetMng.ShowToastMessage(TEXT("매장 문 닫겠습니다~!"));
			FMS_ModalParameter ModalParameter;
			ModalParameter.InModalWidget = gWidgetMng.Create_Widget_NotManaging(UMS_MarketEndModal::GetWidgetPath());
			gWidgetMng.ShowModalWidget(ModalParameter);
			break;
		}
	default:
		{
			break;
		}
	}
}
