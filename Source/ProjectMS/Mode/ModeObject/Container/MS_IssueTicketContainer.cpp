// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_IssueTicketContainer.h"

#include "Manager_Client/MS_ItemManager.h"
#include "Units/MS_FurnitureUnit.h"
#include "Units/MS_StaffAIUnit.h"


UMS_IssueTicket::UMS_IssueTicket()
	: IssueType(EMS_StaffIssueType::None), RequestFurnitureUnit(nullptr), RequestSlot(INDEX_NONE)
{
}

void UMS_IssueTicket::Initialize(EMS_StaffIssueType aIssueType,
	TWeakObjectPtr<::UMS_FurnitureUnit> aRequestFurnitureUnit, int32 aRequestSlot)
{
	IssueType = aIssueType;
	RequestFurnitureUnit = aRequestFurnitureUnit;
	RequestSlot = aRequestSlot;

	UpdateEnabled();
}

void UMS_IssueTicket::Finalize()
{
	if (StaffUnit != nullptr)
	{
		StaffUnit->OnUnregisteredAsIssueTicketStaff();
	}
}

void UMS_IssueTicket::SetStaffUnit(TWeakObjectPtr<UMS_StaffAIUnit> aStaffUnit)
{
	StaffUnit = aStaffUnit;
}

FMS_SlotData UMS_IssueTicket::GetRequestFurnitureSlot() const
{
	return RequestFurnitureUnit->GetSlotData(RequestSlot);
}

bool UMS_IssueTicket::IsSameIssue(EMS_StaffIssueType aIssueType, MS_Handle aUnitHandle, int32 aRequestSlot) const
{
	return IssueType == aIssueType
	&& RequestFurnitureUnit->GetUnitHandle() == aUnitHandle
	&& RequestSlot == aRequestSlot;
}

bool UMS_IssueTicket::IsSameIssue(EMS_StaffIssueType aIssueType, TWeakObjectPtr<UMS_FurnitureUnit> aRequestUnit,
                                  int32 aRequestSlot) const
{
	return IssueType == aIssueType
		&& RequestFurnitureUnit == aRequestUnit
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
		&& RequestFurnitureUnit == aOther->RequestFurnitureUnit
		&& RequestSlot == aOther->RequestSlot;
}

bool UMS_IssueTicket::AllowSameIssue(EMS_StaffIssueType aIssueType)
{
	// ToDo : 타입이 추가된 후 중복 발행이 가능한 이슈는 true
	return false;
}

