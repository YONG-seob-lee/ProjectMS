// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_SaleStandCacheTable.h"

void UMS_SaleStandCacheTable::Initialize(TObjectPtr<UMS_TableManager> aMng)
{
	Super::Initialize(aMng);

	BuildTable(aMng, EMS_TableDataType::SaleStand, SaleStandDatas);
}

void UMS_SaleStandCacheTable::Finalize()
{
	Super::Finalize();
}
