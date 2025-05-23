﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_MarketOrderCheckModalWidget.h"

#include "MS_Define.h"
#include "Manager_Client/MS_ItemManager.h"
#include "Table/Caches/MS_ItemCacheTable.h"
#include "Widget/ListViewElement/ElementData/MS_StockItemElementData.h"
#include "Widget/WidgetComponent/MS_TileView.h"
#include "Widget/WidgetComponent/MS_WidgetSwitcher.h"

void UMS_MarketOrderCheckModalWidget::NativeConstruct()
{
	Super::NativeConstruct();

	TMap<int32, int32> OrderItems;
	gItemMng.GetOrderItems(OrderItems);
	TArray<UMS_StockItemElementData*> StockOrderItemElementDatas;
	CreateStockElement(OrderItems, StockOrderItemElementDatas);

	if(StockOrderItemElementDatas.Num() == 0)
	{
		CPP_ItemSwitcher->SetActiveWidgetIndex(0);
	}
	else
	{
		CPP_ItemSwitcher->SetActiveWidgetIndex(1);
		if(CPP_ItemTileView)
		{
			CPP_ItemTileView->SetElements(TArray<UObject*>(StockOrderItemElementDatas));
		}
	}
}

void UMS_MarketOrderCheckModalWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UMS_MarketOrderCheckModalWidget::CreateStockElement(TMap<int32, int32> aItems, TArray<UMS_StockItemElementData*>& aStockItemElementData)
{
	aStockItemElementData.Empty();

	const TObjectPtr<UMS_ItemCacheTable> ItemTable = Cast<UMS_ItemCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::ItemData));
	MS_CHECK(ItemTable);
	
	for(const auto& Item : aItems)
	{
		const FMS_ItemData* ItemData = ItemTable->GetItem(Item.Key);
		if(!ItemData)
		{
			continue;
		}
		
		TObjectPtr<UMS_StockItemElementData> OrderItemElementData = MS_NewObject<UMS_StockItemElementData>();
		MS_CHECK(OrderItemElementData);

		const FString ItemImagePath = gTableMng.GetPath(EMS_TableDataType::BasePathImgFile, ItemData->ImagePath);
		if(UTexture2D* ItemTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *ItemImagePath)))
		{
			OrderItemElementData->SetImage(ItemTexture);	
		}
		OrderItemElementData->SetItemName(ItemData->ItemName.ToString());
		OrderItemElementData->SetItemCount(Item.Value);
		aStockItemElementData.Emplace(OrderItemElementData);
	}
}