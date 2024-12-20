// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_InventoryManager.h"

#include "Manager_Both/MS_UnitManager.h"
#include "Table/Caches/MS_ItemCacheTable.h"

UMS_InventoryManager::UMS_InventoryManager()
{
	InventoryManager = this;
}

UMS_InventoryManager::~UMS_InventoryManager()
{
}

void UMS_InventoryManager::BuiltInInitialize()
{
	Super::BuiltInInitialize();
}

void UMS_InventoryManager::Initialize()
{
	Super::Initialize();
}

void UMS_InventoryManager::PostInitialize()
{
	Super::PostInitialize();
}

void UMS_InventoryManager::PreFinalize()
{
	Super::PreFinalize();
}

void UMS_InventoryManager::Finalize()
{
	Super::Finalize();
}

void UMS_InventoryManager::BuiltInFinalize()
{
	Super::BuiltInFinalize();
}

void UMS_InventoryManager::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
}

void UMS_InventoryManager::CreateItem(int32 aItemId)
{
	const TObjectPtr<UMS_ItemCacheTable> ItemTable = Cast<UMS_ItemCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::Item));
	if(!ItemTable)
	{
		return;
	}

	ItemTable->GetItem(aItemId);
}

void UMS_InventoryManager::CreateItem(const TMap<int32, FPacketItemDatas*>& aItems)
{
	const TObjectPtr<UMS_ItemCacheTable> ItemTable = Cast<UMS_ItemCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::Item));
	if(!ItemTable)
	{
		return;
	}

	for(auto& Item : aItems)
	{
		if(const FMS_Item* ItemData = ItemTable->GetItem(Item.Key))
		{
			// ItemData->Index 를 유닛 타입의 key 로 변경해야함.
			gUnitMng.CreateUnit(ItemData->Index, EMS_UnitType::Item, Item.Value->Vector, Item.Value->Rotator);
		}
	}
}

UMS_InventoryManager* UMS_InventoryManager::GetInstance()
{
	return InventoryManager;
}
