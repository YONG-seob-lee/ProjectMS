// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_GameProcessDefine.generated.h"

/**
 * 
 */
UENUM()
enum class EMS_ControllerModeType : uint8
{
	Normal = 0,
	Rotate = 1,
};

UENUM()
enum class EMS_ModeState : uint8
{
	Deactive = 0,
	Normal = 1,
	Construct = 2,
	RunMarket = 3,
};

UENUM()
enum class EMS_DailyTimeZone : uint8
{
	Morning = 0,
	DayTimeWork = 1,	// Market
	Evening = 3,
	EveningWork = 4,	// BlackMarket
	Night = 5,
};

UENUM()
enum class EMS_MarketScheduleEvent : uint8
{
	None = 0,
	Prepare = 1,
	TruckIn = 2,
	LoadingUnloading = 3,
	CustomerStart = 4,
	OpenMarket = 5,
	Deadline = 6,
	CloseMarket = 7,
};

UENUM()
enum class EMS_DayOfWeek : uint8
{
	Monday = 0,
	Tuesday = 1,
	Wednesday = 2,
	Thursday = 3,
	Friday = 4,
	Saturday = 5,
	Sunday = 6,
};

USTRUCT()
struct FMS_GameDate
{
	GENERATED_BODY()

	FMS_GameDate()
		: Year(0), Month(0), Day(0), DailyTimeZone(EMS_DailyTimeZone::Morning)
	{
	}

	FMS_GameDate(int32 aYear, int32 aMonth, int32 aDay)
		: Year(aYear), Month(aMonth), Day(aDay), DailyTimeZone(EMS_DailyTimeZone::Morning)
	{
	}
	
	FMS_GameDate(int32 aYear, int32 aMonth, int32 aDay, EMS_DailyTimeZone aDailyTimeZone)
		: Year(aYear), Month(aMonth), Day(aDay), DailyTimeZone(aDailyTimeZone)
	{
	}


	FMS_GameDate(FMS_GameDate aStartDate, int32 aPlusDay)
	{
		aStartDate.Day += aPlusDay;
		if(aStartDate.Day > 28)
		{
			aStartDate.Day = 1;
			aStartDate.Month += 1;
		}
		if(aStartDate.Month > 12)
		{
			aStartDate.Month = 1;
			aStartDate.Year += 1;
		}

		Day = aStartDate.Day;
		Month = aStartDate.Month;
		Year = aStartDate.Year;
		DailyTimeZone = aStartDate.DailyTimeZone;
	}

	bool operator==(const FMS_GameDate& aOther) const;
	bool operator!=(const FMS_GameDate& aOther) const;
	bool operator<(const FMS_GameDate& aOther) const;
	bool operator>(const FMS_GameDate& aOther) const;

	static int32 ConvertTimeZoneToMinute(EMS_DailyTimeZone aTimeZone);
	static bool IsRunningTimeZone(EMS_DailyTimeZone aTimeZone);
	static bool IsNight(EMS_DailyTimeZone aTimeZone);
	
	
public:
	UPROPERTY()
	int32 Year;

	UPROPERTY()
	int32 Month;

	UPROPERTY()
	int32 Day;
	
	UPROPERTY()
	EMS_DailyTimeZone DailyTimeZone;
};