// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ScheduleManager.h"

#include "MS_Define.h"
#include "MS_ItemManager.h"
#include "Controller/MS_PlayerController.h"
#include "PlayerState/MS_PlayerState.h"
#include "Table/Caches/MS_CommonCacheTable.h"
#include "Widget/ListViewElement/ElementData/MS_MonthFinancialElementData.h"
#include "Widget/ListViewElement/ElementData/MS_ScheduleDayElementData.h"


void FMS_TimeSchedule::PassTheDay()
{
	const TObjectPtr<UMS_CommonCacheTable> CommonTable = Cast<UMS_CommonCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::Common));
	MS_CHECK(CommonTable);
	
	GameDate.Day += 1;
	if(GameDate.Day > CommonTable->GetParameter01(CommonContents::DAYS_PER_ONEMONTH))
	{
		GameDate.Month +=1;
		GameDate.Day = 1;
		if(GameDate.Month > CommonTable->GetParameter01(CommonContents::MONTH_PER_ONEYEAR))
		{
			GameDate.Year +=1;
			GameDate.Month = 1;
		}
	}
}

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
	const TObjectPtr<UMS_CommonCacheTable> CommonTable = Cast<UMS_CommonCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::Common));
	MS_CHECK(CommonTable);

	IntervalSecondReal = CommonTable->GetParameter01(CommonContents::INTERVAL_SECOND);

	// for test
	for(int32 i = 1 ; i <= 28; i++)
	{
		UMS_ScheduleDayElementData* Data = MS_NewObject<UMS_ScheduleDayElementData>(this);
		Data->SetDays(i);
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
		ScheduleDayElementData.Emplace(Data);
	}
	
	// for test
	for(int32 i = 1 ; i <=6 ; i++)
	{
		UMS_MonthFinancialElementData* Data = MS_NewObject<UMS_MonthFinancialElementData>(this);
		Data->SetMonth(i);
		Data->SetCostBuildingStorage(1000 + i * 200);
		Data->SetMaintenanceCostMart(300 + i * 50);
		Data->SetLandPurchaseNumber(i + 1);
		Data->SetAverageAmount(30 + i * 2);
		Data->SetShelfCapacity(60 + 5 * i);
		Data->SetStaffSalary(800 + i * 100);
		Data->SetLoanInterest(600 + i * 100);
		MonthFinancialElementDatas.Emplace(Data);
	}
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
	for(const auto& Data : MonthFinancialElementDatas)
	{
		MS_DeleteObject(Data);
	}
	MonthFinancialElementDatas.Empty();

	for(const auto& Data : ScheduleDayElementData)
	{
		MS_DeleteObject(Data);
	}
	ScheduleDayElementData.Empty();
	
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

void UMS_ScheduleManager::BeginPlay()
{
	Super::BeginPlay();

	const TObjectPtr<UWorld> World = GetWorld();
	MS_CHECK(World);

	const TObjectPtr<AMS_PlayerController> PlayerController = World->GetFirstPlayerController<AMS_PlayerController>();
	MS_CHECK(PlayerController);
	
	AMS_PlayerState* PlayerState = PlayerController->GetPlayerState<AMS_PlayerState>();
	MS_CHECK(PlayerState);

	TimeSchedule.SetGameDate(PlayerState->GetGameDate());
	TimeSchedule.ResetMinute();

	OnUpdateGameDateDelegate.Broadcast(TimeSchedule.GetGameDate());
	OnUpdateMinuteDelegate.Broadcast(TimeSchedule.GetMinute());
}

const FMS_GameDate& UMS_ScheduleManager::GetGameDate() const
{
	return TimeSchedule.GetGameDate();
}

const EMS_DailyTimeZone UMS_ScheduleManager::GetDailyTimeZone() const
{
	return TimeSchedule.GetGameDate().DailyTimeZone;
}

void UMS_ScheduleManager::SetDailyTimeZone(EMS_DailyTimeZone aDailyTimeZone)
{
	TimeSchedule.SetDailyTimeZone(aDailyTimeZone);
	TimeSchedule.ResetMinute();

	SaveGameDate();
	
	OnUpdateGameDateDelegate.Broadcast(TimeSchedule.GetGameDate());
	OnUpdateMinuteDelegate.Broadcast(TimeSchedule.GetMinute());
}

void UMS_ScheduleManager::PassTheDay()
{
	TimeSchedule.PassTheDay();
	TimeSchedule.SetDailyTimeZone(EMS_DailyTimeZone::Morning);
	TimeSchedule.ResetMinute();
	
	SaveGameDate();
	
	OnUpdateGameDateDelegate.Broadcast(TimeSchedule.GetGameDate());
	OnUpdateMinuteDelegate.Broadcast(TimeSchedule.GetMinute());
}

int32 UMS_ScheduleManager::GetMinute() const
{
	return TimeSchedule.GetMinute();
}

