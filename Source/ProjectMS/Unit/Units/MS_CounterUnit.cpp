// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_CounterUnit.h"

#include "MS_CustomerAIUnit.h"
#include "MS_StaffAIUnit.h"
#include "Mode/ModeObject/Container/MS_IssueTicketContainer.h"


bool UMS_CounterUnit::RegisterCustomerUnit(TWeakObjectPtr<UMS_CustomerAIUnit> aCustomerUnit)
{
	if (aCustomerUnit != nullptr)
	{
		CustomerUnits.AddUnique(aCustomerUnit);

		UpdateIssueTicket();

		return true;
	}

	return false;
}

void UMS_CounterUnit::UnregisterCustomerUnit(TWeakObjectPtr<UMS_CustomerAIUnit> aCustomerUnit)
{
	if (aCustomerUnit != nullptr)
	{
		CustomerUnits.RemoveSingle(aCustomerUnit);

		UpdateIssueTicket();
	}
}

bool UMS_CounterUnit::RegisterStaffUnit(TWeakObjectPtr<UMS_StaffAIUnit> aStaffUnit)
{
	if (aStaffUnit != nullptr && StaffUnit == nullptr)
	{
		if (IssueTickets.IsValidIndex(0))
		{
			if (IssueTickets[0]->GetStaffUnit() != nullptr && IssueTickets[0]->GetStaffUnit() != aStaffUnit)
			{
				return false;
			}
		}
		
		StaffUnit = aStaffUnit;

		if (IssueTickets.IsValidIndex(0))
		{
			StaffUnit->RegisterAsIssueTicketStaff(IssueTickets[0]);
		}

		return true;
	}

	return false;
}

void UMS_CounterUnit::UnregisterStaffUnit(TWeakObjectPtr<UMS_StaffAIUnit> aStaffUnit)
{
	if (aStaffUnit != nullptr && StaffUnit == aStaffUnit)
	{
		StaffUnit = nullptr;

		if (IssueTickets.IsValidIndex(0))
		{
			IssueTickets[0]->SetStaffUnit(nullptr);
		}
	}
}

TWeakObjectPtr<UMS_CustomerAIUnit> UMS_CounterUnit::GetFirstCustomerUnit() const
{
	if (CustomerUnits.IsValidIndex(0))
	{
		return CustomerUnits[0];
	}

	return nullptr;
}

TWeakObjectPtr<UMS_StaffAIUnit> UMS_CounterUnit::GetStaffUnit(bool bIncludeIssueStaffUnit /*= true*/) const
{
	if (StaffUnit != nullptr)
	{
		return StaffUnit;
	}

	if (bIncludeIssueStaffUnit)
	{
		if (IssueTickets.IsValidIndex(0))
		{
			return IssueTickets[0]->GetStaffUnit();
		}
	}

	return nullptr;
}

void UMS_CounterUnit::UpdateIssueTicket()
{
	Super::UpdateIssueTicket();

	if (CustomerUnits.Num() > 0)
	{
		if (IssueTickets.Num() == 0)
		{
			RegisterIssueTicket(EMS_StaffIssueType::Payment, 0);

			if (IssueTickets.IsValidIndex(0))
			{
				if (StaffUnit != nullptr)
				{
					StaffUnit->RegisterAsIssueTicketStaff(IssueTickets[0]);
				}
			}
		}
	}

	else
	{
		MS_ENSURE (IssueTickets.Num() == 0 || IssueTickets.Num() == 1);

		if (IssueTickets.IsValidIndex(0))
		{
			UnregisterIssueTicket(IssueTickets[0]);
		}
	}
}
