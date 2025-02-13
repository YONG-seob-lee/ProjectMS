// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_SelectRequestedItemWidget.h"

#include "Manager_Client/MS_ItemManager.h"
#include "Widget/ListViewElement/ElementData/MS_StorageSlotElementData.h"
#include "MS_Define.h"
#include "MS_UnitBase.h"
#include "Units/MS_FurnitureUnit.h"
#include "Widget/WidgetComponent/MS_TileView.h"


void UMS_SelectRequestedItemWidget::NativeConstruct()
{
	Super::NativeConstruct();
	CPP_TileView->SetScrollbarVisibility(ESlateVisibility::Collapsed);
}

void UMS_SelectRequestedItemWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UMS_SelectRequestedItemWidget::SetOwnerUnit(TWeakObjectPtr<UMS_UnitBase> aOwnerUnit)
{
	OwnerUnit = aOwnerUnit;
}

void UMS_SelectRequestedItemWidget::SetTileView()
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
	BlankData->SetSlotData(FMS_SlotData());
	BlankData->OnClickShelfSlotDelegate.AddUObject(this, &UMS_SelectRequestedItemWidget::OnClickedShelfSlotButton);
	StorageItemElementDatas.Emplace(BlankData);
	
	for(const auto TakableItem : TakableItems)
	{
		const TObjectPtr<UMS_StorageSlotElementData> Data = MS_NewObject<UMS_StorageSlotElementData>(this);
		Data->SetSlotType(static_cast<int32>(EMS_ZoneType::Shelf));
		Data->SetSlotData(FMS_SlotData(TakableItem.Key, TakableItem.Key, TakableItem.Value));
		Data->SetShelfCount(TakableItem.Value);
		Data->OnClickShelfSlotDelegate.AddUObject(this, &UMS_SelectRequestedItemWidget::OnClickedShelfSlotButton);
		StorageItemElementDatas.Emplace(Data);
	}
	
	CPP_TileView->SetListItems(StorageItemElementDatas);
}

void UMS_SelectRequestedItemWidget::OnClickedShelfSlotButton(int32 aItemId)
{
	if(OnClickedShelfSlotCallback)
	{
		OnClickedShelfSlotCallback(DisplaySlotIndex, aItemId);
	}
}
