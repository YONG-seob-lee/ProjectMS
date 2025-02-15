// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_ManagerBase.h"
#include "ContentsUtilities/MS_GameProcessDefine.h"
#include "MS_ScheduleManager.generated.h"

USTRUCT()
struct FMS_TimeSchedule
{
	GENERATED_BODY()
	
public:
	FMS_TimeSchedule()
	{}
	
	FMS_TimeSchedule(FMS_GameDate aGameDate, int32 aMinute, EMS_MarketNormalScheduleEvent aType)
	: GameDate(aGameDate), Minute(aMinute)
	{}
	
	FORCEINLINE void SetGameDate(FMS_GameDate aGameDate) { GameDate = aGameDate; }
	FORCEINLINE const FMS_GameDate& GetGameDate() const { return GameDate; }
	
	FORCEINLINE void SetDailyTimeZone(EMS_DailyTimeZone aDailyTimeZone) { GameDate.DailyTimeZone = aDailyTimeZone; }
	FORCEINLINE EMS_DailyTimeZone GetDailyTimeZone() const { return GameDate.DailyTimeZone; }
	
	FORCEINLINE void UpdateMinute(int32 aPlusMinute) { Minute += aPlusMinute; }
	FORCEINLINE void ResetMinute() { Minute = 0; }
	FORCEINLINE int32 GetMinute() const { return Minute; }
	void PassTheDay();

private:
	int32 GamePlayTimeSecond = 0;

	FMS_GameDate GameDate;
	int32 Minute = 0;
};

DECLARE_MULTICAST_DELEGATE_OneParam(FMS_OnUpdateGameDateDelegate, const FMS_GameDate&);
DECLARE_MULTICAST_DELEGATE_OneParam(FMS_OnUpdateMinuteDelegate, int32);
DECLARE_MULTICAST_DELEGATE_OneParam(FMS_OnUpdateScheduleEventDelegate, int32);
DECLARE_MULTICAST_DELEGATE(FMS_OnEndSchedule);

/**
 * 현실시간 1분당 게임시간 2시간이 경과되는걸로 확인
 * 이렇게 된다면 가장 평균적인 하루 플레이시간 07~20 사이 시간을 현실시간으로 계산하면 "6분30초" 가 된다.
 */
UCLASS()
class PROJECTMS_API UMS_ScheduleManager : public UMS_ManagerBase
{
	GENERATED_BODY()
public:
	UMS_ScheduleManager();

	virtual void BuiltInInitialize() override;
	virtual void Initialize() override;
	virtual void PostInitialize() override;
	virtual void PreFinalize() override;
	virtual void Finalize() override;
	virtual void BuiltInFinalize() override;

	virtual void Tick(float aDeltaTime) override;
	virtual void BeginPlay() override;
	
	const FMS_GameDate& GetGameDate() const;
	void SetDailyTimeZone(EMS_DailyTimeZone aDailyTimeZone);
	void PassTheDay();
	int32 GetMinute() const;

	void SaveGameDate() const;
	
	void TakeItems(const TMap<int32, int32>* aTakeItems);
	
	void RunSchedule(int32 aGamePlayMinute, const TMap<int32, int32>& aMinuteToScheduleEvent);
	
	bool IsNight() const;
	
	//test
	void SetTest();
	
	void GetScheduleData(TArray<class UMS_ScheduleDayElementData*>& aScheduleDayElementData);
	void GetFinancialData(TArray<class UMS_MonthFinancialElementData*>& Array) const;
	
private:
	void PlayTimer(int32 aGamePlayMinute);
	void DuringTimer();
	void EndTimer();


private:
	FTimerHandle MarketPlayTimerHandle;
	FMS_TimeSchedule TimeSchedule;

	int32 CostTimeSecondReal = 0;

	// 현실시간 1초에 게임시간이 몇분 지나가야하는지에 대한 멤버변수
	int32 IntervalSecondReal = 0;

	UPROPERTY()
	TArray<class UMS_ScheduleDayElementData*> ScheduleDayElementData;
	
	UPROPERTY()
	TArray<class UMS_MonthFinancialElementData*> MonthFinancialElementDatas;

	UPROPERTY()
	TMap<int32, int32> MinuteToScheduleEvent;

public:
	FMS_OnUpdateMinuteDelegate OnUpdateMinuteDelegate;
	FMS_OnUpdateScheduleEventDelegate OnUpdateScheduleEventDelegate;
	FMS_OnUpdateGameDateDelegate OnUpdateGameDateDelegate;
	FMS_OnEndSchedule OnEndSchedule;
	
	inline static TObjectPtr<UMS_ScheduleManager> ScheduleManager = nullptr;
	static UMS_ScheduleManager* GetInstance();
	
#define gScheduleMng (*UMS_ScheduleManager::GetInstance())
};
