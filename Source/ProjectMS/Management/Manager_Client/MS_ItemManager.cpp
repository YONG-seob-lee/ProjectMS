// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ItemManager.h"

#include "Manager_Both/MS_UnitManager.h"
#include "Table/Caches/MS_ItemCacheTable.h"

UMS_ItemManager::UMS_ItemManager()
{
	InventoryManager = this;
}

UMS_ItemManager::~UMS_ItemManager()
{
}

void UMS_ItemManager::BuiltInInitialize()
{
	Super::BuiltInInitialize();
}

void UMS_ItemManager::Initialize()
{
	Super::Initialize();
}

void UMS_ItemManager::PostInitialize()
{
	Super::PostInitialize();
}

void UMS_ItemManager::PreFinalize()
{
	Super::PreFinalize();
}

void UMS_ItemManager::Finalize()
{
	Super::Finalize();
}

void UMS_ItemManager::BuiltInFinalize()
{
	Super::BuiltInFinalize();
}

void UMS_ItemManager::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
}

void UMS_ItemManager::CreateItem(int32 aItemId)
{
	const TObjectPtr<UMS_ItemCacheTable> ItemTable = Cast<UMS_ItemCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::Item));
	if(!ItemTable)
	{
		return;
	}

	ItemTable->GetItem(aItemId);
}

void UMS_ItemManager::CreateItem(const TMap<int32, FPacketItemDatas*>& aItems)
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
			gUnitMng.CreateUnit(ItemData->Id, EMS_UnitType::Item, Item.Value->Vector, Item.Value->Rotator);
		}
	}
}

void UMS_ItemManager::GetItem(TArray<FMS_Item*>& aItems, EMS_ItemType aItemType)
{
	
}

UMS_ItemManager* UMS_ItemManager::GetInstance()
{
	return InventoryManager;
}
