// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ContentsUtilities/MS_LevelDefine.h"
#include "Table/MS_CacheTable.h"
#include "Table/RowBase/MS_FurnitureData.h"
#include "MS_FurnitureCacheTable.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_FurnitureCacheTable : public UMS_CacheTable
{
	GENERATED_BODY()
public:
	virtual void Initialize(TObjectPtr<UMS_TableManager> aMng) override;
	virtual void Finalize() override;

	FORCEINLINE TMap<int32, FMS_FurnitureData*> GetFurnitureDatas() { return FurnitureDatas; }
	void GetFurnitureData(EMS_ZoneType aZoneType, TArray<TObjectPtr<class UMS_ConstructItemElement>>& aConstructArray);
	FMS_FurnitureData* GetFurnitureData(int32 aFurnitureId) const;
	void GetFurnitureCategoryData(TArray<TObjectPtr<class UMS_ConstructCategoryElementData>>& aCategoryArray);
	void GetOrderFurnitureElementDatas(TArray<TObjectPtr<class UMS_OrderItemElementData>>& aOrderFurnitureElementDatas);
	
	int32 GetFurniturePrice(int32 FurnitureTableId) const;
	int32 GetTotalFurniturePrice(const TMap<int32, int32>& OrderFurnitures);

private:
	TMap<int32, FMS_FurnitureData*> FurnitureDatas; 
};
