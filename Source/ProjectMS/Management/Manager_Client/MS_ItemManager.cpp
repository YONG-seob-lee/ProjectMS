// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ItemManager.h"

#include "Controller/MS_PlayerController.h"
#include "Manager_Both/MS_UnitManager.h"
#include "PlayerState/MS_PlayerState.h"
#include "Table/Caches/MS_StaffCacheTable.h"
#include "Units/MS_FurnitureUnit.h"
#include "Widget/ListViewElement/ElementData/MS_StaffProfileElementData.h"


UMS_ItemManager::UMS_ItemManager()
{
	ItemManager = this;
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
	
	const TObjectPtr<UMS_StaffCacheTable> StaffTable = Cast<UMS_StaffCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::Staff));
	MS_ENSURE(StaffTable);

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

void UMS_ItemManager::GetCurrentItems(TMap<int32, int32>& OutItems) const
{
	OutItems.Empty();

	UWorld* World = GetWorld();
	if (!IsValid(World))
	{
		return;
	}

	AMS_PlayerController* PlayerController = World->GetFirstPlayerController<AMS_PlayerController>();
	if (!IsValid(PlayerController))
	{
		return;
	}
	
	AMS_PlayerState* PlayerState = PlayerController->GetPlayerState<AMS_PlayerState>();
	if (!IsValid(PlayerState))
	{
		return;
	}

	PlayerState->GetAllItems(OutItems);

	for (const auto& AddedItem : AddedItems)
	{
		int32& Amount = OutItems.FindOrAdd(AddedItem.Key);
		Amount += AddedItem.Value;
	}

	for (const auto& SoldItem : SoldItems)
	{
		int32& Amount = OutItems.FindOrAdd(SoldItem.Key);
		Amount -= SoldItem.Value;
	}
}

void UMS_ItemManager::GetDisplayItems(TMap<int32, int32>& OutItems) const
{
	OutItems.Empty();

	if (const TObjectPtr UnitManager = gUnitMng)
	{
		TArray<TObjectPtr<UMS_UnitBase>> Units;
		UnitManager->GetUnits(EMS_UnitType::Furniture, Units);

		for (TObjectPtr<UMS_UnitBase> Unit : Units)
		{
			if (UMS_FurnitureUnit* FurnitureUnit = Cast<UMS_FurnitureUnit>(Unit.Get()))
			{
				if (FurnitureUnit->GetZoneType() != EMS_ZoneType::Display)
				{
					continue;
				}
				
				TArray<FMS_SlotData> FurnitureSlotDatas;
				FurnitureUnit->GetSlotDatas(FurnitureSlotDatas);

				for (const FMS_SlotData& SlotData: FurnitureSlotDatas)
				{
					if (SlotData.CurrentItemTableId == INDEX_NONE || SlotData.CurrentItemTableId == 0)
					{
						continue;
					}
					
					int32& Amount = OutItems.FindOrAdd(SlotData.CurrentItemTableId);
					Amount += SlotData.CurrentItemAmount;
				}
			}
		}
	}
}

void UMS_ItemManager::GetNoneDisplayItems(TMap<int32, int32>& OutItems) const
{
	GetCurrentItems(OutItems);

	TMap<int32, int32> DisplayItems;
	GetDisplayItems(DisplayItems);

	for (const auto& DisplayItem : DisplayItems)
	{
		int32& Amount = OutItems.FindOrAdd(DisplayItem.Key);
		Amount -= DisplayItem.Value;
	}
}

void UMS_ItemManager::GetStaffProfileElementData(TArray<TObjectPtr<UMS_StaffProfileElementData>>& aProfileDatas) const
{
	aProfileDatas.Empty();
	aProfileDatas = StaffProfileDatas;
}

void UMS_ItemManager::SetStaffProperty(int32 aStaffId, UMS_StaffPropertyElementData* aStaffProperty)
{
	StaffPropertys.Emplace(aStaffId, aStaffProperty);
}

void UMS_ItemManager::GetStaffPropertys(TArray<UMS_StaffPropertyElementData*>& aStaffPropertys)
{
	aStaffPropertys.Empty();
	StaffPropertys.GenerateValueArray(aStaffPropertys);
}

UMS_ItemManager* UMS_ItemManager::GetInstance()
{
	return ItemManager;
}
