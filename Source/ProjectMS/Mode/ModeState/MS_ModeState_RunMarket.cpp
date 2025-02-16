// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ModeState_RunMarket.h"

#include "MS_Define.h"
#include "Mode/ModeObject/Supervisor/Customer/MS_CustomerSupervisor.h"
#include "Mode/ModeObject/Supervisor/Staff/MS_StaffSupervisor.h"
#include "Manager_Client/MS_ModeManager.h"
#include "Manager_Client/MS_ScheduleManager.h"
#include "Mode/ModeObject/Container/MS_IssueTicketContainer.h"


UMS_ModeState_RunMarket::UMS_ModeState_RunMarket()
{
}

void UMS_ModeState_RunMarket::Initialize(uint8 aIndex, const FName& aName)
{
	Super::Initialize(aIndex, aName);

	ScheduleEvent.Empty();

	IssueTicketContainer = MS_NewObject<UMS_IssueTicketContainer>(this);
	if (IsValid(IssueTicketContainer))
	{
		IssueTicketContainer->Initialize();
	}
	
	StaffSupervisor = MS_NewObject<UMS_StaffSupervisor>(this);
	if (IsValid(StaffSupervisor))
	{
		StaffSupervisor->Initialize();
	}
	
	CustomerSupervisor = MS_NewObject<UMS_CustomerSupervisor>(this);
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

	if (IsValid(IssueTicketContainer))
	{
		IssueTicketContainer->Finalize();
		MS_DeleteObject(IssueTicketContainer);
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
	gScheduleMng.OnEndSchedule.AddUObject(this, &UMS_ModeState_RunMarket::EndSchedule);
	
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
	if (IsValid(CustomerSupervisor))
	{
		CustomerSupervisor->Finalize();
	}

	if (IsValid(StaffSupervisor))
	{
		StaffSupervisor->Finalize();
	}

	Super::Exit();
}

void UMS_ModeState_RunMarket::RunSchedule()
{
	gScheduleMng.RunSchedule(800, ScheduleEvent);
}

void UMS_ModeState_RunMarket::EndSchedule()
{
	// ToDo : Save Daily Data
	
	gScheduleMng.SetDailyTimeZone(EMS_DailyTimeZone::Evening);
	gModeMng.ChangeState(EMS_ModeState::Normal);
}

void UMS_ModeState_RunMarket::UpdateMinute(int32 aCurrentMinute)
{
}

void UMS_ModeState_RunMarket::UpdateScheduleEvent(int32 aScheduleEvent)
{
}
