// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Table/MS_CacheTable.h"
#include "Table/RowBase/MS_SaleStand.h"
#include "MS_SaleStandCacheTable.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_SaleStandCacheTable : public UMS_CacheTable
{
	GENERATED_BODY()
public:
	virtual void Initialize(TObjectPtr<UMS_TableManager> aMng) override;
	virtual void Finalize() override;
private:
	TMap<int32, FMS_SaleStand*> SaleStandDatas; 
};
