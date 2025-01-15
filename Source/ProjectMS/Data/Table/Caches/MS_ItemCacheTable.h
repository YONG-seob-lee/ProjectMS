// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Table/MS_CacheTable.h"
#include "Table/RowBase/MS_ItemData.h"
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

	FMS_ItemData* GetItem(int32 aItemId);
	void GetItems(TMap<int32, FMS_ItemData*>& aItemDatas) const;
	void GetItemElementDatas(TArray<TObjectPtr<class UMS_ItemElementData>>& aItemElementDatas);
	void GetOrderItemElementDatas(TArray<TObjectPtr<class UMS_OrderItemElementData>>& aOrderItemElementDatas);

private:
	TMap<int32, FMS_ItemData*> ItemDatas;
	TMap<int32, FMS_ItemData*> MoneyDatas;
};
