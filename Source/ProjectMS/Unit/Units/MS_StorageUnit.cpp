// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_StorageUnit.h"

#include "MS_Actor.h"
#include "Manager_Both/MS_UnitManager.h"
#include "Manager_Client/MS_ItemManager.h"
#include "Manager_Client/MS_ModeManager.h"
#include "Mode/ModeObject/Container/MS_IssueTicketContainer.h"
#include "Mode/ModeState/MS_ModeState_RunMarket.h"
#include "PlayerState/MS_PlayerState.h"
#include "Prop/Furniture/Storage/MS_Storage.h"
#include "Table/RowBase/MS_ItemData.h"
#include "Table/RowBase/MS_FurnitureData.h"


void UMS_StorageUnit::Initialize(MS_Handle aUnitHandle, EMS_UnitType aUnitType, int32 aTableId)
{
	Super::Initialize(aUnitHandle, aUnitType, aTableId);
	
	int32 SlotCount = FurnitureData->SlotCount;
	for (int32 i = 0; i < SlotCount; ++i)
	{
		SlotDatas.Emplace(FMS_SlotData());
	}

	if (FurnitureData->ZoneType == static_cast<int32>(EMS_ZoneType::Display))
	{
		AddPercentage = 0.5f;
	}
	else if (FurnitureData->ZoneType == static_cast<int32>(EMS_ZoneType::Shelf))
	{
		AddPercentage = 0.99f;
	}
}

void UMS_StorageUnit::Finalize()
{
	Super::Finalize();
}

void UMS_StorageUnit::PostInitialize()
{
	Super::PostInitialize();
}

void UMS_StorageUnit::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
}

FMS_SlotData UMS_StorageUnit::GetSlotData(int32 aSlotId) const
{
	if (SlotDatas.IsValidIndex(aSlotId))
	{
		return SlotDatas[aSlotId];
	}

	return FMS_SlotData();
}

void UMS_StorageUnit::SetSlotDatas(const TArray<FMS_SlotData>& aSlotDatas, bool bSavePlayerData /*= false*/)
{
	if (AMS_PlayerState* PlayerState = GetPlayerState())
	{
		TArray<int32> SlotIds = {};
		int32 DataCount = aSlotDatas.Num();
		for (int32 i = 0; i < DataCount; ++i)
		{
			if (SlotDatas.IsValidIndex(i))
			{
				SlotDatas[i] = aSlotDatas[i];
				SlotIds.Emplace(i);
			}
			else
			{
				break;
			}
		}

		if (bSavePlayerData)
		{
			PlayerState->SetFurnitureSlotDatas(GetGridPosition(), SlotDatas);
			PlayerState->SavePlayerData();
		}
		
		OnChangeRequestSlotDatas(SlotIds);
		OnChangeCurrentSlotDatas(SlotIds);
	}
}

bool UMS_StorageUnit::AddCurrentItemCount(int32 aSlotId, int32 aItemId, int32 aCount, bool bSavePlayerData /*= false*/)
{
	if (AMS_PlayerState* PlayerState = GetPlayerState())
	{
		if (!SlotDatas.IsValidIndex(aSlotId))
		{
			MS_ENSURE(false);
			return false;
		}
		
		if (SlotDatas[aSlotId].CurrentItemTableId != aItemId)
		{
			if (SlotDatas[aSlotId].CurrentItemCount == 0)
			{
				SlotDatas[aSlotId].CurrentItemTableId = aItemId;
			}
			else
			{
				MS_ENSURE(false);
				return false;
			}
		}
	
		SlotDatas[aSlotId].CurrentItemCount += aCount;

		if (bSavePlayerData)
		{
			PlayerState->SetFurnitureSlotDatas(GetGridPosition(), SlotDatas);
			PlayerState->SavePlayerData();
		}
		
		OnChangeCurrentSlotDatas(TArray<int32>({aSlotId}));
		return true;
	}

	return false;
}

