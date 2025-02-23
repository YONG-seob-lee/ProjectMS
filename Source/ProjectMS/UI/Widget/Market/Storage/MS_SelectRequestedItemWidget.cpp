// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_SelectRequestedItemWidget.h"

#include "Manager_Client/MS_ItemManager.h"
#include "Widget/ListViewElement/ElementData/MS_StorageSlotElementData.h"
#include "MS_Define.h"
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

void UMS_SelectRequestedItemWidget::SetTileView(EMS_TemperatureType aTemperatureType)
{
	TMap<int32, int32> RequestableItems;
	
	if (OwnerZoneType == EMS_ZoneType::Display)
	{
		gItemMng.GetStorageItems(EMS_ZoneType::Shelf, RequestableItems, aTemperatureType);
	}
	else if (OwnerZoneType == EMS_ZoneType::Shelf)
	{
		gItemMng.GetStorageItems(EMS_ZoneType::Pallet, RequestableItems);
	}
	else
	{
		MS_ENSURE(false);
		return;
	}
	
	TArray<TObjectPtr<UMS_StorageSlotElementData>> StorageItemElementDatas;
		
	// 빈 슬롯 하나 추가.
	const TObjectPtr<UMS_StorageSlotElementData> BlankData = MS_NewObject<UMS_StorageSlotElementData>(this);
	BlankData->SetSlotType(EMS_ItemSlotUIType::Requestable);
	BlankData->SetSlotData(FMS_SlotData());
	BlankData->OnClickShelfSlotDelegate.AddUObject(this, &UMS_SelectRequestedItemWidget::OnClickedShelfSlotButton);
	StorageItemElementDatas.Emplace(BlankData);
	
	for(const auto RequestableItem : RequestableItems)
	{
		const TObjectPtr<UMS_StorageSlotElementData> Data = MS_NewObject<UMS_StorageSlotElementData>(this);
		Data->SetSlotType(EMS_ItemSlotUIType::Requestable);
		Data->SetSlotData(FMS_SlotData(RequestableItem.Key, RequestableItem.Key, RequestableItem.Value));
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
