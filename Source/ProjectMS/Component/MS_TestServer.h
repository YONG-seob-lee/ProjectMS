// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MS_TestServer.generated.h"

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

struct FMS_StaffProperty
{
public:
	FMS_StaffProperty();
	FMS_StaffProperty(int32 aStaffId) : StaffId(aStaffId) {}

private:
	int32 StaffId = INDEX_NONE;
	
};

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_TestServer : public UObject
{
	GENERATED_BODY()
public:
	void Initialize();
	void Destroy();

	// Schedule
	void RenewSchedule(EMS_ScheduleType aType);
	FORCEINLINE FMS_TimeSchedule TransferSchedule() const { return CurrentTime; }

	// Order Item
	void RenewItems(TMap<int32, int32> aTransferItems);


	// Staff
	void RenewStaff(int32 aStaffId);
	
private:
	// Schedule
	FMS_TimeSchedule CurrentTime;

	// Order Item
	TMap<int32, int32> Items;

	// Staff
	TMap<int32, FMS_StaffProperty> StaffPropertys;
public:
	inline static TObjectPtr<UMS_TestServer> TestServer = nullptr;
	static UMS_TestServer* GetInstance();
	
#define gTestServer (*UMS_TestServer::GetInstance())
};
