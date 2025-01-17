// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ShelfStatus.h"

#include "Manager_Client/MS_ItemManager.h"
#include "Widget/ListViewElement/ElementData/MS_StorageSlotElementData.h"
#include "MS_Define.h"
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

void UMS_ShelfStatus::SetTileView(int32 aDisplaySlotIndex)
{
	SetDisplaySlotIndex(aDisplaySlotIndex);
	
	TMap<int32, int32> ShelfItems = gItemMng.GetShelfItems();
	TArray<TObjectPtr<UMS_StorageSlotElementData>> StorageItemElementDatas;

	// 빈 슬롯 하나 추가.
	const TObjectPtr<UMS_StorageSlotElementData> BlankData = MS_NewObject<UMS_StorageSlotElementData>(this);
	BlankData->SetSlotType(static_cast<int32>(EMS_StorageType::Shelf));
	BlankData->SetItemId(INDEX_NONE);
	BlankData->OnClickShelfSlotDelegate.AddUObject(this, &UMS_ShelfStatus::OnClickedShelfSlotButton);
	StorageItemElementDatas.Emplace(BlankData);
	
	for(const auto ShelfItem : ShelfItems)
	{
		const TObjectPtr<UMS_StorageSlotElementData> Data = MS_NewObject<UMS_StorageSlotElementData>(this);
		Data->SetSlotType(static_cast<int32>(EMS_StorageType::Shelf));
		Data->SetItemId(ShelfItem.Key);
		Data->SetShelfCount(ShelfItem.Value);
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
