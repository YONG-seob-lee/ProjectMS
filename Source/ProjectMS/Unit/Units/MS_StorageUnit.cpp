// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_StorageUnit.h"

#include "MS_Actor.h"
#include "Manager_Both/MS_UnitManager.h"
#include "Manager_Client/MS_ItemManager.h"
#include "Manager_Client/MS_ModeManager.h"
#include "Mode/ModeObject/Container/MS_IssueTicketContainer.h"
#include "Mode/ModeState/MS_ModeState_RunMarket.h"
#include "PlayerState/MS_PlayerState.h"
#include "Prop/Furniture/MS_Furniture.h"
#include "Table/RowBase/MS_ItemData.h"
#include "Table/RowBase/MS_StorageData.h"


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
		int32 DataCount = aSlotDatas.Num();
		for (int32 i = 0; i < DataCount; ++i)
		{
			if (SlotDatas.IsValidIndex(i))
			{
				SlotDatas[i] = aSlotDatas[i];
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
		
		OnChangeRequestSlotDatas();
		OnChangeCurrentSlotDatas(false);
	}
}

bool UMS_StorageUnit::AddCurrentItemCount(int32 aSlotId, int32 aItemId, int32 aCount, bool bSavePlayerData /*= false*/, bool bUpdateNotPlacedItems /*= true*/)
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

		OnChangeRequestSlotDatas();
		OnChangeCurrentSlotDatas(bUpdateNotPlacedItems);
		return true;
	}

	return false;
}

int32 UMS_StorageUnit::AddAnySlotCurrentItemCount(int32 aItemId, int32 aCount, bool bSavePlayerData,
	bool bUpdateNotPlacedItems)
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
		
		if (SlotDatas[i].RequestItemTableId == aItemId && SlotDatas[i].CurrentItemCount > 0)
		{
			int32 AddCount = FMath::Min(RemainAddCount, MaxSlotCount - SlotDatas[i].CurrentItemCount);

			if (AddCurrentItemCount(i, aItemId, AddCount, bSavePlayerData, bUpdateNotPlacedItems))
			{
				RemainAddCount -= AddCount;
			}
		}
	}

	return aCount - RemainAddCount;
}

bool UMS_StorageUnit::SubtractCurrentItemCount(int32 aSlotId, int32 aItemId, int32 aCount, bool bSavePlayerData /*= false*/, bool bUpdateNotPlacedItems /*= true*/)
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
		
		OnChangeRequestSlotDatas();
		OnChangeCurrentSlotDatas(bUpdateNotPlacedItems);
		return true;
	}

	return false;
}

int32 UMS_StorageUnit::SubtractAnySlotCurrentItemCount(int32 aItemId, int32 aCount, bool bSavePlayerData,
	bool bUpdateNotPlacedItems)
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

			if (SubtractCurrentItemCount(i, aItemId, SubtractCount, bSavePlayerData, bUpdateNotPlacedItems))
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
		OnChangeRequestSlotDatas();

		if (bSavePlayerData)
		{
			PlayerState->SetFurnitureSlotDatas(GetGridPosition(), SlotDatas);
			PlayerState->SavePlayerData();
		}
	}
}

