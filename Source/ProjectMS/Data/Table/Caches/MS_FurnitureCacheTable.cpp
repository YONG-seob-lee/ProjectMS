// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_FurnitureCacheTable.h"

#include "Widget/ListViewElement/ElementData/MS_ConstructCategoryElementData.h"
#include "Widget/ListViewElement/ElementData/MS_ConstructItemElement.h"
#include "Widget/ListViewElement/ElementData/MS_OrderItemElementData.h"

void UMS_FurnitureCacheTable::Initialize(TObjectPtr<UMS_TableManager> aMng)
{
	Super::Initialize(aMng);

	BuildTable(aMng, EMS_TableDataType::Furniture, FurnitureDatas);
}

void UMS_FurnitureCacheTable::Finalize()
{
	Super::Finalize();
}

void UMS_FurnitureCacheTable::GetFurnitureData(EMS_ZoneType aZoneType, TArray<TObjectPtr<UMS_ConstructItemElement>>& aConstructArray)
{
	aConstructArray.Empty();

	for(const auto& StorageData : FurnitureDatas)
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

FMS_FurnitureData* UMS_FurnitureCacheTable::GetFurnitureData(int32 aFurnitureId) const
{
	if(FurnitureDatas.Contains(aFurnitureId))
	{
		FMS_FurnitureData* StorageData = *FurnitureDatas.Find(aFurnitureId);
		return StorageData;
	}

	return nullptr;
}

void UMS_FurnitureCacheTable::GetFurnitureCategoryData(TArray<TObjectPtr<UMS_ConstructCategoryElementData>>& aCategoryArray)
{
	aCategoryArray.Empty();

	for(int32 i = 1 ; i <= 3 ; i++)
	{
		TObjectPtr<UMS_ConstructCategoryElementData> Category = MS_NewObject<UMS_ConstructCategoryElementData>();
		Category->SetZoneType(i);
		aCategoryArray.Emplace(Category);
	}
}

void UMS_FurnitureCacheTable::GetOrderFurnitureElementDatas(TArray<TObjectPtr<UMS_OrderItemElementData>>& aOrderFurnitureElementDatas)
{
	aOrderFurnitureElementDatas.Empty();
	
	for(const auto& StorageData : FurnitureDatas)
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

int32 UMS_FurnitureCacheTable::GetFurniturePrice(int32 FurnitureTableId) const
{
	const FMS_FurnitureData* FurnitureData = GetFurnitureData(FurnitureTableId);
	if(!FurnitureData)
	{
		return 0;
	}

	return FurnitureData->Price;
}

int32 UMS_FurnitureCacheTable::GetTotalFurniturePrice(const TMap<int32, int32>& OrderFurnitures)
{
	int32 TotalPrice = 0;
	for(const auto& OrderFurniture : OrderFurnitures)
	{
		if(FMS_FurnitureData** FurnitureData = FurnitureDatas.Find(OrderFurniture.Key))
		{
			TotalPrice += (*FurnitureData)->Price * OrderFurniture.Value;	
		}
	}

	return TotalPrice;
}
