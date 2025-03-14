// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_ManagerBase.h"
#include "ContentsUtilities/MS_GameProcessDefine.h"
#include "MS_ScheduleManager.generated.h"

USTRUCT()
struct FMS_SettlementSheet
{
	GENERATED_BODY()
public:
	FMS_SettlementSheet() {}

	FMS_SettlementSheet(FMS_GameDate aDate) : Date(aDate) {} 
	FMS_SettlementSheet(FMS_GameDate aDate, int32 aSellItemPrice, int32 aOrderFurnitures, int32 aOrderItems, int32 aElectricityBill,
						int32 aPersonalExpanses, int32 aLoanInterest)
			: Date(aDate), SellItemPrice(aSellItemPrice), OrderFurnitures(aOrderFurnitures), OrderItems(aOrderItems)
				, ElectricityBill(aElectricityBill), PersonalExpanses(aPersonalExpanses)
				, LoanInterest(aLoanInterest)
	{
		TotalAggregate = aSellItemPrice - aOrderFurnitures - aOrderItems - aElectricityBill - aPersonalExpanses - aLoanInterest;
	}

	UPROPERTY()
	FMS_GameDate Date = FMS_GameDate();
	UPROPERTY()
	int32 SellItemPrice = 0;
	UPROPERTY()
	int32 OrderFurnitures = 0;
	UPROPERTY()
	int32 OrderItems = 0;
	UPROPERTY()
	int32 ElectricityBill = 0;
	UPROPERTY()
	int32 PurchaseZone = 0;
	UPROPERTY()
	int32 PersonalExpanses = 0;
	UPROPERTY()
	int32 LoanInterest = 0;
	UPROPERTY()
	int32 TotalAggregate = 0;
};

USTRUCT()
struct FMS_TimeSchedule
{
	GENERATED_BODY()
	
public:
	FMS_TimeSchedule()
	{}
	
	FMS_TimeSchedule(FMS_GameDate aGameDate, int32 aMinute, EMS_MarketScheduleEvent aType)
	: GameDate(aGameDate), Minute(aMinute)
	{}
	
	FORCEINLINE void SetGameDate(FMS_GameDate aGameDate) { GameDate = aGameDate; }
	FORCEINLINE const FMS_GameDate& GetGameDate() const { return GameDate; }
	
	FORCEINLINE void SetDailyTimeZone(EMS_DailyTimeZone aDailyTimeZone) { GameDate.DailyTimeZone = aDailyTimeZone; }
	FORCEINLINE EMS_DailyTimeZone GetDailyTimeZone() const { return GameDate.DailyTimeZone; }

	FORCEINLINE void ForcedRenewalMinute(int32 aRenewalMinute) { Minute = aRenewalMinute; }
	FORCEINLINE void UpdateMinute(int32 aPlusMinute) { Minute += aPlusMinute; }
	FORCEINLINE void ResetMinute() { Minute = 0; }
	FORCEINLINE int32 GetMinute() const { return Minute; }
	void PassTheDay();

private:
	int32 GamePlayTimeSecond = 0;

	FMS_GameDate GameDate;
	int32 Minute = 0;
};

namespace ScheduleDefault
{
	constexpr int32 GamePlayMinute = 820;
}

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

	virtual auto BeginPlay() -> void override;
	virtual void Tick(float aDeltaTime) override;
	
	const FMS_GameDate& GetGameDate() const;
	EMS_DailyTimeZone GetDailyTimeZone() const;
	void SetDailyTimeZone(EMS_DailyTimeZone aDailyTimeZone);
	void PassTheDay();
	int32 GetMinute() const;

	void SaveGameDate() const;
	
	void RunSchedule(int32 aGamePlayMinute, const TMap<int32, int32>& aMinuteToScheduleEvent);
	void PauseSchedule();
	void ResumeSchedule(int32 aRenewalCostTime = 0);
	
	void SetMultiplyIntervalSecondReal(int32 aMultiply);
	
	void GetFinancialData(TArray<class UMS_MonthFinancialElementData*>& Array) const;

	bool IsOverTime(EMS_MarketScheduleEvent ScheduleEvent);

	// Diary
	FORCEINLINE void UpdateDiary(const TArray<FMS_SettlementSheet>& aDiary) { Diary = aDiary; }
	void UpdateDailySheet();
	void WriteDiary() const;
	void SetupNewDiary() const;
	void GetSettlementSheet(const FMS_GameDate& aGameDate, FMS_SettlementSheet& Sheet);
	void CollectMonthDiarySheet();
	
	FORCEINLINE FMS_SettlementSheet& GetDailySheet() { return DailySheet; }
private:
	void PlayTimer(int32 aGamePlayMinute);
	void PauseTimer();
	void ResumeTimer(int32 aRenewalCostTime);
	void DuringTimer();
	void EndTimer();


private:
	FTimerHandle MarketPlayTimerHandle;
	FMS_TimeSchedule TimeSchedule;

	int32 CostTimeSecondReal = 0;

	// 현실시간 1초에 게임시간이 몇분 지나가야하는지에 대한 멤버변수
	int32 IntervalSecondReal = 0;
	int32 MultiplyIntervalSecondReal = 1;
	
	UPROPERTY()
	TMap<int32, class UMS_MonthFinancialElementData*> MonthFinancialElementDatas;

	UPROPERTY()
	TMap<int32, int32> MinuteToScheduleEvent;

	UPROPERTY()
	TArray<FMS_SettlementSheet> Diary;
	
	FMS_SettlementSheet DailySheet = FMS_SettlementSheet();
public:
	FMS_OnUpdateMinuteDelegate OnUpdateMinuteDelegate;
	FMS_OnUpdateScheduleEventDelegate OnUpdateScheduleEventDelegate;
	FMS_OnUpdateGameDateDelegate OnUpdateGameDateDelegate;
	FMS_OnEndSchedule OnEndSchedule;
	
	inline static TObjectPtr<UMS_ScheduleManager> ScheduleManager = nullptr;
	static UMS_ScheduleManager* GetInstance();
	
#define gScheduleMng (*UMS_ScheduleManager::GetInstance())
};
