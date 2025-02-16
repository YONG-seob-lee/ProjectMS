// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_IssueTicketContainer.h"

#include "MS_UnitBase.h"
#include "Units/MS_StaffCharacterUnit.h"


UMS_IssueTicket::UMS_IssueTicket()
	: IssueType(EMS_IssueType::None), RequestUnit(nullptr), RequestSlot(INDEX_NONE)
{
}

void UMS_IssueTicket::Initialize(EMS_IssueType aIssueType, TWeakObjectPtr<UMS_UnitBase> aRequestUnit,
	int32 aRequestSlot)
{
	IssueType = aIssueType;
	RequestUnit = aRequestUnit;
	RequestSlot = aRequestSlot;
}

void UMS_IssueTicket::Finalize()
{
	if (StaffUnit != nullptr)
	{
		StaffUnit->OnUnregistedAsIssueTicketStaff();
	}
}

void UMS_IssueTicket::SetStaffUnit(TWeakObjectPtr<UMS_StaffCharacterUnit> aStaffUnit)
{
	StaffUnit = aStaffUnit;
}

int32 UMS_IssueTicket::GetPriority() const
{
	return static_cast<int32>(IssueType);
}

bool UMS_IssueTicket::IsSameIssue(EMS_IssueType aIssueType, MS_Handle aUnitHandle, int32 aRequestSlot) const
{
	return IssueType == aIssueType
	&& RequestUnit->GetUnitHandle() == aUnitHandle
	&& RequestSlot == aRequestSlot;
}

bool UMS_IssueTicket::IsSameIssue(EMS_IssueType aIssueType, TWeakObjectPtr<UMS_UnitBase> aRequestUnit,
                                  int32 aRequestSlot) const
{
	return IssueType == aIssueType
		&& RequestUnit == aRequestUnit
		&& RequestSlot == aRequestSlot;
}

bool UMS_IssueTicket::IsSameIssue(const TWeakObjectPtr<UMS_IssueTicket> aOther) const
{
	if (aOther == nullptr)
	{
		MS_ENSURE(false);
		return false;
	}

	return IssueType == aOther->IssueType
		&& RequestUnit == aOther->RequestUnit
		&& RequestSlot == aOther->RequestSlot;
}

bool UMS_IssueTicket::AllowSameIssue(EMS_IssueType aIssueType)
{
	// ToDo : 타입이 추가된 후 중복 발행이 가능한 이슈는 true
	return false;
}

UMS_IssueTicketContainer::UMS_IssueTicketContainer()
{
	IssueTickets.Empty();
}

void UMS_IssueTicketContainer::Initialize()
{
}

void UMS_IssueTicketContainer::Finalize()
{
	UnregisterAllIssueTickets();
}

void UMS_IssueTicketContainer::RegisterIssueTicket(EMS_IssueType aIssueType,
	TWeakObjectPtr<UMS_UnitBase> aRequestUnit /*= nullptr*/, int32 aSlotId /*= INDEX_NONE*/)
{
	if (!UMS_IssueTicket::AllowSameIssue(aIssueType))
	{
		for (UMS_IssueTicket* TestTicket : IssueTickets)
		{
			if (IsValid(TestTicket))
			{
				if (TestTicket->IsSameIssue(aIssueType, aRequestUnit, aSlotId))
				{
					return;
				}
			}
		}
	}
	
	UMS_IssueTicket* IssueTicket = NewObject<UMS_IssueTicket>(this);
	if (IssueTicket)
	{
		IssueTicket->Initialize(aIssueType, aRequestUnit, aSlotId);
		IssueTickets.Emplace(IssueTicket);
	}
}

void UMS_IssueTicketContainer::UnregisterAllIssueTickets()
{
	for (int32 i = IssueTickets.Num() - 1; i >= 0; --i)
	{
		if (IsValid(IssueTickets[i]))
		{
			IssueTickets[i]->Finalize();
			MS_DeleteObject(IssueTickets[i]);
		}
	}
	
	IssueTickets.Empty();
}

void UMS_IssueTicketContainer::UnregisterUnitIssueTickets(MS_Handle aUnitHandle)
{
	for (int32 i = IssueTickets.Num() - 1; i >= 0; --i)
	{
		if (IsValid(IssueTickets[i]))
		{
			TWeakObjectPtr<UMS_UnitBase> RequestUnit = IssueTickets[i]->GetRequestUnit();
		
			if (RequestUnit == nullptr)
			{
				continue;
			}
		
			if (RequestUnit->GetUnitHandle() == aUnitHandle)
			{
				IssueTickets[i]->Finalize();
				MS_DeleteObject(IssueTickets[i]);
				IssueTickets.RemoveAt(i);
			}
		}
	}
}

