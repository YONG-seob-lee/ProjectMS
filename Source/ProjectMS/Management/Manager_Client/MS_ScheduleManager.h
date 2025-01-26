// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_ManagerBase.h"
#include "Component/MS_TestServer.h"
#include "MS_ScheduleManager.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FMS_OnUpdateScheduleDelegate, int32);
DECLARE_MULTICAST_DELEGATE_OneParam(FMS_OnUpdateMinuteDelegate, int32);

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

	int32 GetCurrentMinute() const;
	
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

	// 현실시간 1초에 게임시간이 몇분 지나가야하는지에 대한 멤버변수
	int32 IntervalSecondReal = 0; 

public:
	inline static TObjectPtr<UMS_ScheduleManager> ScheduleManager = nullptr;
	static UMS_ScheduleManager* GetInstance();
	
#define gScheduleMng (*UMS_ScheduleManager::GetInstance())
};
