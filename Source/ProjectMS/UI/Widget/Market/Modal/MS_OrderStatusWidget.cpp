// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_OrderStatusWidget.h"

#include "Manager_Client/MS_ItemManager.h"
#include "Table/Caches/MS_ItemCacheTable.h"
#include "Widget/ListViewElement/ElementData/MS_ItemElementData.h"
#include "Widget/WidgetComponent/MS_TileView.h"

void UMS_OrderStatusWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(CPP_OrderItemTileView)
	{
		TArray<UMS_ItemElementData*> ItemElementDatas = {};
		TMap<int32, int32> OrderItems = {};
		gItemMng.GetOrderItems(OrderItems);

		const TObjectPtr<UMS_ItemCacheTable> ItemTable = Cast<UMS_ItemCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::ItemData));
		MS_ENSURE(ItemTable);
		
		for(const auto& OrderItem : OrderItems)
		{
			UMS_ItemElementData* ItemElementData = MS_NewObject<UMS_ItemElementData>();
			ItemElementData->ShowItemName(false);
			ItemElementData->ShowItemCount(true);
			
			ItemElementData->SetImage(ItemTable->GetItemImage(OrderItem.Key));
			ItemElementData->SetItemCount(OrderItem.Value);
			ItemElementDatas.Emplace(ItemElementData);	
		}
		
		CPP_OrderItemTileView->SetListItems(ItemElementDatas);
	}
}

void UMS_OrderStatusWidget::NativeDestruct()
{
	Super::NativeDestruct();
}