void UMS_IssueTicket::UpdateEnabled()
{
	if (IssueType == EMS_StaffIssueType::ReturnItemsFromDisplay)
	{
		FMS_SlotData SlotData = GetRequestFurnitureSlot();
			
		SetIsEnabled(gItemMng.CanReturnToStorage(SlotData.CurrentItemTableId, SlotData.CurrentItemCount, EMS_ZoneType::Shelf));
	}
	
	else if (IssueType == EMS_StaffIssueType::AddItemsToDisplay)
	{
		FMS_SlotData SlotData = GetRequestFurnitureSlot();
		
		int32 ShelfItemCount = gItemMng.GetStorageItemCount(EMS_ZoneType::Shelf, SlotData.RequestItemTableId);
		SetIsEnabled(ShelfItemCount > 0);
	}
	
	else if (IssueType == EMS_StaffIssueType::ReturnItemsFromShelf)
	{
		FMS_SlotData SlotData = GetRequestFurnitureSlot();
			
		SetIsEnabled(gItemMng.CanReturnToStorage(SlotData.CurrentItemTableId, SlotData.CurrentItemCount, EMS_ZoneType::Pallet));
	}
	
	else if (IssueType == EMS_StaffIssueType::AddItemsToShelf)
	{
		FMS_SlotData SlotData = GetRequestFurnitureSlot();
		
		int32 ShelfItemCount = gItemMng.GetStorageItemCount(EMS_ZoneType::Pallet, SlotData.RequestItemTableId);
		SetIsEnabled(ShelfItemCount > 0);
	}
	else
	{
		SetIsEnabled(true);
	}
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

TWeakObjectPtr<UMS_IssueTicket> UMS_IssueTicketContainer::RegisterIssueTicket(EMS_StaffIssueType aIssueType,
	TWeakObjectPtr<UMS_FurnitureUnit> aRequestUnit /*= nullptr*/, int32 aSlotId /*= INDEX_NONE*/)
{
	if (!UMS_IssueTicket::AllowSameIssue(aIssueType))
	{
		for (UMS_IssueTicket* TestTicket : IssueTickets)
		{
			if (IsValid(TestTicket))
			{
				if (TestTicket->IsSameIssue(aIssueType, aRequestUnit, aSlotId))
				{
					return nullptr;
				}
			}
		}
	}
	
	UMS_IssueTicket* IssueTicket = NewObject<UMS_IssueTicket>(this);
	if (IssueTicket)
	{
		IssueTicket->Initialize(aIssueType, aRequestUnit, aSlotId);
		IssueTickets.Emplace(IssueTicket);
		return IssueTicket;
	}

	return nullptr;
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
			TWeakObjectPtr<UMS_FurnitureUnit> RequestUnit = IssueTickets[i]->GetRequestFurnitureUnit();
		
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

void UMS_IssueTicketContainer::UnregisterUnitIssueTickets(TWeakObjectPtr<UMS_FurnitureUnit> aUnitBase)
{
	for (int32 i = IssueTickets.Num() - 1; i >= 0; --i)
	{
		if (IsValid(IssueTickets[i]))
		{
			TWeakObjectPtr<UMS_FurnitureUnit> RequestUnit = IssueTickets[i]->GetRequestFurnitureUnit();
		
			if (RequestUnit == nullptr)
			{
				continue;
			}
		
			if (RequestUnit == aUnitBase)
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
			TWeakObjectPtr<UMS_FurnitureUnit> RequestUnit = IssueTickets[i]->GetRequestFurnitureUnit();
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

void UMS_IssueTicketContainer::UnregisterUnitSlotIssueTickets(TWeakObjectPtr<UMS_FurnitureUnit> aFurnitureUnit, int32 aSlotId)
{
	for (int32 i = IssueTickets.Num() - 1; i >= 0; --i)
	{
		if (IsValid(IssueTickets[i]))
		{
			TWeakObjectPtr<UMS_FurnitureUnit> RequestUnit = IssueTickets[i]->GetRequestFurnitureUnit();
			int32 RequestSlot = IssueTickets[i]->GetRequestSlot();
			
			if (RequestUnit == nullptr)
			{
				continue;
			}
		
			if (RequestUnit == aFurnitureUnit && RequestSlot == aSlotId)
			{
				IssueTickets[i]->Finalize();
				MS_DeleteObject(IssueTickets[i]);
				IssueTickets.RemoveAt(i);
			}
		}
	}
}

bool UMS_IssueTicketContainer::UnregisterIssueTicket(TWeakObjectPtr<UMS_IssueTicket> aIssueTicket)
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
			
				return true;
			}
		}
	}

	return false;
}

void UMS_IssueTicketContainer::GetTypeIssueTickets(TArray<TWeakObjectPtr<UMS_IssueTicket>>& aOutTickets,
	EMS_StaffIssueType aIssueType)
{
	aOutTickets.Empty();

	for (UMS_IssueTicket* IssueTicket : IssueTickets)
	{
		if (IsValid(IssueTicket))
		{
			EMS_StaffIssueType IssueType = IssueTicket->GetIssueType();
		
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
			TWeakObjectPtr<UMS_FurnitureUnit> RequestUnit = IssueTicket->GetRequestFurnitureUnit();
		
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
			TWeakObjectPtr<UMS_FurnitureUnit> RequestUnit = IssueTicket->GetRequestFurnitureUnit();
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
	EMS_StaffIssueType aIssueType, MS_Handle aUnitHandle, int32 aSlotId)
{
	aOutTickets.Empty();

	for (UMS_IssueTicket* IssueTicket : IssueTickets)
	{
		if (IsValid(IssueTicket))
		{
			TWeakObjectPtr<UMS_FurnitureUnit> RequestUnit = IssueTicket->GetRequestFurnitureUnit();
		
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
	TWeakObjectPtr<UMS_StaffAIUnit> aStaffUnit)
{
	MS_ENSURE (aTargetTicket != nullptr);

	TWeakObjectPtr<UMS_StaffAIUnit> PreviousStaffUnit = aTargetTicket->GetStaffUnit();
	
	if (PreviousStaffUnit != nullptr)
	{
		PreviousStaffUnit->OnUnregisteredAsIssueTicketStaff();
	}

	if (aStaffUnit != nullptr)
	{
		aStaffUnit->OnRegisteredAsIssueTicketStaff(aTargetTicket);
	}

	aTargetTicket->SetStaffUnit(aStaffUnit);
}

void UMS_IssueTicketContainer::UpdateStorageIssueTicketsEnabled(EMS_ZoneType aZoneType)
{
	if (aZoneType == EMS_ZoneType::Display)
	{
		// Return Items Tickets
		TArray<TWeakObjectPtr<UMS_IssueTicket>> ReturnItemsTickets;
		GetTypeIssueTickets(ReturnItemsTickets, EMS_StaffIssueType::ReturnItemsFromDisplay);

		for (TWeakObjectPtr<UMS_IssueTicket> Ticket : ReturnItemsTickets)
		{
			FMS_SlotData SlotData = Ticket->GetRequestFurnitureSlot();
			
			Ticket->SetIsEnabled(gItemMng.CanReturnToStorage(SlotData.CurrentItemTableId, SlotData.CurrentItemCount, EMS_ZoneType::Shelf));
		}
		
		// Add Items Tickets
		TArray<TWeakObjectPtr<UMS_IssueTicket>> AddItemsTickets;
		GetTypeIssueTickets(ReturnItemsTickets, EMS_StaffIssueType::AddItemsToDisplay);

		if (!AddItemsTickets.IsEmpty())
		{
			TMap<int32, int32> ShelfItems;
			gItemMng.GetStorageItems(EMS_ZoneType::Shelf, ShelfItems);

			for (TWeakObjectPtr<UMS_IssueTicket> Ticket : AddItemsTickets)
			{
				FMS_SlotData SlotData = Ticket->GetRequestFurnitureSlot();
				
				Ticket->SetIsEnabled(ShelfItems.Contains(SlotData.RequestItemTableId));
			}
		}
	}
	else if (aZoneType == EMS_ZoneType::Shelf)
	{
		// Return Items Tickets
		TArray<TWeakObjectPtr<UMS_IssueTicket>> ReturnItemsTickets;
		GetTypeIssueTickets(ReturnItemsTickets, EMS_StaffIssueType::ReturnItemsFromShelf);

		for (TWeakObjectPtr<UMS_IssueTicket> Ticket : ReturnItemsTickets)
		{
			FMS_SlotData SlotData = Ticket->GetRequestFurnitureSlot();
			
			Ticket->SetIsEnabled(gItemMng.CanReturnToStorage(SlotData.CurrentItemTableId, SlotData.CurrentItemCount, EMS_ZoneType::Pallet));
		}
		
		// Add Items Tickets
		TArray<TWeakObjectPtr<UMS_IssueTicket>> AddItemsTickets;
		GetTypeIssueTickets(ReturnItemsTickets, EMS_StaffIssueType::AddItemsToShelf);

		if (!AddItemsTickets.IsEmpty())
		{
			TMap<int32, int32> PalletItems;
			gItemMng.GetStorageItems(EMS_ZoneType::Pallet, PalletItems);

			for (TWeakObjectPtr<UMS_IssueTicket> Ticket : AddItemsTickets)
			{
				FMS_SlotData SlotData = Ticket->GetRequestFurnitureSlot();
				
				Ticket->SetIsEnabled(PalletItems.Contains(SlotData.RequestItemTableId));
			}
		}
	}
}