void UMS_IssueTicketContainer::UnregisterUnitSlotIssueTickets(MS_Handle aUnitHandle, int32 aSlotId)
{
	for (int32 i = IssueTickets.Num() - 1; i >= 0; --i)
	{
		if (IsValid(IssueTickets[i]))
		{
			TWeakObjectPtr<UMS_UnitBase> RequestUnit = IssueTickets[i]->GetRequestUnit();
			int32 RequestSlot = IssueTickets[i]->GetRequestSlot();
			
			if (RequestUnit == nullptr)
			{
				continue;
			}
		
			if (RequestUnit->GetUnitHandle() == aUnitHandle && RequestSlot == aSlotId)
			{
				IssueTickets[i]->Finalize();
				MS_DeleteObject(IssueTickets[i]);
				IssueTickets.RemoveAt(i);
			}
		}
	}
}

void UMS_IssueTicketContainer::UnregisterIssueTicket(TWeakObjectPtr<UMS_IssueTicket> aIssueTicket)
{
	for (int32 i = IssueTickets.Num() - 1; i >= 0; --i)
	{
		if (IsValid(IssueTickets[i]))
		{
			if (IssueTickets[i] == aIssueTicket)
			{
				IssueTickets[i]->Finalize();
				MS_DeleteObject(IssueTickets[i]);
				IssueTickets.RemoveAt(i);
			
				return;
			}
		}
	}
}

void UMS_IssueTicketContainer::GetTypeIssueTickets(TArray<TWeakObjectPtr<UMS_IssueTicket>>& aOutTickets,
	EMS_IssueType aIssueType)
{
	aOutTickets.Empty();

	for (UMS_IssueTicket* IssueTicket : IssueTickets)
	{
		if (IsValid(IssueTicket))
		{
			EMS_IssueType IssueType = IssueTicket->GetIssueType();
		
			if (IssueType == aIssueType)
			{
				aOutTickets.Emplace(IssueTicket);
			}
		}
	}
}

void UMS_IssueTicketContainer::GetUnitIssueTickets(TArray<TWeakObjectPtr<UMS_IssueTicket>>& aOutTickets,
                                                   MS_Handle aUnitHandle)
{
	aOutTickets.Empty();

	for (UMS_IssueTicket* IssueTicket : IssueTickets)
	{
		if (IsValid(IssueTicket))
		{
			TWeakObjectPtr<UMS_UnitBase> RequestUnit = IssueTicket->GetRequestUnit();
		
			if (RequestUnit == nullptr)
			{
				return;
			}
		
			if (RequestUnit->GetUnitHandle() == aUnitHandle)
			{
				aOutTickets.Emplace(IssueTicket);
			}
		}
	}
}

void UMS_IssueTicketContainer::GetUnitIssueTickets(TArray<TWeakObjectPtr<UMS_IssueTicket>>& aOutTickets,
	MS_Handle aUnitHandle, int32 aSlotId)
{
	aOutTickets.Empty();

	for (UMS_IssueTicket* IssueTicket : IssueTickets)
	{
		if (IsValid(IssueTicket))
		{
			TWeakObjectPtr<UMS_UnitBase> RequestUnit = IssueTicket->GetRequestUnit();
			int32 RequestSlot = IssueTicket->GetRequestSlot();
			
			if (RequestUnit == nullptr)
			{
				return;
			}
			
			if (RequestUnit->GetUnitHandle() == aUnitHandle && RequestSlot == aSlotId)
			{
				aOutTickets.Emplace(IssueTicket);
			}
		}
	}
}

void UMS_IssueTicketContainer::GetIssueTickets(TArray<TWeakObjectPtr<UMS_IssueTicket>>& aOutTickets,
	EMS_IssueType aIssueType, MS_Handle aUnitHandle, int32 aSlotId)
{
	aOutTickets.Empty();

	for (UMS_IssueTicket* IssueTicket : IssueTickets)
	{
		if (IsValid(IssueTicket))
		{
			TWeakObjectPtr<UMS_UnitBase> RequestUnit = IssueTicket->GetRequestUnit();
		
			if (IssueTicket->IsSameIssue(aIssueType, aUnitHandle, aSlotId))
			{
				return;
			}
		
			if (RequestUnit->GetUnitHandle() == aUnitHandle)
			{
				aOutTickets.Emplace(IssueTicket);
			}
		}
	}
}

void UMS_IssueTicketContainer::RegisterIssueTicketStaff(TWeakObjectPtr<UMS_IssueTicket>& aTargetTicket,
	TWeakObjectPtr<UMS_StaffCharacterUnit> aStaffUnit)
{
	MS_ENSURE (aTargetTicket != nullptr);

	TWeakObjectPtr<UMS_StaffCharacterUnit> PreviousStaffUnit = aTargetTicket->GetStaffUnit();
	
	if (PreviousStaffUnit != nullptr)
	{
		PreviousStaffUnit->OnUnregistedAsIssueTicketStaff();
	}

	if (aStaffUnit != nullptr)
	{
		aStaffUnit->OnRegistedAsIssueTicketStaff(aTargetTicket);
	}

	aTargetTicket->SetStaffUnit(aStaffUnit);
}