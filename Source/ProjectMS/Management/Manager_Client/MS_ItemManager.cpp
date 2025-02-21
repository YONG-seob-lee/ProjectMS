// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ItemManager.h"

#include "MS_ModeManager.h"
#include "MS_SceneManager.h"
#include "MS_ScheduleManager.h"
#include "Controller/MS_PlayerController.h"
#include "Manager_Both/MS_UnitManager.h"
#include "PlayerState/MS_PlayerState.h"
#include "Table/Caches/MS_ItemCacheTable.h"
#include "Table/Caches/MS_StaffCacheTable.h"
#include "Units/MS_FurnitureUnit.h"
#include "Widget/ListViewElement/ElementData/MS_StaffProfileElementData.h"
#include "Widget/ListViewElement/ElementData/MS_StaffPropertyElementData.h"


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
	
	// 해당 데이터는 원래라면 서버에서 받아야 함
	const TObjectPtr<UMS_StaffCacheTable> StaffTable = Cast<UMS_StaffCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::Staff));
	MS_ENSURE(StaffTable);

	TMap<int32, FMS_Staff*> StaffDatas;
	StaffTable->GetStaffDatas(StaffDatas);
	for(const auto& StaffData : StaffDatas)
	{
		UMS_StaffProfileElementData* Data = MS_NewObject<UMS_StaffProfileElementData>(this);
		Data->SetStaffId(StaffData.Key);
		Data->SetWorkDay(FMath::RandRange(30, 120));
		StaffProfileDatas.Emplace(Data);
	}
	// 여기까지
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

void UMS_ItemManager::BeginPlay()
{
	Super::BeginPlay();

	// Furniture
	InitializePlayerDatas();
}

void UMS_ItemManager::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
}

void UMS_ItemManager::GetRemainItems(TMap<int32, int32>& OutItems) const
{
	OutItems = Items;

	for (const auto& SoldItem : SoldItems)
	{
		int32& Count = OutItems.FindOrAdd(SoldItem.Key);
		Count -= SoldItem.Value;
	}
}

int32 UMS_ItemManager::GetRemainItemCount(int32 aItemId)
{
	const int32* pItemCount = Items.Find(aItemId);
	if(!pItemCount)
	{
		return 0;
	}

	int32 ItemCount = *pItemCount;

	if (SoldItems.Contains(aItemId))
	{
		ItemCount -= *SoldItems.Find(aItemId);
	}

	return ItemCount;
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
			if (const UMS_FurnitureUnit* FurnitureUnit = Cast<UMS_FurnitureUnit>(Unit.Get()))
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
					
					int32& Count = OutItems.FindOrAdd(SlotData.CurrentItemTableId);
					Count += SlotData.CurrentItemCount;
				}
			}
		}
	}
}

int32 UMS_ItemManager::GetDisplayItemCount(int32 aItemId) const
{
	TMap<int32, int32> DisplayItems;
	GetDisplayItems(DisplayItems);

	const int32* ItemCount = DisplayItems.Find(aItemId);
	if(!ItemCount)
	{
		return 0;
	}
	
	return *ItemCount;
}

void UMS_ItemManager::GetShelfItems(TMap<int32, int32>& OutItems, EMS_TemperatureType aTemperatureType /* = EMS_TemperatureType::Undefined */) const
{
	OutItems.Empty();

	if (const TObjectPtr UnitManager = gUnitMng)
	{
		TArray<TObjectPtr<UMS_UnitBase>> Units;
		UnitManager->GetUnits(EMS_UnitType::Furniture, Units);

		for (TObjectPtr<UMS_UnitBase> Unit : Units)
		{
			const UMS_FurnitureUnit* FurnitureUnit = Cast<UMS_FurnitureUnit>(Unit.Get());
			if (!FurnitureUnit)
			{
				continue;
			}
			if (FurnitureUnit->GetZoneType() != EMS_ZoneType::Shelf)
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

				if(aTemperatureType != EMS_TemperatureType::Undefined)
				{
					TObjectPtr<UMS_ItemCacheTable> ItemTable = Cast<UMS_ItemCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::ItemData));
					MS_ENSURE(ItemTable);
					
					if(ItemTable->GetItemTemperature(SlotData.CurrentItemTableId) != aTemperatureType)
					{
						continue;
					}	
				}
					
				int32& Count = OutItems.FindOrAdd(SlotData.CurrentItemTableId);
				Count += SlotData.CurrentItemCount;
			}
		}
	}
}

