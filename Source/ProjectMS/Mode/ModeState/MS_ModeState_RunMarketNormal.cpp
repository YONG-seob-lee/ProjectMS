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

	ScheduleEvent.Emplace(0, static_cast<int32>(EMS_MarketNormalScheduleEvent::Prepare));
	ScheduleEvent.Emplace(20, static_cast<int32>(EMS_MarketNormalScheduleEvent::LoadingUnloading));
	ScheduleEvent.Emplace(140, static_cast<int32>(EMS_MarketNormalScheduleEvent::OpenMarket));
	ScheduleEvent.Emplace(770, static_cast<int32>(EMS_MarketNormalScheduleEvent::Deadline));
	ScheduleEvent.Emplace(800, static_cast<int32>(EMS_MarketNormalScheduleEvent::CloseMarket));
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
			gWidgetMng.ShowToastMessage(TEXT("준비 단계! 출근 시간은 7:00입니다."));
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
	case EMS_MarketNormalScheduleEvent::Deadline:
		{
			gWidgetMng.ShowToastMessage(TEXT("곧 마켓 영업이 끝납니다. 계산하고 나가주세요~!"));
			break;
		}
	case EMS_MarketNormalScheduleEvent::CloseMarket:
		{
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
