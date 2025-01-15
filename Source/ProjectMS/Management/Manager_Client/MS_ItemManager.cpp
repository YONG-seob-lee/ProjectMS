// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ItemManager.h"

#include "Item/MS_Item.h"
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

UMS_ItemManager* UMS_ItemManager::GetInstance()
{
	return InventoryManager;
}
