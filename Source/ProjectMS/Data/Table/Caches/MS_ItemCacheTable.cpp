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

FMS_ItemData* UMS_ItemCacheTable::GetItem(int32 aItemId) const
{
	if(ItemDatas.Contains(aItemId))
	{
		FMS_ItemData* ItemData = *ItemDatas.Find(aItemId);
		return ItemData;
	}

	return nullptr;
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

const FMS_ItemData* UMS_ItemCacheTable::GetItemByName(const FName& aItemName)
{
	for (const auto& PairData : ItemDatas)
	{
		if (PairData.Value != nullptr && PairData.Value->ItemName == aItemName)
		{
			return PairData.Value;
		}
	}

	return nullptr;
}

TArray<FName> UMS_ItemCacheTable::GetAllItemNames()
{
	TArray<FName> ItemNameArray = {};

	for (const auto& PairData : ItemDatas)
	{
		if (PairData.Value != nullptr)
		{
			ItemNameArray.Add(PairData.Value->ItemName);
		}
	}

	return ItemNameArray;
}

EMS_TemperatureType UMS_ItemCacheTable::GetItemTemperature(int32 aItemId) const
{
	const FMS_ItemData* TargetItem = GetItem(aItemId);
	if(!TargetItem)
	{
		return EMS_TemperatureType::Undefined;
	}

	return static_cast<EMS_TemperatureType>(TargetItem->TemperatureType);
}

int32 UMS_ItemCacheTable::GetTotalItemPrice(const TMap<int32, int32>& _ItemArray)
{
	int32 TotalPrice = 0;
	for(const auto& Item : _ItemArray)
	{
		FMS_ItemData** ItemData = ItemDatas.Find(Item.Key);
		MS_CHECK(ItemData)

		TotalPrice += (*ItemData)->PriceMin * Item.Value;
	}

	return TotalPrice;
}

int32 UMS_ItemCacheTable::GetItemPrice(int32 ItemId) const
{
	const FMS_ItemData* ItemData = GetItem(ItemId);
	if(!ItemData)
	{
		return 0;
	}

	return ItemData->PriceMin;
}
