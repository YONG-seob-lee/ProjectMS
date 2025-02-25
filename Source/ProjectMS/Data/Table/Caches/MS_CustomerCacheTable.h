// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Table/MS_CacheTable.h"
#include "Table/RowBase/MS_Customer.h"
#include "MS_CustomerCacheTable.generated.h"

struct FMS_CustomerData
{
public:
	FMS_CustomerData() {};
	FMS_CustomerData(int32 aDuckColor, int32 aMaxItemKind, int32 aMaxItemCount);

private:
	int32 DuckColor = 0;
	TMap<int32, int32> PurchaseItem = {};
};

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_CustomerCacheTable : public UMS_CacheTable
{
	GENERATED_BODY()
public:
	virtual void Initialize(TObjectPtr<UMS_TableManager> aMng) override;
	virtual void Finalize() override;
	void MakeNewCustomerData(FMS_CustomerData& NewCustomerData);

private:
	TMap<int32, FMS_Customer*> CustomerDatas = {};
};
