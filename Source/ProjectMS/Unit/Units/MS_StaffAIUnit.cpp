// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_StaffAIUnit.h"

#include "MS_FurnitureUnit.h"
#include "UtilityFunctions.h"
#include "Character/MS_CharacterBase.h"
#include "ContentsUtilities/MS_AIDefine.h"
#include "Manager_Both/MS_UnitManager.h"
#include "Manager_Client/MS_ItemManager.h"
#include "Manager_Client/MS_ModeManager.h"
#include "Mode/ModeObject/Container/MS_IssueTicketContainer.h"
#include "Mode/ModeState/MS_ModeStateBase.h"
#include "Mode/ModeState/MS_ModeState_RunMarketBase.h"
#include "Table/RowBase/MS_Staff.h"


void UMS_StaffAIUnit::Initialize(MS_Handle aUnitHandle, EMS_UnitType aUnitType, int32 aTableId)
{
	Super::Initialize(aUnitHandle, aUnitType, aTableId);

	StaffTableData = gTableMng.GetTableRowData<FMS_Staff>(EMS_TableDataType::Staff, aTableId);
	MS_ENSURE(StaffTableData != nullptr);

	int32 SlotCount = StaffTableData->SlotCount;
	for (int32 i = 0; i < SlotCount; ++i)
	{
		SlotDatas.Emplace(FMS_SlotData());
	}
}

void UMS_StaffAIUnit::Finalize()
{
	Super::Finalize();
}

void UMS_StaffAIUnit::PostInitialize()
{
	Super::PostInitialize();
}

void UMS_StaffAIUnit::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
}

int32 UMS_StaffAIUnit::GetBlueprintPathId() const
{
	return StaffTableData->PathFile;
}

UClass* UMS_StaffAIUnit::GetBlueprintClass() const
{
	int32 BPPathId = GetBlueprintPathId();
	if (BPPathId == INDEX_NONE)
	{
		return nullptr;
	}

	return UUtilityFunctions::GetClassByTablePathId(BPPathId);
}

void UMS_StaffAIUnit::SetPlayerStaffData(const FMS_PlayerStaffData& aPlayerStaffData)
{
	PlayerStaffData = aPlayerStaffData;
}

EMS_StaffActionType UMS_StaffAIUnit::GetFirstStaffAction(TWeakObjectPtr<UMS_IssueTicket>& OutIssueTicket)
{
	if (NoneIssueStaffActions.IsValidIndex(0))
	{
		MS_ENSURE (NoneIssueStaffActions[0] != EMS_StaffActionType::None);

		OutIssueTicket = nullptr;
		return NoneIssueStaffActions[0];
	}

	if (IssueTicket != nullptr)
	{
		OutIssueTicket = IssueTicket;
		return EMS_StaffActionType::Issue;
	}

	else
	{
		SearchAndRegisterIssueTicket();
		if (IssueTicket != nullptr)
		{
			OutIssueTicket = IssueTicket;
			return EMS_StaffActionType::Issue;
		}

		OutIssueTicket = nullptr;
		return EMS_StaffActionType::None;
	}
}

void UMS_StaffAIUnit::RegisterNoneIssueStaffAction(EMS_StaffActionType aStaffActionType)
{
	NoneIssueStaffActions.Emplace(aStaffActionType);
}

void UMS_StaffAIUnit::UnregisterNoneIssueStaffAction(EMS_StaffActionType aStaffActionType)
{
	int32 RemoveNum = NoneIssueStaffActions.RemoveSingle(aStaffActionType);
}

void UMS_StaffAIUnit::SearchAndRegisterIssueTicket()
{
	TWeakObjectPtr<class UMS_IssueTicket> Ticket = SearchIssueTicket();
	if (Ticket != nullptr)
	{
		RegisterAsIssueTicketStaff(Ticket);
	}
}

TWeakObjectPtr<class UMS_IssueTicket> UMS_StaffAIUnit::SearchIssueTicket()
{
	UMS_ModeStateBase* ModeState = gModeMng.GetCurrentModeState();
	if (UMS_ModeState_RunMarketBase* RunMarketMode = Cast<UMS_ModeState_RunMarketBase>(ModeState))
	{
		return RunMarketMode->SearchStaffIssueTicket(this);
	}

	return nullptr;
}

void UMS_StaffAIUnit::RegisterAsIssueTicketStaff(TWeakObjectPtr<UMS_IssueTicket>& aTargetTicket)
{
	UMS_ModeStateBase* ModeState = gModeMng.GetCurrentModeState();
	if (UMS_ModeState_RunMarketBase* RunMarketMode = Cast<UMS_ModeState_RunMarketBase>(ModeState))
	{
		RunMarketMode->RegisterIssueTicketStaff(aTargetTicket, this);
	}
}