void UMS_StorageUnit::TakeItemsImmediately(int32 aSlotId, int32 aItemId,
                                             bool bSavePlayerData /*= true*/)
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
		
		// 기존 아이템 삭제 (빈 개수로 카운트되어 Pallet로 이동)
		// ToDo : Shelf로 정리되도록 변경
		SlotDatas[aSlotId].Empty();

		FMS_ItemData* ItemData = gTableMng.GetTableRowData<FMS_ItemData>(EMS_TableDataType::ItemData, aItemId);
		if (ItemData == nullptr)
		{
			return;
		}

		// 채울 개수 구하기
		int32 NewItemCount = 0;
		if (GetZoneType() == EMS_ZoneType::Display)
		{
			NewItemCount = FMath::Min(gItemMng.GetStorageItemCount(EMS_ZoneType::Shelf, aItemId), ItemData->Slot100x100MaxCount);
		}
		else
		{
			NewItemCount = FMath::Min(gItemMng.GetStorageItemCount(EMS_ZoneType::Pallet, aItemId), ItemData->BoxMaxCount);
		}
		
		// 창고에서 빼기
		if (GetZoneType() == EMS_ZoneType::Display)
		{
			int32 TotalSubtractCount = NewItemCount;
	
			if (const TObjectPtr UnitManager = gUnitMng)
			{
				TArray<TObjectPtr<UMS_UnitBase>> Units;
				UnitManager->GetUnits(EMS_UnitType::Furniture, Units);

				for (TObjectPtr<UMS_UnitBase> Unit : Units)
				{
					if (UMS_StorageUnit* SubtractUnit = Cast<UMS_StorageUnit>(Unit.Get()))
					{
						if (SubtractUnit->GetZoneType() != EMS_ZoneType::Shelf)
						{
							continue;
						}
				
						TArray<FMS_SlotData> SubtractUnitSlotDatas;
						SubtractUnit->GetSlotDatas(SubtractUnitSlotDatas);

						for (int32 i = 0; i < SubtractUnitSlotDatas.Num(); ++i)
						{
							if (SubtractUnitSlotDatas[i].CurrentItemTableId == aItemId)
							{
								int32 SubtractCount = FMath::Min(SubtractUnitSlotDatas[i].CurrentItemCount, TotalSubtractCount);
						
								SubtractUnit->SubtractCurrentItemCount(i, SubtractCount, bSavePlayerData);
								TotalSubtractCount -= SubtractCount;

								if (TotalSubtractCount == 0)
								{
									break;
								}
							}
						}
					}

					if (TotalSubtractCount == 0)
					{
						break;
					}
				}
			}
		}
		
		// 채우기
		SlotDatas[aSlotId].RequestItemTableId = aItemId;
		SlotDatas[aSlotId].CurrentItemTableId = aItemId;
		AddCurrentItemCount(aSlotId, NewItemCount, bSavePlayerData);

		if (bSavePlayerData)
		{
			PlayerState->SavePlayerData();
		}
	}
}

void UMS_StorageUnit::OnChangeRequestSlotDatas()
{
	// 이 가구의 이슈 업데이트
	if (FurnitureData->ZoneType == static_cast<int32>(EMS_ZoneType::Display)
	|| FurnitureData->ZoneType == static_cast<int32>(EMS_ZoneType::Shelf))
	{
		UpdateStorageSlotIssueTickets();
	}
	
	AMS_Furniture* Furniture = GetActor<AMS_Furniture>();
	MS_ENSURE(IsValid(Furniture));

	// MS_Furniture
	Furniture->OnChangeRequestSlotDatas(SlotDatas);
}

