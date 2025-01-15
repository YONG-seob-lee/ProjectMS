// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_ManagerBase.h"
#include "MS_ScheduleManager.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FMS_OnUpdateScheduleDelegate, int32);
DECLARE_MULTICAST_DELEGATE_OneParam(FMS_OnUpdateMinuteDelegate, int32);

UENUM()
enum class EMS_ScheduleType
{
	Prepare = 0,
	UpAndDown = 1,
	OpenMarket = 2,
	Deadline = 3,
	//BlackMarket = 4,
};

struct FMS_TimeSchedule
{
public:
	FMS_TimeSchedule() {}
	FMS_TimeSchedule(int32 aYear, int32 aMonth, int32 aDay, int32 aMinute, EMS_ScheduleType aType) : ScheduleType(aType), Year(aYear), Month(aMonth), Day(aDay), Minute(aMinute) {}

	void SetScheduleType(EMS_ScheduleType aType);
	FORCEINLINE EMS_ScheduleType GetCurrentScheduleType() const { return ScheduleType; }
	FORCEINLINE void UpdateMinute(int32 aPlusMinute) { Minute += aPlusMinute; }
	FORCEINLINE int32 GetMinute() const { return Minute; }
	
	EMS_ScheduleType GetNextScheduleType();

private:
	void PassTheDay();
	
	EMS_ScheduleType ScheduleType = EMS_ScheduleType::Prepare;
	
	int32 GamePlayTimeSecond = 0;

	int32 Year = 0;
	int32 Month = 0;
	int32 Day = 0;
	int32 Minute = 0;
};

struct FMS_TestServerScheduler
{
public:
	FMS_TestServerScheduler() {}

	void SetManager(class UMS_ScheduleManager* aManager) { Manager = aManager; }
	
	void RenewSchedule(EMS_ScheduleType aType);
	void RenewItems(TMap<int32, int32> aTransferItems);

	FORCEINLINE FMS_TimeSchedule TransferSchedule() const { return CurrentTime; }

private:
	FMS_TimeSchedule CurrentTime;
	TMap<int32, int32> Items;

	class UMS_ScheduleManager* Manager = nullptr; 
};

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

	virtual void Tick(float aDeltaTime);

	void TakeTimeSchedule(FMS_TimeSchedule* aTimeSchedule);
	void TakeItems(const TMap<int32, int32>* aTakeItems);

	void TransferServer();
	void TransferItemsToServer(const TMap<int32, int32>& aTransferItems);

	//test
	void SetTest();

	FMS_OnUpdateScheduleDelegate OnUpdateScheduleDelegate;
	FMS_OnUpdateMinuteDelegate OnUpdateMinuteDelegate;
	
private:
	void PlayTimer(int32 aGamePlayMinute);
	void DuringTimer();
	void EndTimer();
	
	FTimerHandle MarketPlayTimerHandle;
	FMS_TimeSchedule* TimeSchedule = nullptr;

	int32 CostTimeSecondReal = 0;
	int32 IntervalSecondReal = 0; 
	// Test
	FMS_TestServerScheduler TestServer;

public:
	inline static TObjectPtr<UMS_ScheduleManager> ScheduleManager = nullptr;
	static UMS_ScheduleManager* GetInstance();
	
#define gScheduleMng (*UMS_ScheduleManager::GetInstance())
};