void UMS_StaffAIUnit::UnregisterAsIssueTicketStaff()
{
	UMS_ModeStateBase* ModeState = gModeMng.GetCurrentModeState();
	if (UMS_ModeState_RunMarketBase* RunMarketMode = Cast<UMS_ModeState_RunMarketBase>(ModeState))
	{
		RunMarketMode->UnregisterIssueTicketStaff(IssueTicket);
	}
}

void UMS_StaffAIUnit::OnRegisteredAsIssueTicketStaff(TWeakObjectPtr<UMS_IssueTicket> aIssueTicket)
{
	IssueTicket = aIssueTicket;
}

void UMS_StaffAIUnit::OnUnregisteredAsIssueTicketStaff()
{
	IssueTicket = nullptr;
}

TWeakObjectPtr<class UMS_FurnitureUnit> UMS_StaffAIUnit::GetIssueTicketRequestFurnitrueUnit() const
{
	if (IssueTicket != nullptr)
	{
		return IssueTicket->GetRequestFurnitureUnit();
	}

	return nullptr;
}

bool UMS_StaffAIUnit::GetIssueTicketTakeOutTargetUnits(
	TArray<TWeakObjectPtr<UMS_FurnitureUnit>>& aOutTargetUnits) const
{
	aOutTargetUnits.Empty();

	FMS_SlotData SlotData = IssueTicket->GetRequestFurnitureSlot();
	EMS_StaffIssueType IssueType = IssueTicket->GetIssueType();

	if (IssueType != EMS_StaffIssueType::AddItemsToDisplay
	&& IssueType != EMS_StaffIssueType::AddItemsToShelf)
	{
		return false;
	}
	
	if (IssueType == EMS_StaffIssueType::AddItemsToDisplay)
	{
		TArray<TWeakObjectPtr<class UMS_FurnitureUnit>> TakeOutTargetFurnitrues;
		if (gItemMng.CanTakeOutFromStorage(SlotData.RequestItemTableId, EMS_ZoneType::Shelf, TakeOutTargetFurnitrues))
		{
			aOutTargetUnits = TakeOutTargetFurnitrues;
			return true;
		}
	}

	else if (IssueType == EMS_StaffIssueType::AddItemsToShelf)
	{
		TArray<TWeakObjectPtr<class UMS_FurnitureUnit>> TakeOutTargetFurnitrues;
		if (gItemMng.CanTakeOutFromStorage(SlotData.RequestItemTableId, EMS_ZoneType::Pallet, TakeOutTargetFurnitrues))
		{
			aOutTargetUnits = TakeOutTargetFurnitrues;
			return true;
		}
	}

	return false;
}

bool UMS_StaffAIUnit::GetIssueTicketTakeInTargetUnits(TArray<TWeakObjectPtr<UMS_FurnitureUnit>>& aOutTargetUnits) const
{
	aOutTargetUnits.Empty();

	FMS_SlotData SlotData = IssueTicket->GetRequestFurnitureSlot();
	EMS_StaffIssueType IssueType = IssueTicket->GetIssueType();

	if (IssueType != EMS_StaffIssueType::ReturnItemsFromDisplay
	&& IssueType != EMS_StaffIssueType::ReturnItemsFromShelf)
	{
		return false;
	}
	
	if (IssueType == EMS_StaffIssueType::ReturnItemsFromDisplay)
	{
		TArray<TWeakObjectPtr<class UMS_FurnitureUnit>> TakeInTargetFurnitrues;
		if (gItemMng.CanTakeInToStorage(SlotData.CurrentItemTableId, SlotData.CurrentItemCount, EMS_ZoneType::Shelf, TakeInTargetFurnitrues))
		{
			aOutTargetUnits = TakeInTargetFurnitrues;
			return true;
		}
	}

	else if (IssueType == EMS_StaffIssueType::ReturnItemsFromShelf)
	{
		TArray<TWeakObjectPtr<class UMS_FurnitureUnit>> TakeInTargetFurnitrues;
		if (gItemMng.CanTakeInToStorage(SlotData.CurrentItemTableId, SlotData.CurrentItemCount, EMS_ZoneType::Pallet, TakeInTargetFurnitrues))
		{
			aOutTargetUnits = TakeInTargetFurnitrues;
			return true;
		}
	}

	return false;
}
