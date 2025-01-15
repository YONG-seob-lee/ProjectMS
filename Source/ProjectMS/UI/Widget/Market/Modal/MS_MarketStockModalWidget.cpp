// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_MarketStockModalWidget.h"

#include "MS_Define.h"
#include "Manager_Client/MS_ItemManager.h"
#include "Table/Caches/MS_ItemCacheTable.h"
#include "Widget/ListViewElement/ElementData/MS_StockItemElementData.h"
#include "Widget/WidgetComponent/MS_TileView.h"

void UMS_MarketStockModalWidget::NativeConstruct()
{
	Super::NativeConstruct();

	const TMap<int32, int32> Items = gItemMng.GetCurrentItems();
	TArray<UMS_StockItemElementData*> StockItemElementDatas;
	CreateStockElement(Items, StockItemElementDatas);
	if(CPP_ItemTileView)
	{
		CPP_ItemTileView->SetElements(TArray<UObject*>(StockItemElementDatas));
	}
}

void UMS_MarketStockModalWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UMS_MarketStockModalWidget::CreateStockElement(TMap<int32, int32> aItems, TArray<UMS_StockItemElementData*>& aStockItemElementData)
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
		OrderItemElementData->SetItemCount(Item.Value);
		aStockItemElementData.Emplace(OrderItemElementData);
	}
}