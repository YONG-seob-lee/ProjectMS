// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Table/MS_CacheTable.h"
#include "Table/RowBase/MS_Item.h"
#include "MS_ItemCacheTable.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_ItemCacheTable : public UMS_CacheTable
{
	GENERATED_BODY()
public:
	virtual void Initialize(TObjectPtr<UMS_TableManager> aMng) override;
	virtual void Finalize() override;

	FMS_Item* GetItem(int32 aItemId);
	
private:
	TMap<int32, FMS_Item*> ItemDatas; 
};