void UMS_ScheduleManager::SaveGameDate() const
{
	const FMS_GameDate& GameDate = TimeSchedule.GetGameDate();

	if (GameDate == FMS_GameDate())
	{
		return;
	}
	
	const TObjectPtr<UWorld> World = GetWorld();
	MS_CHECK(World);

	const TObjectPtr<AMS_PlayerController> PlayerController = World->GetFirstPlayerController<AMS_PlayerController>();
	MS_CHECK(PlayerController);
	
	AMS_PlayerState* PlayerState = PlayerController->GetPlayerState<AMS_PlayerState>();
	MS_CHECK(PlayerState);

	PlayerState->SetGameDate(GameDate);
	PlayerState->SavePlayerData();
}

void UMS_ScheduleManager::TakeItems(const TMap<int32, int32>* aTakeItems)
{
	gItemMng.SetItems(aTakeItems);
}

void UMS_ScheduleManager::RunSchedule(int32 aGamePlayMinute, const TMap<int32, int32>& aMinuteToScheduleEvent)
{
	MinuteToScheduleEvent = aMinuteToScheduleEvent;

	TimeSchedule.ResetMinute();
	if (MinuteToScheduleEvent.Contains(0))
	{
		OnUpdateScheduleEventDelegate.Broadcast(*MinuteToScheduleEvent.Find(0));
	}
	
	PlayTimer(aGamePlayMinute);
}

void UMS_ScheduleManager::PauseSchedule()
{
	PauseTimer();
}

void UMS_ScheduleManager::ResumeSchedule(int32 aRenewalCostTime /* = 0 */)
{
	ResumeTimer(aRenewalCostTime);
}

void UMS_ScheduleManager::SetMultiplyIntervalSecondReal(int32 aMultiply)
{
	MultiplyIntervalSecondReal = aMultiply;
}

void UMS_ScheduleManager::GetScheduleData(TArray<UMS_ScheduleDayElementData*>& aScheduleDayElementData)
{
	aScheduleDayElementData.Empty();
	aScheduleDayElementData = ScheduleDayElementData;
}

void UMS_ScheduleManager::GetFinancialData(TArray<UMS_MonthFinancialElementData*>& aMonthFinancialElementDatas) const
{
	aMonthFinancialElementDatas.Empty();
	aMonthFinancialElementDatas = MonthFinancialElementDatas;
}

void UMS_ScheduleManager::PlayTimer(int32 aGamePlayMinute)
{
	// 현실시간 30초에 게임시간 1시간
	// 예시) 게임시간 2시간을 플레이하려면 현실시간 60초가 필요.
	CostTimeSecondReal = aGamePlayMinute;
	
	MS_LOG(TEXT("====== UMS_ScheduleManager::PlayTimer Start \' In Rate Time : %d \'"), CostTimeSecondReal);

	// Test용으로 나중에 InRate 인수에 IntervalSecond 로 대체
	GetWorld()->GetTimerManager().SetTimer(MarketPlayTimerHandle, this, &UMS_ScheduleManager::DuringTimer, 1, true);
}

void UMS_ScheduleManager::PauseTimer()
{
	GetWorld()->GetTimerManager().PauseTimer(MarketPlayTimerHandle);
}

void UMS_ScheduleManager::ResumeTimer(int32 aRenewalCostTime)
{
	CostTimeSecondReal = ScheduleDefault::GamePlayMinute - aRenewalCostTime;
	TimeSchedule.ForcedRenewalMinute(aRenewalCostTime); 
	GetWorld()->GetTimerManager().UnPauseTimer(MarketPlayTimerHandle);
}

void UMS_ScheduleManager::DuringTimer()
{
	int32 PreMinute = TimeSchedule.GetMinute();

	int32 CalcIntervalSecondReal = IntervalSecondReal * MultiplyIntervalSecondReal;
	CostTimeSecondReal -= CalcIntervalSecondReal;
	
	TimeSchedule.UpdateMinute(CalcIntervalSecondReal);
	int32 NewMinitue = TimeSchedule.GetMinute();
	
	OnUpdateMinuteDelegate.Broadcast(NewMinitue);

	for (int32 i = PreMinute + 1; i <= NewMinitue; ++i)
	{
		if (MinuteToScheduleEvent.Contains(i))
		{
			OnUpdateScheduleEventDelegate.Broadcast(*MinuteToScheduleEvent.Find(i));
		}
	}
	
	if(CostTimeSecondReal <= 0)
	{
		CostTimeSecondReal = 0;
			
		GetWorld()->GetTimerManager().ClearTimer(MarketPlayTimerHandle);
		EndTimer();
	}
}

void UMS_ScheduleManager::EndTimer()
{
	OnEndSchedule.Broadcast();
}

UMS_ScheduleManager* UMS_ScheduleManager::GetInstance()
{
	return ScheduleManager; 
}
