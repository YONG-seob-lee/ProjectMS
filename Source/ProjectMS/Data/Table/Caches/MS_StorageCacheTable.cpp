// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_StorageCacheTable.h"

#include "Manager_Client/MS_ItemManager.h"
#include "Widget/ListViewElement/ElementData/MS_ConstructCategoryElementData.h"
#include "Widget/ListViewElement/ElementData/MS_ConstructItemElement.h"
#include "Widget/ListViewElement/ElementData/MS_OrderItemElementData.h"

void UMS_StorageCacheTable::Initialize(TObjectPtr<UMS_TableManager> aMng)
{
	Super::Initialize(aMng);

	BuildTable(aMng, EMS_TableDataType::Storage, StorageDatas);
}

void UMS_StorageCacheTable::Finalize()
{
	Super::Finalize();
}

void UMS_StorageCacheTable::GetStorageData(EMS_ZoneType aZoneType, TArray<TObjectPtr<UMS_ConstructItemElement>>& aConstructArray)
{
	aConstructArray.Empty();

	for(const auto& StorageData : StorageDatas)
	{
		if(StorageData.Value->ZoneType != static_cast<int32>(aZoneType))
		{
			continue;
		}
		
		TObjectPtr<UMS_ConstructItemElement> ConstructItem = MS_NewObject<UMS_ConstructItemElement>();
		ConstructItem->SetElementName(StorageData.Value->StandName.ToString());
		const FString ImagePath = gTableMng.GetPath(EMS_TableDataType::BasePathImgFile, StorageData.Value->ImagePath); 
		if(UTexture2D* ImageImage = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *ImagePath)))
		{
			ConstructItem->SetImage(ImageImage);
		}
		ConstructItem->SetItemId(StorageData.Key);
		aConstructArray.Emplace(ConstructItem);
	}
}

FMS_StorageData* UMS_StorageCacheTable::GetStorageData(int32 aStorageId) const
{
	if(StorageDatas.Contains(aStorageId))
	{
		FMS_StorageData* StorageData = *StorageDatas.Find(aStorageId);
		return StorageData;
	}

	return nullptr;
}

void UMS_StorageCacheTable::GetStorageCategoryData(TArray<TObjectPtr<UMS_ConstructCategoryElementData>>& aCategoryArray)
{
	aCategoryArray.Empty();

	for(int32 i = 3 ; i > 0 ; i--)
	{
		TObjectPtr<UMS_ConstructCategoryElementData> Category = MS_NewObject<UMS_ConstructCategoryElementData>();
		Category->SetZoneType(i);
		aCategoryArray.Emplace(Category);
	}
}

void UMS_StorageCacheTable::GetOrderFurnitureElementDatas(TArray<TObjectPtr<UMS_OrderItemElementData>>& aOrderFurnitureElementDatas)
{
	aOrderFurnitureElementDatas.Empty();
	
	for(const auto& StorageData : StorageDatas)
	{
		TObjectPtr<UMS_OrderItemElementData> OrderItemElementData = MS_NewObject<UMS_OrderItemElementData>();
		MS_CHECK(OrderItemElementData);

		OrderItemElementData->SetItemId(StorageData.Key);
		OrderItemElementData->SetItemName(StorageData.Value->StandName.ToString());
		const FString ItemImagePath = gTableMng.GetPath(EMS_TableDataType::BasePathImgFile, StorageData.Value->ImagePath);
		if(UTexture2D* ItemTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *ItemImagePath)))
		{
			OrderItemElementData->SetImage(ItemTexture);	
		}
		OrderItemElementData->SetItemPrice(StorageData.Value->Price);
		OrderItemElementData->SetItemCount(0);
		aOrderFurnitureElementDatas.Emplace(OrderItemElementData);
	}
}
