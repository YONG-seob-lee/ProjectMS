// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ContentsUtilities/MS_LevelDefine.h"
#include "Manager_Client/MS_ItemManager.h"
#include "Table/MS_CacheTable.h"
#include "Table/RowBase/MS_StorageData.h"
#include "MS_StorageCacheTable.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_StorageCacheTable : public UMS_CacheTable
{
	GENERATED_BODY()
public:
	virtual void Initialize(TObjectPtr<UMS_TableManager> aMng) override;
	virtual void Finalize() override;

	FORCEINLINE TMap<int32, FMS_StorageData*> GetStorageDatas() { return StorageDatas; }
	void GetStorageData(EMS_ZoneType aZoneType, TArray<TObjectPtr<class UMS_ConstructItemElement>>& aConstructArray);
	FMS_StorageData* GetStorageData(int32 aStorageId) const;
	void GetStorageCategoryData(TArray<TObjectPtr<class UMS_ConstructCategoryElementData>>& aCategoryArray);

	
private:
	TMap<int32, FMS_StorageData*> StorageDatas; 
};
