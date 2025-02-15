// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_GameProcessDefine.h"

int32 FMS_GameDate::ConvertTimeZoneToMinute(EMS_DailyTimeZone aTimeZone)
{
	switch (aTimeZone)
	{
	case EMS_DailyTimeZone::Morning :
		{
			return 360;		//6:00
		}
	case EMS_DailyTimeZone::DayTimeWork :
		{
			return 400;		// 6:40
		}
	case EMS_DailyTimeZone::Evening :
		{
			return 1200;	// 20:00
		}
	case EMS_DailyTimeZone::EveningWork :
		{
			return 1230;	// 20:30
		}
	case EMS_DailyTimeZone::Night :
		{
			return 1380;	// 23:00
		}
	}

	return 0;
}

bool FMS_GameDate::IsRunningTimeZone(EMS_DailyTimeZone aTimeZone)
{
	switch (aTimeZone)
	{
	case EMS_DailyTimeZone::Morning :
	case EMS_DailyTimeZone::Evening :
	case EMS_DailyTimeZone::Night :
		{
			return false;
		}
	case EMS_DailyTimeZone::DayTimeWork :
	case EMS_DailyTimeZone::EveningWork :
		{
			return true;
		}
	}

	return false;
}
