// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_StorageCacheTable.h"

void UMS_StorageCacheTable::Initialize(TObjectPtr<UMS_TableManager> aMng)
{
	Super::Initialize(aMng);

	BuildTable(aMng, EMS_TableDataType::Storage, SaleStandDatas);
}

void UMS_StorageCacheTable::Finalize()
{
	Super::Finalize();
}