void UMS_StorageUnit::OnChangeCurrentSlotDatas(bool bUpdateNotPlacedItems /*= true*/)
{
	// 이 가구의 이슈 업데이트
	if (FurnitureData->ZoneType == static_cast<int32>(EMS_ZoneType::Display)
	|| FurnitureData->ZoneType == static_cast<int32>(EMS_ZoneType::Shelf))
	{
		UpdateStorageSlotIssueTickets();
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

	// Not Placed Item이 옮겨질 수 있는 지 업데이트
	if (bUpdateNotPlacedItems)
	{
		if (FurnitureData->ZoneType == static_cast<int32>(EMS_ZoneType::Pallet))
		{
			gItemMng.UpdateNotPlacedItemsToPalletItems(this);
		}
	}

	// MS_Furniture
	AMS_Furniture* Furniture = GetActor<AMS_Furniture>();
	MS_ENSURE(IsValid(Furniture));

	Furniture->OnChangeCurrentSlotDatas(SlotDatas);
}

void UMS_StorageUnit::UpdateIssueTickets()
{
	Super::UpdateIssueTickets();
	
	UpdateStorageSlotIssueTickets();
}

void UMS_StorageUnit::ClearIssueTickets(bool bNeedToUpdateIssueTicketContainer)
{
	Super::ClearIssueTickets(bNeedToUpdateIssueTicketContainer);
}

void UMS_StorageUnit::UpdateStorageSlotIssueTickets()
{
	UMS_ModeStateBase* ModeState = gModeMng.GetCurrentModeState();
	
	if (UMS_ModeState_RunMarketBase* RunMarketMode = Cast<UMS_ModeState_RunMarketBase>(ModeState))
	{
		if (FurnitureData->ZoneType != static_cast<int32>(EMS_ZoneType::Display)
			&& FurnitureData->ZoneType != static_cast<int32>(EMS_ZoneType::Shelf))
		{
			return;
		}

		for (int32 i = IssueTickets.Num() - 1; i >= 0; --i)
		{
			if (IssueTickets[i] == nullptr)
			{
				IssueTickets.RemoveAt(i);
			}
		}
		
		// 필요한 이슈 정리
		TMap<int32, EMS_StaffIssueType> SlotIdToStaffIssueTypes = {};
		for (int32 i = 0;  i < SlotDatas.Num(); ++i)
		{
			// 요구 아이템과 현재 아이템이 다를 때
			if (SlotDatas[i].RequestItemTableId != SlotDatas[i].CurrentItemTableId)
			{
				// 아이템 빼기
				if (SlotDatas[i].CurrentItemCount > 0)
				{
					if (FurnitureData->ZoneType == static_cast<int32>(EMS_ZoneType::Display))
					{
						SlotIdToStaffIssueTypes.Emplace(i, EMS_StaffIssueType::ReturnItemsFromDisplay);
					}
					else if (FurnitureData->ZoneType == static_cast<int32>(EMS_ZoneType::Shelf))
					{
						SlotIdToStaffIssueTypes.Emplace(i, EMS_StaffIssueType::ReturnItemsFromShelf);
					}
				}
			
				// 아이템 채우기
				else
				{
					if (FurnitureData->ZoneType == static_cast<int32>(EMS_ZoneType::Display))
					{
						SlotIdToStaffIssueTypes.Emplace(i, EMS_StaffIssueType::AddItemsToDisplay);
					}
					else
					{
						SlotIdToStaffIssueTypes.Emplace(i, EMS_StaffIssueType::AddItemsToShelf);
					}
				}
			}
			// 요구 아이템과 현재 아이템이 같을 때
			else
			{
				FMS_ItemData* CurrentItemData = gTableMng.GetTableRowData<FMS_ItemData>(EMS_TableDataType::ItemData, SlotDatas[i].CurrentItemTableId);
				if (CurrentItemData != nullptr)
				{
					if (FurnitureData->ZoneType == static_cast<int32>(EMS_ZoneType::Display))
					{
						int32 RequestAddNum = FMath::Floor(CurrentItemData->Slot100x100MaxCount * AddPercentage);
						if (SlotDatas[i].CurrentItemCount <= RequestAddNum)
						{
							SlotIdToStaffIssueTypes.Emplace(i, EMS_StaffIssueType::AddItemsToDisplay);
						}
					}
					else
					{
						int32 RequestAddNum = FMath::Floor(CurrentItemData->BoxMaxCount * AddPercentage);
						if (SlotDatas[i].CurrentItemCount <= RequestAddNum)
						{
							SlotIdToStaffIssueTypes.Emplace(i, EMS_StaffIssueType::AddItemsToShelf);
						}
					}
				}
			}
		}
	
		// 기존 이슈에 슬롯 번호가 겹치는 것 정리
		for (int32 i = IssueTickets.Num() - 1; i >= 0; --i)
		{
			int32 SlotId = IssueTickets[i]->GetRequestSlotId();
			if (SlotId == INDEX_NONE)
			{
				continue;
			}
			if (!SlotDatas.IsValidIndex(SlotId))
			{
				MS_ENSURE(false);
				continue;
			}

			// 현재 슬롯 이슈와 필요한 슬롯 이슈가 다를 때
			if (SlotIdToStaffIssueTypes.Contains(SlotId))
			{
				EMS_StaffIssueType SlotIssueType = *SlotIdToStaffIssueTypes.Find(SlotId);
				if (SlotIssueType != IssueTickets[i]->GetIssueType())
				{
					UnregisterIssueTicket(IssueTickets[i]);
					RegisterIssueTicket(SlotIssueType, SlotId);

					SlotIdToStaffIssueTypes.Remove(SlotId);
				}
			}
			// 현재 슬롯 이슈가 필요하지 않을 때
			else
			{
				UnregisterIssueTicket(IssueTickets[i]);
			}
		}

		// 기존 이슈에 슬롯 번호가 없는 것 추가
		for (auto& It : SlotIdToStaffIssueTypes)
		{
			RegisterIssueTicket(It.Value, It.Key);
		}
	}
}