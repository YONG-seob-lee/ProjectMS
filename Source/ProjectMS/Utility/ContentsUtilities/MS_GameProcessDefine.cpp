// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_GameProcessDefine.h"

bool FMS_GameDate::operator==(const FMS_GameDate& aOther) const
{
	return Year == aOther.Year && Month == aOther.Month && Day == aOther.Day && DailyTimeZone == aOther.DailyTimeZone;
}

bool FMS_GameDate::operator!=(const FMS_GameDate& aOther) const
{
	return !(*this == aOther);
}

bool FMS_GameDate::operator<(const FMS_GameDate& aOther) const
{
	if (Year < aOther.Year)
	{
		return true;
	}
	else if (Year > aOther.Year)
	{
		return false;
	}
	else
	{
		if (Month < aOther.Month)
		{
			return true;
		}
		else if (Month > aOther.Month)
		{
			return false;
		}
		else
		{
			if (Day < aOther.Day)
			{
				return true;
			}
			else if (Day > aOther.Day)
			{
				return false;
			}
			else
			{
				if (DailyTimeZone < aOther.DailyTimeZone)
				{
					return true;
				}
				else if (DailyTimeZone > aOther.DailyTimeZone)
				{
					return false;
				}
				else
				{
					return false;
				}
			}
		}
	}
}

bool FMS_GameDate::operator>(const FMS_GameDate& aOther) const
{
	return (*this != aOther) && !(*this < aOther);
}

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

bool FMS_GameDate::IsNight(EMS_DailyTimeZone aTimeZone)
{
	return aTimeZone == EMS_DailyTimeZone::Evening
	|| aTimeZone == EMS_DailyTimeZone::EveningWork
	|| aTimeZone == EMS_DailyTimeZone::Night;
}