int32 UMS_StorageUnit::AddAnySlotCurrentItemCount(int32 aItemId, int32 aCount, bool bSavePlayerData)
{
	int32 RemainAddCount = aCount;

	FMS_ItemData* ItemData = gTableMng.GetTableRowData<FMS_ItemData>(EMS_TableDataType::ItemData, aItemId);
	if (ItemData == nullptr)
	{
		MS_ENSURE(false);
		return false;
	}

	int32 MaxSlotCount = GetZoneType() == EMS_ZoneType::Display ? ItemData->Slot100x100MaxCount : ItemData->BoxMaxCount;
	
	for (int32 i = 0; i < SlotDatas.Num(); ++i)
	{
		if (RemainAddCount <= 0)
		{
			break;
		}

		if (SlotDatas[i].CurrentItemTableId != aItemId && SlotDatas[i].CurrentItemCount == 0 &&
			SlotDatas[i].RequestItemTableId == aItemId)
		{
			SlotDatas[i].CurrentItemTableId = aItemId;
		}

		// ReqiestItemId가 일치하지 않더라도 이미 가지고 있는 아이템과 같은 종류면 집어 넣기
		// 유저 인터렉션으로 Staff가 일을 처리하는 중간에 값이 바꼈을 때 더 자연스럽게 연출하기 위함
		if (SlotDatas[i].CurrentItemTableId == aItemId)
		{
			int32 AddCount = FMath::Min(RemainAddCount, MaxSlotCount - SlotDatas[i].CurrentItemCount);

			if (AddCurrentItemCount(i, aItemId, AddCount, bSavePlayerData))
			{
				RemainAddCount -= AddCount;
			}
		}
	}

	return aCount - RemainAddCount;
}

bool UMS_StorageUnit::SubtractCurrentItemCount(int32 aSlotId, int32 aItemId, int32 aCount, bool bSavePlayerData /*= false*/)
{
	if (AMS_PlayerState* PlayerState = GetPlayerState())
	{
		if (!SlotDatas.IsValidIndex(aSlotId))
		{
			MS_ENSURE(false);
			return false;
		}

		if (SlotDatas[aSlotId].CurrentItemTableId != aItemId)
		{
			MS_ENSURE(false);
			return false;
		}

		if (SlotDatas[aSlotId].CurrentItemCount < aCount)
		{
			MS_ENSURE(false);
			return false;
		}
		
		SlotDatas[aSlotId].CurrentItemCount -= aCount;

		if (SlotDatas[aSlotId].CurrentItemCount == 0)
		{
			SlotDatas[aSlotId].CurrentItemTableId = INDEX_NONE;
		}

		if (bSavePlayerData)
		{
			PlayerState->SetFurnitureSlotDatas(GetGridPosition(), SlotDatas);
			PlayerState->SavePlayerData();
		}
		
		OnChangeCurrentSlotDatas(TArray<int32>({aSlotId}));
		return true;
	}

	return false;
}

int32 UMS_StorageUnit::SubtractAnySlotCurrentItemCount(int32 aItemId, int32 aCount, bool bSavePlayerData)
{
	int32 RemainSubtractCount = aCount;
	
	for (int32 i = 0; i < SlotDatas.Num(); ++i)
	{
		if (RemainSubtractCount <= 0)
		{
			break;
		}
		
		if (SlotDatas[i].CurrentItemTableId == aItemId && SlotDatas[i].CurrentItemCount > 0)
		{
			int32 SubtractCount = FMath::Min(RemainSubtractCount, SlotDatas[i].CurrentItemCount);

			if (SubtractCurrentItemCount(i, aItemId, SubtractCount, bSavePlayerData))
			{
				RemainSubtractCount -= SubtractCount;
			}
		}
	}

	return aCount - RemainSubtractCount;
}

void UMS_StorageUnit::SetRequestItem(int32 aSlotId, int32 aItemId, bool bSavePlayerData)
{
	if (AMS_PlayerState* PlayerState = GetPlayerState())
	{
		if (!SlotDatas.IsValidIndex(aSlotId))
		{
			MS_ENSURE(false);
			return;
		}

		if (GetZoneType() != EMS_ZoneType::Display && GetZoneType() != EMS_ZoneType::Shelf)
		{
			return;
		}
		
		SlotDatas[aSlotId].RequestItemTableId = aItemId;
		OnChangeRequestSlotDatas(TArray<int32>({aSlotId}));

		if (bSavePlayerData)
		{
			PlayerState->SetFurnitureSlotDatas(GetGridPosition(), SlotDatas);
			PlayerState->SavePlayerData();
		}
	}
}

