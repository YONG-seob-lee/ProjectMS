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
	RunMarketNormal = 3,
};

UENUM()
enum class EMS_DailyTimeZone : int32
{
	Morning = 0,
	DayTimeWork = 1,	// Market
	Evening = 3,
	EveningWork = 4,	// BlackMarket
	Night = 5,
};

UENUM()
enum class EMS_MarketNormalScheduleEvent
{
	None = 0,
	Prepare = 1,
	LoadingUnloading = 2,
	OpenMarket = 3,
	Deadline = 4,
	CloseMarket = 5,
};

USTRUCT(BlueprintType)
struct FMS_GameDate
{
	GENERATED_BODY()

	FMS_GameDate()
		: Year(0), Month(0), Day(0), DailyTimeZone(static_cast<int32>(EMS_DailyTimeZone::Morning))
	{
	}

	FMS_GameDate(int32 aYear, int32 aMonth, int32 aDay, EMS_DailyTimeZone aDailyTimeZone)
	: Year(aYear), Month(aMonth), Day(aDay), DailyTimeZone(static_cast<int32>(aDailyTimeZone))
	{
	}

	bool operator==(const FMS_GameDate& aOther) const;
	bool operator!=(const FMS_GameDate& aOther) const;
	bool operator<(const FMS_GameDate& aOther) const;
	bool operator>(const FMS_GameDate& aOther) const;

	static int32 ConvertTimeZoneToMinute(EMS_DailyTimeZone aTimeZone);
	static bool IsRunningTimeZone(EMS_DailyTimeZone aTimeZone);

	EMS_DailyTimeZone GetDailyTimeZone() const { return static_cast<EMS_DailyTimeZone>(DailyTimeZone); }
	void SetDailyTimeZone(EMS_DailyTimeZone aDailyTimeZone) { DailyTimeZone = static_cast<int32>(aDailyTimeZone); }

public:
	int32 Year;
	int32 Month;
	int32 Day;

	int32 DailyTimeZone;
};