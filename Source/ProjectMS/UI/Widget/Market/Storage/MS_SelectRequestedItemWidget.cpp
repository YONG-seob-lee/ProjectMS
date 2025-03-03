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
	TMap<int32, int32> DeployableItems;
	TMap<int32, int32> RequestStateItems;
	
	if (OwnerZoneType == EMS_ZoneType::Display)
	{
		gItemMng.GetDeployableItems(DeployableItems, aTemperatureType);
		gItemMng.GetStorageItems(EMS_ZoneType::Shelf, RequestStateItems, aTemperatureType);
	}
	else if (OwnerZoneType == EMS_ZoneType::Shelf)
	{
		gItemMng.GetDeployableItems(DeployableItems, aTemperatureType);
		gItemMng.GetStorageItems(EMS_ZoneType::Pallet, RequestStateItems);
	}
	else
	{
		return;
	}
	
	TArray<TObjectPtr<UMS_StorageSlotElementData>> StorageItemElementDatas;
	
	// 빈 슬롯 하나 추가.
	const TObjectPtr<UMS_StorageSlotElementData> BlankData = MS_NewObject<UMS_StorageSlotElementData>(this);
	BlankData->SetSlotType(EMS_ItemSlotUIType::Requestable);
	BlankData->SetSlotData(FMS_SlotData());
	BlankData->OnClickShelfSlotDelegate.AddUObject(this, &UMS_SelectRequestedItemWidget::OnClickedShelfSlotButton);
	StorageItemElementDatas.Emplace(BlankData);
	
	for(const auto DeployableItem : DeployableItems)
	{
		const TObjectPtr<UMS_StorageSlotElementData> Data = MS_NewObject<UMS_StorageSlotElementData>(this);
		Data->SetSlotType(EMS_ItemSlotUIType::Requestable);

		int32 ItemCount = 0;
		
		if (RequestStateItems.Contains(DeployableItem.Key))
		{
			ItemCount = *RequestStateItems.Find(DeployableItem.Key);
		}

		Data->SetSlotData(FMS_SlotData(DeployableItem.Key, DeployableItem.Key, ItemCount));
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
