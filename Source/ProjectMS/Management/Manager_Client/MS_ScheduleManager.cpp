// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ScheduleManager.h"

#include "MS_Define.h"
#include "MS_ItemManager.h"
#include "MS_WidgetManager.h"
#include "Table/Caches/MS_CommonCacheTable.h"
#include "Widget/Market/Modal/MS_MarketEndModal.h"

UMS_ScheduleManager::UMS_ScheduleManager()
{
	ScheduleManager = this;
}

void UMS_ScheduleManager::BuiltInInitialize()
{
	Super::BuiltInInitialize();
}

void UMS_ScheduleManager::Initialize()
{
	Super::Initialize();

	// "TEST" Step.1 : 최초로 서버에서 스케쥴 데이터를 받음.
	TakeTimeSchedule(nullptr);

	const TObjectPtr<UMS_CommonCacheTable> CommonTable = Cast<UMS_CommonCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::Common));
	MS_CHECK(CommonTable);

	IntervalSecondReal = CommonTable->GetParameter01(CommonContents::INTERVAL_SECOND);
}

void UMS_ScheduleManager::PostInitialize()
{
	Super::PostInitialize();
}

void UMS_ScheduleManager::PreFinalize()
{
	Super::PreFinalize();
}

void UMS_ScheduleManager::Finalize()
{
	Super::Finalize();
}

void UMS_ScheduleManager::BuiltInFinalize()
{
	Super::BuiltInFinalize();
}

void UMS_ScheduleManager::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
}

void UMS_ScheduleManager::TakeTimeSchedule(FMS_TimeSchedule* aTimeSchedule)
{
	// 나중에는 서버에서 전달받음.
	//TimeSchedule = aTimeSchedule;

	// 테스트용 데이터 생성.
	if(TimeSchedule == nullptr)
	{
		const TObjectPtr<UMS_CommonCacheTable> CommonTable = Cast<UMS_CommonCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::Common));
		MS_CHECK(CommonTable);
		
		TimeSchedule = new FMS_TimeSchedule(CommonTable->GetParameter01(CommonContents::DEFAULT_YEAR), CommonTable->GetParameter01(CommonContents::DEFAULT_MONTH), CommonTable->GetParameter01(CommonContents::DEFAULT_DAY) , CommonTable->GetParameter01(CommonContents::DEFAULT_MINUTE), EMS_ScheduleType::Prepare);
	}
	else
	{
		TimeSchedule = aTimeSchedule;
	}
	
	switch(TimeSchedule->GetCurrentScheduleType())
	{
	case EMS_ScheduleType::UpAndDown:
		{
			// 타이머를 매니저에서 돌려 (게임시간 1분당 현실시간 0.5초)
			PlayTimer(120);
			gWidgetMng.ShowToastMessage(TEXT("상하차가 시작되었습니다!"));
			break;
		}
	case EMS_ScheduleType::OpenMarket:
		{
			PlayTimer(660);
			gWidgetMng.ShowToastMessage(TEXT("매장 오픈~!! 달려보자고!"));
			break;
		}
	case EMS_ScheduleType::Prepare:
		{
			OnUpdateMinuteDelegate.Broadcast(TimeSchedule->GetMinute());
			gWidgetMng.ShowToastMessage(TEXT("준비 단계!"));
			break;
		}
	case EMS_ScheduleType::Deadline:
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

	OnUpdateScheduleDelegate.Broadcast(static_cast<int32>(TimeSchedule->GetCurrentScheduleType()));
}

void UMS_ScheduleManager::TakeItems(const TMap<int32, int32>* aTakeItems)
{
	gItemMng.SetItems(aTakeItems);
}

void UMS_ScheduleManager::TransferServer()
{
	gTestServer.RenewSchedule(TimeSchedule->GetNextScheduleType());
}

void UMS_ScheduleManager::TransferItemsToServer(const TMap<int32, int32>& aTransferItems)
{
	gTestServer.RenewItems(aTransferItems);
}

void UMS_ScheduleManager::SetTest()
{
	IntervalSecondReal = 30;
}

void UMS_ScheduleManager::PlayTimer(int32 aGamePlayMinute)
{
	if(IntervalSecondReal != 1)
	{
		CostTimeSecondReal = aGamePlayMinute;
	}
	else
	{
		CostTimeSecondReal = aGamePlayMinute / 2;
	}
	
	MS_LOG(TEXT("====== UMS_ScheduleManager::PlayTimer Start \' In Rate Time : %d \'"), CostTimeSecondReal);

	// Test용으로 나중에 InRate 인수에 IntervalSecond 로 대체
	GetWorld()->GetTimerManager().SetTimer(MarketPlayTimerHandle, this, &UMS_ScheduleManager::DuringTimer, 1, true);
}

void UMS_ScheduleManager::DuringTimer()
{
	CostTimeSecondReal -= IntervalSecondReal;
	
	TimeSchedule->UpdateMinute(IntervalSecondReal);
	OnUpdateMinuteDelegate.Broadcast(TimeSchedule->GetMinute());
	
	if(CostTimeSecondReal <= 0)
	{
		CostTimeSecondReal = 0;
			
		GetWorld()->GetTimerManager().ClearTimer(MarketPlayTimerHandle);
		EndTimer();
	}
}

void UMS_ScheduleManager::EndTimer()
{
	// "TEST" Step.3 게임플레이가 끝나면 서버로 보냄. 
	TransferServer();
}

UMS_ScheduleManager* UMS_ScheduleManager::GetInstance()
{
	return ScheduleManager; 
}
