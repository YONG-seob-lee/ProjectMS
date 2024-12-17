// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ItemCacheTable.h"

void UMS_ItemCacheTable::Initialize(TObjectPtr<UMS_TableManager> aMng)
{
	Super::Initialize(aMng);
	BuildTable(aMng, EMS_TableDataType::Item, ItemDatas);
}

void UMS_ItemCacheTable::Finalize()
{
	Super::Finalize();
}
