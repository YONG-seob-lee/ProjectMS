// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_InventoryManager.h"

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

UMS_InventoryManager* UMS_InventoryManager::GetInstance()
{
	return InventoryManager;
}
