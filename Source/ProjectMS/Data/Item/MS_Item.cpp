// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_Item.h"

#include "Table/Caches/MS_ItemCacheTable.h"

void UMS_Item::Initialize(int32 aItemId)
{
	ItemId = aItemId;
}

UTexture2D* UMS_Item::GetItemTexture() const
{
	const TObjectPtr<UMS_ItemCacheTable> ItemTable = Cast<UMS_ItemCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::ItemData));
	MS_CHECK(ItemTable);

	const FMS_ItemData* ItemData = ItemTable->GetItem(ItemId);
	MS_CHECK(ItemData);

	const FString ItemImagePath = gTableMng.GetPath(EMS_TableDataType::BasePathImgFile, ItemData->ImagePath);
	if(UTexture2D* ItemTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *ItemImagePath)))
	{
		return ItemTexture;
	}

	return nullptr;
}
