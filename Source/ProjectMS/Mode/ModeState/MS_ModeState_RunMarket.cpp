// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ModeState_RunMarket.h"

#include "MS_Define.h"
#include "AI/AISupervisor/Customer/CustomerSupervisor.h"
#include "AI/AISupervisor/Staff/StaffSupervisor.h"
#include "Manager_Client/MS_ScheduleManager.h"


UMS_ModeState_RunMarket::UMS_ModeState_RunMarket()
{
}

void UMS_ModeState_RunMarket::Initialize(uint8 aIndex, const FName& aName)
{
	Super::Initialize(aIndex, aName);

	StaffSupervisor = MS_NewObject<UStaffSupervisor>(this);
	if (IsValid(StaffSupervisor))
	{
		StaffSupervisor->Initialize();
	}
	
	CustomerSupervisor = MS_NewObject<UCustomerSupervisor>(this);
	if (IsValid(CustomerSupervisor))
	{
		CustomerSupervisor->Initialize();
	}
}

void UMS_ModeState_RunMarket::Finalize()
{
	if (IsValid(CustomerSupervisor))
	{
		CustomerSupervisor->Finalize();
		MS_DeleteObject(CustomerSupervisor);
	}

	if (IsValid(StaffSupervisor))
	{
		StaffSupervisor->Finalize();
		MS_DeleteObject(StaffSupervisor);
	}
	
	Super::Finalize();
}

void UMS_ModeState_RunMarket::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);

	if (IsValid(StaffSupervisor))
	{
		StaffSupervisor->Tick(aDeltaTime);
	}
	
	if (IsValid(CustomerSupervisor))
	{
		CustomerSupervisor->Tick(aDeltaTime);
	}
}

void UMS_ModeState_RunMarket::Begin()
{
	Super::Begin();

	gScheduleMng.SetDailyTimeZone(EMS_DailyTimeZone::DayTimeWork);
	gScheduleMng.OnUpdateMinuteDelegate.AddUObject(this, &UMS_ModeState_RunMarket::UpdateMinute);
	gScheduleMng.OnUpdateScheduleEventDelegate.AddUObject(this, &UMS_ModeState_RunMarket::UpdateScheduleEvent);

	GetWorld()->GetTimerManager().SetTimer(DelayTimerHandle, this, &UMS_ModeState_RunMarket::RunSchedule, 3, false);
	
	if (IsValid(StaffSupervisor))
	{
		StaffSupervisor->Begin();
	}
	
	if (IsValid(CustomerSupervisor))
	{
		CustomerSupervisor->Begin();
	}
}

void UMS_ModeState_RunMarket::Exit()
{
	Super::Exit();

	if (IsValid(CustomerSupervisor))
	{
		CustomerSupervisor->Finalize();
	}

	if (IsValid(StaffSupervisor))
	{
		StaffSupervisor->Finalize();
	}
}

void UMS_ModeState_RunMarket::RunSchedule()
{
	gScheduleMng.RunSchedule(800, TMap<int32, int32>());
}

void UMS_ModeState_RunMarket::UpdateMinute(int32 aCurrentMinute)
{
}

void UMS_ModeState_RunMarket::UpdateScheduleEvent(int32 aScheduleEvent)
{
}
