// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ItemCacheTable.h"

#include "Widget/ListViewElement/ElementData/MS_ItemElementData.h"
#include "Widget/ListViewElement/ElementData/MS_OrderItemElementData.h"

void UMS_ItemCacheTable::Initialize(TObjectPtr<UMS_TableManager> aMng)
{
	Super::Initialize(aMng);
	BuildTable(aMng, EMS_TableDataType::ItemData, ItemDatas);

	for(const auto& ItemData : ItemDatas)
	{
		if(ItemData.Value->TemperatureType == 0)
		{
			MoneyDatas.Emplace(ItemData.Key, ItemData.Value);
		}
	}
	for(const auto& MoneyData : MoneyDatas)
	{
		ItemDatas.Remove(MoneyData.Key);
	}
}

void UMS_ItemCacheTable::Finalize()
{
	Super::Finalize();
}

FMS_ItemData* UMS_ItemCacheTable::GetItem(int32 aItemId)
{
	FMS_ItemData** ItemData = ItemDatas.Find(aItemId);
	if(!ItemData)
	{
		return nullptr;
	}
	
	return *ItemData;
}

void UMS_ItemCacheTable::GetItems(TMap<int32, FMS_ItemData*>& aItemDatas) const
{
	aItemDatas.Empty();
	aItemDatas = ItemDatas;
}

void UMS_ItemCacheTable::GetItemElementDatas(TArray<TObjectPtr<UMS_ItemElementData>>& aItemElementDatas)
{
	aItemElementDatas.Empty();
	
	for(const auto& ItemData : ItemDatas)
	{
		TObjectPtr<UMS_ItemElementData> ItemElementData = MS_NewObject<UMS_ItemElementData>();
		MS_CHECK(ItemElementData);

		ItemElementData->SetElementName(ItemData.Value->ItemName.ToString());
		const FString ItemImagePath = gTableMng.GetPath(EMS_TableDataType::BasePathImgFile, ItemData.Value->ImagePath);
		if(UTexture2D* ItemTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *ItemImagePath)))
		{
			ItemElementData->SetImage(ItemTexture);	
		}
		aItemElementDatas.Emplace(ItemElementData);
	}
}

void UMS_ItemCacheTable::GetOrderItemElementDatas(TArray<TObjectPtr<UMS_OrderItemElementData>>& aOrderItemElementDatas)
{
	aOrderItemElementDatas.Empty();
	
	for(const auto& ItemData : ItemDatas)
	{
		TObjectPtr<UMS_OrderItemElementData> OrderItemElementData = MS_NewObject<UMS_OrderItemElementData>();
		MS_CHECK(OrderItemElementData);

		OrderItemElementData->SetItemId(ItemData.Key);
		OrderItemElementData->SetItemName(ItemData.Value->ItemName.ToString());
		const FString ItemImagePath = gTableMng.GetPath(EMS_TableDataType::BasePathImgFile, ItemData.Value->ImagePath);
		if(UTexture2D* ItemTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *ItemImagePath)))
		{
			OrderItemElementData->SetImage(ItemTexture);	
		}
		OrderItemElementData->SetItemPrice(ItemData.Value->PriceMin);
		OrderItemElementData->SetItemCount(0);
		aOrderItemElementDatas.Emplace(OrderItemElementData);
	}
}

UTexture2D* UMS_ItemCacheTable::GetItemImage(int32 aItemId)
{
	if(const FMS_ItemData* ItemData = GetItem(aItemId))
	{
		const FString ItemImagePath = gTableMng.GetPath(EMS_TableDataType::BasePathImgFile, ItemData->ImagePath);
		if(UTexture2D* ItemTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *ItemImagePath)))
		{
			return ItemTexture;
		}
	}
	
	return nullptr;
}