int32 UMS_ItemManager::GetShelfItemCount(int32 aItemId) const
{
	int32 ItemCount = 0;

	if (const TObjectPtr UnitManager = gUnitMng)
	{
		TArray<TObjectPtr<UMS_UnitBase>> Units;
		UnitManager->GetUnits(EMS_UnitType::Furniture, Units);

		for (TObjectPtr<UMS_UnitBase> Unit : Units)
		{
			if (UMS_FurnitureUnit* FurnitureUnit = Cast<UMS_FurnitureUnit>(Unit.Get()))
			{
				if (FurnitureUnit->GetZoneType() != EMS_ZoneType::Shelf)
				{
					continue;
				}
				
				TArray<FMS_SlotData> FurnitureSlotDatas;
				FurnitureUnit->GetSlotDatas(FurnitureSlotDatas);

				for (const FMS_SlotData& SlotData: FurnitureSlotDatas)
				{
					if (SlotData.CurrentItemTableId == aItemId)
					{
						ItemCount += SlotData.CurrentItemCount; 
					}
				}
			}
		}
	}
	
	return ItemCount;
}

void UMS_ItemManager::GetPalletItems(TMap<int32, int32>& OutItems) const
{
	OutItems = Items;


	TMap<int32, int32> DisplayItems;
	GetDisplayItems(DisplayItems);

	for (const auto& DisplayItem : DisplayItems)
	{
		int32& Count = OutItems.FindOrAdd(DisplayItem.Key);
		Count -= DisplayItem.Value;
	}
	
	TMap<int32, int32> ShelfItems;
	GetShelfItems(ShelfItems);

	for (const auto& ShelfItem : ShelfItems)
	{
		int32& Count = OutItems.FindOrAdd(ShelfItem.Key);
		Count -= ShelfItem.Value;
	}
}

int32 UMS_ItemManager::GetPalletItemCount(int32 aItemId)
{
	return GetRemainItemCount(aItemId) - GetDisplayItemCount(aItemId) - GetShelfItemCount(aItemId);
}

bool UMS_ItemManager::IsAvailablePurchase() const
{
	if(gSceneMng.GetCurrentLevelType() != EMS_LevelType::MarketLevel)
	{
		return false;
	}

	const FMS_GameDate& GameDate = gScheduleMng.GetGameDate();
	if(FMS_GameDate::IsNight(GameDate.DailyTimeZone))
	{
		return true;
	}
	
	if(gScheduleMng.IsOverTime(EMS_MarketScheduleEvent::LoadingUnloading) == false)
	{
		return false;
	}

	return true;
}

void UMS_ItemManager::GetNotDeployFurniture(TMap<int32, int32>& aNotDeployFurnitures)
{
	aNotDeployFurnitures = Furnitures;

	for(const auto& GridPositionToMarketFurnitureData : GridPositionToMarketFurnitureDatas)
	{
		int32& FurnitureCount = aNotDeployFurnitures.FindOrAdd(GridPositionToMarketFurnitureData.Value.FurnitureTableId);
		FurnitureCount -= 1;
	}
}

void UMS_ItemManager::AddFurnitureData(int32 aFurnitureTableId, const FIntVector2& aGridPosition, EMS_Rotation aRotation)
{
	if (GridPositionToMarketFurnitureDatas.Contains(aGridPosition))
	{
		MS_LOG_VERBOSITY(Error, TEXT("[%s] There is alreay Furniture at this grid position. [Grid Position : %d, %d]")
			, *MS_FUNC_STRING, aGridPosition.X, aGridPosition.Y);
		MS_CHECK(false);
	}
	
	GridPositionToMarketFurnitureDatas.Emplace(aGridPosition, FMS_FurniturePositionData(aFurnitureTableId, aGridPosition, aRotation));
}

