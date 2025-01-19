// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_TestServer.h"

#include "Manager_Client/MS_ItemManager.h"
#include "Manager_Client/MS_ScheduleManager.h"
#include "Table/Caches/MS_CommonCacheTable.h"
#include "Widget/ListViewElement/ElementData/MS_StaffPropertyElementData.h"

void FMS_TimeSchedule::SetScheduleType(EMS_ScheduleType aType)
{
	const TObjectPtr<UMS_CommonCacheTable> CommonTable = Cast<UMS_CommonCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::Common));
	MS_CHECK(CommonTable);

	const int32 SecondPerOneMinute = CommonTable->GetParameter01(CommonContents::SECONDS_PER_ONEMINUTE);
	switch(aType)
	{
	case EMS_ScheduleType::Prepare:
		{
			if(ScheduleType != EMS_ScheduleType::Deadline)
			{
				MS_LOG(TEXT("Miss Schedule! "));
				return;
			}
			
			PassTheDay();
			Minute = 7 * SecondPerOneMinute;
			break;
		}
	case EMS_ScheduleType::UpAndDown:
		{
			if(ScheduleType != static_cast<EMS_ScheduleType>(static_cast<int32>(aType) - 1))
			{
				MS_LOG(TEXT("Miss Schedule! "));
				return;
			}
			Minute = 7 * SecondPerOneMinute;
			break;
		}
	case EMS_ScheduleType::OpenMarket:
		{
			if(ScheduleType != static_cast<EMS_ScheduleType>(static_cast<int32>(aType) - 1))
			{
				MS_LOG(TEXT("Miss Schedule! "));
				return;
			}
			Minute = 9 * SecondPerOneMinute;
			break;
		}
	case EMS_ScheduleType::Deadline:
		{
			if(ScheduleType != static_cast<EMS_ScheduleType>(static_cast<int32>(aType) - 1))
			{
				MS_LOG(TEXT("Miss Schedule! "));
				return;
			}
			Minute = 20 * SecondPerOneMinute;
			break;
		}
	default:
		{
			break;
		}
	}
	
	ScheduleType = aType;
}

EMS_ScheduleType FMS_TimeSchedule::GetNextScheduleType()
{
	switch(ScheduleType)
	{
	case EMS_ScheduleType::Deadline:
		{
			return EMS_ScheduleType::Prepare;
		}
	default:
		{
			return static_cast<EMS_ScheduleType>(static_cast<int32>(ScheduleType) + 1);
		}
	}
}

void FMS_TimeSchedule::PassTheDay()
{
	const TObjectPtr<UMS_CommonCacheTable> CommonTable = Cast<UMS_CommonCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::Common));
	MS_CHECK(CommonTable);
	
	Day += 1;
	if(Day > CommonTable->GetParameter01(CommonContents::DAYS_PER_ONEMONTH))
	{
		Month +=1;
		Day = 1;
		if(Month > CommonTable->GetParameter01(CommonContents::MONTH_PER_ONEYEAR))
		{
			Year +=1;
			Month = 1;
		}
	}
}

void UMS_TestServer::Initialize()
{
	TestServer = this;
}

void UMS_TestServer::Destroy()
{
}

void UMS_TestServer::RenewSchedule(EMS_ScheduleType aType)
{
	CurrentTime.SetScheduleType(aType);

	// "TEST" Step.4 : 서버에서 클라로 전송.
	gScheduleMng.TakeTimeSchedule(&CurrentTime);
}

void UMS_TestServer::RenewItems(TMap<int32, int32> aTransferItems)
{
	for(const auto& TransferItem : aTransferItems)
	{
		if(int32* TargetItem = Items.Find(TransferItem.Key))
		{
			*TargetItem += TransferItem.Value; 
		}
		else
		{
			Items.Emplace(TransferItem.Key, TransferItem.Value);
		}
	}
	
	// "TEST" Step.4 : 서버에서 클라로 전송.
	gItemMng.SetItems(&Items);
}

void UMS_TestServer::RenewStaff(int32 aStaffId)
{
	if(UMS_StaffPropertyElementData* StaffProperty = MS_NewObject<UMS_StaffPropertyElementData>())
	{
		StaffPropertys.Emplace(aStaffId, StaffProperty);
		StaffProperty->SetStaffId(aStaffId);
		StaffProperty->SetHP(100);
		StaffProperty->SetCondition(100);
		StaffProperty->SetFeeling(1);
		StaffProperty->SetExpirationDate(5, 31);
	}
	gItemMng.SetStaffProperty(aStaffId, StaffPropertys[aStaffId]);
}

UMS_TestServer* UMS_TestServer::GetInstance()
{
	return TestServer;
}
