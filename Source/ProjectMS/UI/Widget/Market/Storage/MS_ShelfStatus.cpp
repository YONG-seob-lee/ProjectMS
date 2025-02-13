// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ShelfStatus.h"

#include "Manager_Client/MS_ItemManager.h"
#include "Widget/ListViewElement/ElementData/MS_StorageSlotElementData.h"
#include "MS_Define.h"
#include "MS_UnitBase.h"
#include "Units/MS_FurnitureUnit.h"
#include "Widget/WidgetComponent/MS_TileView.h"

void UMS_ShelfStatus::NativeConstruct()
{
	Super::NativeConstruct();
	CPP_TileView->SetScrollbarVisibility(ESlateVisibility::Collapsed);
}

void UMS_ShelfStatus::NativeDestruct()
{
	Super::NativeDestruct();
}

void UMS_ShelfStatus::SetOwnerUnit(TWeakObjectPtr<UMS_UnitBase> aOwnerUnit)
{
	OwnerUnit = aOwnerUnit;
}

void UMS_ShelfStatus::SetTileView()
{
	TMap<int32, int32> TakableItems;
	
	if (OwnerUnit == nullptr)
	{
		MS_ENSURE(false);
		return;
	}

	if (UMS_FurnitureUnit* FurnitureUnit = Cast<UMS_FurnitureUnit>(OwnerUnit.Get()))
	{
		if (FurnitureUnit->GetZoneType() == EMS_ZoneType::Display)
		{
			gItemMng.GetNoneDisplayItems(TakableItems);
		}
		else if (FurnitureUnit->GetZoneType() == EMS_ZoneType::Shelf)
		{
			gItemMng.GetPalletItems(TakableItems);
		}
		else
		{
			MS_ENSURE(false);
			return;
		}
	}
	
	TArray<TObjectPtr<UMS_StorageSlotElementData>> StorageItemElementDatas;
		
	// 빈 슬롯 하나 추가.
	const TObjectPtr<UMS_StorageSlotElementData> BlankData = MS_NewObject<UMS_StorageSlotElementData>(this);
	BlankData->SetSlotType(static_cast<int32>(EMS_ZoneType::Shelf));
	BlankData->SetItemId(INDEX_NONE);
	BlankData->OnClickShelfSlotDelegate.AddUObject(this, &UMS_ShelfStatus::OnClickedShelfSlotButton);
	StorageItemElementDatas.Emplace(BlankData);
	
	for(const auto TakableItem : TakableItems)
	{
		const TObjectPtr<UMS_StorageSlotElementData> Data = MS_NewObject<UMS_StorageSlotElementData>(this);
		Data->SetSlotType(static_cast<int32>(EMS_ZoneType::Shelf));
		Data->SetItemId(TakableItem.Key);
		Data->SetShelfCount(TakableItem.Value);
		Data->OnClickShelfSlotDelegate.AddUObject(this, &UMS_ShelfStatus::OnClickedShelfSlotButton);
		StorageItemElementDatas.Emplace(Data);
	}
	
	CPP_TileView->SetListItems(StorageItemElementDatas);
}

void UMS_ShelfStatus::OnClickedShelfSlotButton(int32 aItemId)
{
	if(OnClickedShelfSlotCallback)
	{
		OnClickedShelfSlotCallback(DisplaySlotIndex, aItemId);
	}
}