void UMS_ItemManager::AddFurnitureData(FMS_FurniturePositionData aFurnitureData)
{
	if (GridPositionToMarketFurnitureDatas.Contains(aFurnitureData.GridPosition))
	{
		MS_LOG_VERBOSITY(Error, TEXT("[%s] There is alreay Furniture at this grid position. [Grid Position : %d, %d]")
			, *MS_FUNC_STRING, aFurnitureData.GridPosition.X, aFurnitureData.GridPosition.Y);
		MS_CHECK(false);
	}
	
	GridPositionToMarketFurnitureDatas.Emplace(aFurnitureData.GridPosition, aFurnitureData);
}

void UMS_ItemManager::RemoveFurnitureData(FIntVector2 aGridPosition)
{
	if (!GridPositionToMarketFurnitureDatas.Contains(aGridPosition))
	{
		MS_LOG_VERBOSITY(Error, TEXT("[%s] There isn't Furniture at this grid position. [Grid Position : %d, %d]")
			, *MS_FUNC_STRING, aGridPosition.X, aGridPosition.Y);
		MS_ENSURE(false);
	}
	
	GridPositionToMarketFurnitureDatas.Remove(aGridPosition);
}

void UMS_ItemManager::InitializePlayerDatas()
{
	const TObjectPtr<UWorld> World = GetWorld();
	MS_CHECK(World);

	const TObjectPtr<AMS_PlayerController> PlayerController = World->GetFirstPlayerController<AMS_PlayerController>();
	MS_CHECK(PlayerController);
	
	AMS_PlayerState* PlayerState = PlayerController->GetPlayerState<AMS_PlayerState>();
	MS_CHECK(PlayerState);

	PlayerState->GetAllFurnitureDatas(GridPositionToMarketFurnitureDatas);
	
	PlayerState->GetAllItems(Items);
}

void UMS_ItemManager::SaveFurniturePosition() const
{
	const TObjectPtr<UWorld> World = GetWorld();
	MS_CHECK(World);

	const TObjectPtr<AMS_PlayerController> PlayerController = World->GetFirstPlayerController<AMS_PlayerController>();
	MS_CHECK(PlayerController);
	
	AMS_PlayerState* PlayerState = PlayerController->GetPlayerState<AMS_PlayerState>();
	MS_CHECK(PlayerState);

	PlayerState->SaveFurniturePositionDatas(GridPositionToMarketFurnitureDatas);
}

void UMS_ItemManager::GetStaffProfileElementData(TArray<TObjectPtr<UMS_StaffProfileElementData>>& aProfileDatas) const
{
	aProfileDatas.Empty();
	aProfileDatas = StaffProfileDatas;
}

void UMS_ItemManager::UpdateStaffProperty(TArray<FMS_StaffData>& aStaffDatas)
{
	StaffPropertys.Empty();
	for(const auto& StaffData : aStaffDatas)
	{
		if(UMS_StaffPropertyElementData* StaffProperty = MS_NewObject<UMS_StaffPropertyElementData>())
    	{
    		StaffProperty->SetStaffId(StaffData.StaffId);
			StaffProperty->SetWorkDay(StaffData.WorkDay);
    		StaffProperty->SetHP(100);
    		StaffProperty->SetCondition(100);
    		StaffProperty->SetFeeling(1);
			StaffProperty->SetFirstDateOfWork(StaffData.FirstDateOfWork);
    		StaffProperty->SetExpirationDate(StaffData.ExpirationDate);
    		StaffPropertys.Emplace(StaffData.StaffId, StaffProperty);
    	}	
	}
}

void UMS_ItemManager::GetStaffProperties(TArray<UMS_StaffPropertyElementData*>& aStaffProperties)
{
	aStaffProperties.Empty();
	StaffPropertys.GenerateValueArray(aStaffProperties);
}

UMS_ItemManager* UMS_ItemManager::GetInstance()
{
	return ItemManager;
}