void UMS_StorageUnit::OnChangeRequestSlotDatas(const TArray<int32>& aChangeSlotIds)
{
	// 이 가구의 이슈 업데이트
	if (FurnitureData->ZoneType == static_cast<int32>(EMS_ZoneType::Display)
	|| FurnitureData->ZoneType == static_cast<int32>(EMS_ZoneType::Shelf))
	{
		for (int32 ChangeSlotId : aChangeSlotIds)
		{
			UpdateStorageSlotIssueTicket(ChangeSlotId);
		}
	}

	// 이 가구의 아이템슬롯이 변경 되어 다른 가구의 이슈들이 해결 가능, 불가능해졌는지 업데이트
	UMS_ModeStateBase* ModeState = gModeMng.GetCurrentModeState();
	if (UMS_ModeState_RunMarketBase* RunMarketMode = Cast<UMS_ModeState_RunMarketBase>(ModeState))
	{
		if (FurnitureData->ZoneType == static_cast<int32>(EMS_ZoneType::Pallet))
		{
			RunMarketMode->UpdateAllZoneStorageIssueTicketsEnabled(EMS_ZoneType::Shelf);
		}
		else if (FurnitureData->ZoneType == static_cast<int32>(EMS_ZoneType::Shelf))
		{
			RunMarketMode->UpdateAllZoneStorageIssueTicketsEnabled(EMS_ZoneType::Display);
		}
	}
	
	AMS_Storage* Storage = GetActor<AMS_Storage>();
	MS_ENSURE(IsValid(Storage));
	
	Storage->OnChangeRequestSlotDatas(SlotDatas, aChangeSlotIds);
}

void UMS_StorageUnit::OnChangeCurrentSlotDatas(const TArray<int32>& aChangeSlotIds)
{
	// 이 가구의 이슈 업데이트
	if (FurnitureData->ZoneType == static_cast<int32>(EMS_ZoneType::Display)
	|| FurnitureData->ZoneType == static_cast<int32>(EMS_ZoneType::Shelf))
	{
		for (int32 ChangeSlotId : aChangeSlotIds)
		{
			UpdateStorageSlotIssueTicket(ChangeSlotId);
		}
	}

	// 이 가구의 아이템슬롯이 변경 되어 다른 가구의 이슈들이 해결 가능, 불가능해졌는지 업데이트
	UMS_ModeStateBase* ModeState = gModeMng.GetCurrentModeState();
	if (UMS_ModeState_RunMarketBase* RunMarketMode = Cast<UMS_ModeState_RunMarketBase>(ModeState))
	{
		if (FurnitureData->ZoneType == static_cast<int32>(EMS_ZoneType::Pallet))
		{
			RunMarketMode->UpdateAllZoneStorageIssueTicketsEnabled(EMS_ZoneType::Shelf);
		}
		else if (FurnitureData->ZoneType == static_cast<int32>(EMS_ZoneType::Shelf))
		{
			RunMarketMode->UpdateAllZoneStorageIssueTicketsEnabled(EMS_ZoneType::Display);
		}
	}
	
	AMS_Storage* Storage = GetActor<AMS_Storage>();
	MS_ENSURE(IsValid(Storage));

	Storage->OnChangeCurrentSlotDatas(SlotDatas, aChangeSlotIds);
}

void UMS_StorageUnit::UpdateIssueTicket()
{
	Super::UpdateIssueTicket();

	for (int32 i = 0; i < SlotDatas.Num(); ++i)
	{
		UpdateStorageSlotIssueTicket(i);
	}
}

void UMS_StorageUnit::ClearIssueTickets(bool bNeedToUpdateIssueTicketContainer)
{
	Super::ClearIssueTickets(bNeedToUpdateIssueTicketContainer);
}

