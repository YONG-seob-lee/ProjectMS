// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_FurnitureUnit.h"

#include "MS_Actor.h"
#include "Controller/MS_PlayerController.h"
#include "Manager_Both/MS_UnitManager.h"
#include "Manager_Client/MS_ItemManager.h"
#include "PlayerState/MS_PlayerState.h"
#include "Prop/Furniture/MS_Furniture.h"
#include "Table/RowBase/MS_ItemData.h"
#include "Table/RowBase/MS_StorageData.h"


void UMS_FurnitureUnit::Initialize(MS_Handle aUnitHandle, EMS_UnitType aUnitType, int32 aTableId)
{
	Super::Initialize(aUnitHandle, aUnitType, aTableId);

	FurnitureData = gTableMng.GetTableRowData<FMS_StorageData>(EMS_TableDataType::Storage, aTableId);
	MS_ENSURE(FurnitureData != nullptr);
	
	int32 SlotCount = FurnitureData->SlotCount;
	for (int32 i = 0; i < SlotCount; ++i)
	{
		SlotDatas.Emplace(FMS_SlotData());
	}
}

void UMS_FurnitureUnit::Finalize()
{
	Super::Finalize();
}

void UMS_FurnitureUnit::PostInitialize()
{
	Super::PostInitialize();
}

void UMS_FurnitureUnit::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
}

int32 UMS_FurnitureUnit::GetBlueprintPathId() const
{
	return FurnitureData->PathFile;
}

EMS_ZoneType UMS_FurnitureUnit::GetZoneType() const
{
	return static_cast<EMS_ZoneType>(FurnitureData->ZoneType);
}

int32 UMS_FurnitureUnit::GetSlotCount() const
{
	return FurnitureData->SlotCount;
}

FIntVector2 UMS_FurnitureUnit::GetGridPosition() const
{
	AMS_Furniture* Furniture = GetActor<AMS_Furniture>();
	MS_ENSURE(IsValid(Furniture));

	return Furniture->GetGridPosition();
}

void UMS_FurnitureUnit::SetSlotDatas(const TArray<FMS_SlotData>& aSlotDatas, bool bChangePlayerData /*= false*/)
{
	if (AMS_PlayerState* PlayerState = GetPlayerState())
	{
		int32 DataCount = aSlotDatas.Num();
		for (int32 i = 0; i < DataCount; ++i)
		{
			if (SlotDatas.IsValidIndex(i))
			{
				SlotDatas[i] = aSlotDatas[i];
				break;
			}
		}

		if (bChangePlayerData)
		{
			PlayerState->SetFurnitureSlotDatas(GetGridPosition(), SlotDatas);
		}
		
		OnChangeRequestSlotDatas();
		OnChangeCurrentSlotDatas();
	}
}

void UMS_FurnitureUnit::AddCurrentItemCount(int32 aSlotId, int32 aCount, bool bChangePlayerData /*= false*/)
{
	if (AMS_PlayerState* PlayerState = GetPlayerState())
	{
		MS_ENSURE(SlotDatas.IsValidIndex(aSlotId));
	
		SlotDatas[aSlotId].CurrentItemCount += aCount;

		if (bChangePlayerData)
		{
			PlayerState->SetFurnitureSlotDatas(GetGridPosition(), SlotDatas);
		}

		OnChangeRequestSlotDatas();
		OnChangeCurrentSlotDatas();
	}
}

void UMS_FurnitureUnit::SubtractCurrentItemCount(int32 aSlotId, int32 aCount, bool bChangePlayerData /*= false*/)
{
	if (AMS_PlayerState* PlayerState = GetPlayerState())
	{
		MS_ENSURE(SlotDatas.IsValidIndex(aSlotId));
	
		SlotDatas[aSlotId].CurrentItemCount -= aCount;

		if (bChangePlayerData)
		{
			PlayerState->SetFurnitureSlotDatas(GetGridPosition(), SlotDatas);
		}
		
		OnChangeRequestSlotDatas();
		OnChangeCurrentSlotDatas();
	}
}

void UMS_FurnitureUnit::SetRequestItem(int32 aSlotId, int32 aItemId, bool bChangePlayerData, bool bSavePlayerData /*= false*/)
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

		if (bChangePlayerData)
		{
			PlayerState->SetFurnitureSlotDatas(GetGridPosition(), SlotDatas);
		}
	}
}

void UMS_FurnitureUnit::TakeItemsImmediately(int32 aSlotId, int32 aItemId,
                                             bool bChangePlayerData /*= true*/, bool bSavePlayerData /*= true*/)
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
			NewItemCount = FMath::Min(gItemMng.GetNoneDisplayItemCount(aItemId), ItemData->Slot100x100MaxCount);
		}
		else
		{
			NewItemCount = FMath::Min(gItemMng.GetPalletItemCount(aItemId), ItemData->BoxMaxCount);
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
					if (UMS_FurnitureUnit* SubtractUnit = Cast<UMS_FurnitureUnit>(Unit.Get()))
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
						
								SubtractUnit->SubtractCurrentItemCount(i, SubtractCount, bChangePlayerData);
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
		AddCurrentItemCount(aSlotId, NewItemCount, bChangePlayerData);

		if (bSavePlayerData)
		{
			PlayerState->SavePlayerData();
		}
	}
}

void UMS_FurnitureUnit::OnChangeRequestSlotDatas()
{
	AMS_Furniture* Furniture = GetActor<AMS_Furniture>();
	MS_ENSURE(IsValid(Furniture));

	Furniture->OnChangeRequestSlotDatas(SlotDatas);
}

void UMS_FurnitureUnit::OnChangeCurrentSlotDatas()
{
	AMS_Furniture* Furniture = GetActor<AMS_Furniture>();
	MS_ENSURE(IsValid(Furniture));

	Furniture->OnChangeCurrentSlotDatas(SlotDatas);
}