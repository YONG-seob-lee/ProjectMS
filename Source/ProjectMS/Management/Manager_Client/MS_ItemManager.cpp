// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ItemManager.h"

#include "Item/MS_Item.h"
#include "Manager_Both/MS_UnitManager.h"
#include "Table/Caches/MS_ItemCacheTable.h"
#include "Table/Caches/MS_StaffCacheTable.h"
#include "Widget/ListViewElement/ElementData/MS_StaffProfileElementData.h"

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

	// 나중에 실제 데이터로 대체
	ShelfItems.Emplace(4, 8);
	ShelfItems.Emplace(5, 2);
	ShelfItems.Emplace(6, 4);
	ShelfItems.Emplace(7, 3);
	ShelfItems.Emplace(8, 7);
	ShelfItems.Emplace(9, 1);
	ShelfItems.Emplace(10, 15);
	ShelfItems.Emplace(11, 10);
	ShelfItems.Emplace(12, 5);
	ShelfItems.Emplace(13, 1);
	ShelfItems.Emplace(14, 3);
	ShelfItems.Emplace(15, 1);

	const TObjectPtr<UMS_StaffCacheTable> StaffTable = Cast<UMS_StaffCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::Staff));
	MS_Ensure(StaffTable);

	TMap<int32, FMS_Staff*> StaffDatas;
	StaffTable->GetStaffDatas(StaffDatas);
	for(const auto& StaffData : StaffDatas)
	{
		UMS_StaffProfileElementData* Data = MS_NewObject<UMS_StaffProfileElementData>(this);
		Data->SetStaffId(StaffData.Key);
		StaffProfileDatas.Emplace(Data);
	}
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

void UMS_ItemManager::GetStaffData(TArray<TObjectPtr<UMS_StaffProfileElementData>>& aProfileDatas) const
{
	aProfileDatas.Empty();
	aProfileDatas = StaffProfileDatas;
}

void UMS_ItemManager::SetStaffPropertys(FMS_StaffProperty* aStaffProperty)
{
	StaffPropertys.Emplace(aStaffProperty);
}

UMS_ItemManager* UMS_ItemManager::GetInstance()
{
	return InventoryManager;
}