void UMS_StorageUnit::UpdateStorageSlotIssueTicket(int32 aSlotId)
{
	if (FurnitureData->ZoneType != static_cast<int32>(EMS_ZoneType::Display)
		&& FurnitureData->ZoneType != static_cast<int32>(EMS_ZoneType::Shelf))
	{
		return;
	}
	
	// ===== 필요한 이슈 ===== //
	EMS_StaffIssueType StaffIssueType = EMS_StaffIssueType::None;
	
	// 요구 아이템과 현재 아이템이 다를 때
	if (SlotDatas[aSlotId].RequestItemTableId != SlotDatas[aSlotId].CurrentItemTableId)
	{
		// 아이템 빼기
		if (SlotDatas[aSlotId].CurrentItemCount > 0)
		{
			if (FurnitureData->ZoneType == static_cast<int32>(EMS_ZoneType::Display))
			{
				StaffIssueType = EMS_StaffIssueType::ReturnItemsFromDisplay;
			}
			else if (FurnitureData->ZoneType == static_cast<int32>(EMS_ZoneType::Shelf))
			{
				StaffIssueType = EMS_StaffIssueType::ReturnItemsFromShelf;
			}
		}
	
		// 아이템 채우기
		else
		{
			if (FurnitureData->ZoneType == static_cast<int32>(EMS_ZoneType::Display))
			{
				StaffIssueType = EMS_StaffIssueType::AddItemsToDisplay;
			}
			else
			{
				StaffIssueType = EMS_StaffIssueType::AddItemsToShelf;
			}
		}
	}
	
	// 요구 아이템과 현재 아이템이 같을 때
	else
	{
		FMS_ItemData* CurrentItemData = gTableMng.GetTableRowData<FMS_ItemData>(EMS_TableDataType::ItemData, SlotDatas[aSlotId].CurrentItemTableId);
		if (CurrentItemData != nullptr)
		{
			if (FurnitureData->ZoneType == static_cast<int32>(EMS_ZoneType::Display))
			{
				int32 RequestAddNum = FMath::Floor(CurrentItemData->Slot100x100MaxCount * AddPercentage);
				if (SlotDatas[aSlotId].CurrentItemCount <= RequestAddNum)
				{
					StaffIssueType = EMS_StaffIssueType::AddItemsToDisplay;
				}
			}
			else
			{
				int32 RequestAddNum = FMath::Floor(CurrentItemData->BoxMaxCount * AddPercentage);
				if (SlotDatas[aSlotId].CurrentItemCount <= RequestAddNum)
				{
					StaffIssueType = EMS_StaffIssueType::AddItemsToShelf;
				}
			}
		}
	}

	// ===== 기존 이슈 ===== //
	TWeakObjectPtr<UMS_IssueTicket> TargetSlotTicket = nullptr;
	
	for (auto& IssueTicket : IssueTickets)
	{
		if (IssueTicket->GetRequestUnit() != this)
		{
			MS_ENSURE(false);
			continue;
		}

		if (IssueTicket->GetRequestSlotId() == aSlotId)
		{
			TargetSlotTicket = IssueTicket;
			break;
		}
	}

	// ===== 정리 ===== //
	if (TargetSlotTicket == nullptr && StaffIssueType != EMS_StaffIssueType::None)
	{
		RegisterIssueTicket(StaffIssueType, aSlotId);
	}
	
	if (TargetSlotTicket != nullptr && StaffIssueType == EMS_StaffIssueType::None)
	{
		UnregisterIssueTicket(TargetSlotTicket);
	}
	
	else if (TargetSlotTicket != nullptr && TargetSlotTicket->GetIssueType() != StaffIssueType)
	{
		UnregisterIssueTicket(TargetSlotTicket);
		RegisterIssueTicket(StaffIssueType, aSlotId);
	}

	else if (TargetSlotTicket != nullptr && TargetSlotTicket->GetIssueType() == StaffIssueType)
	{
		TargetSlotTicket->UpdateEnabled();
	}
}
