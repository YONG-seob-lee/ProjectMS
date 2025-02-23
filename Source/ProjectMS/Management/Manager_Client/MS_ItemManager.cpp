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
#include "Units/MS_CustomerAIUnit.h"
#include "Units/MS_FurnitureUnit.h"
#include "Units/MS_StaffAIUnit.h"
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

int32 UMS_ItemManager::GetRemainItemCount(int32 aItemId) const
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

void UMS_ItemManager::GetStaffItems(TMap<int32, int32>& OutItems) const
{
	OutItems.Empty();

	if (const TObjectPtr UnitManager = gUnitMng)
	{
		TArray<TObjectPtr<UMS_UnitBase>> Units;
		UnitManager->GetUnits(EMS_UnitType::StaffAI, Units);

		for (TObjectPtr<UMS_UnitBase> Unit : Units)
		{
			if (const UMS_StaffAIUnit* StaffUnit = Cast<UMS_StaffAIUnit>(Unit.Get()))
			{
				TArray<FMS_SlotData> StaffSlotDatas;
				StaffUnit->GetSlotDatas(StaffSlotDatas);

				for (const FMS_SlotData& SlotData: StaffSlotDatas)
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

int32 UMS_ItemManager::GetStaffItemCount(int32 aItemId) const
{
	TMap<int32, int32> StaffItems;
	GetStaffItems(StaffItems);

	const int32* ItemCount = StaffItems.Find(aItemId);
	if(!ItemCount)
	{
		return 0;
	}
	
	return *ItemCount;
}

void UMS_ItemManager::GetCustomerItems(TMap<int32, int32>& OutItems) const
{
	OutItems.Empty();

	if (const TObjectPtr UnitManager = gUnitMng)
	{
		TArray<TObjectPtr<UMS_UnitBase>> Units;
		UnitManager->GetUnits(EMS_UnitType::CustomerAI, Units);

		for (TObjectPtr<UMS_UnitBase> Unit : Units)
		{
			if (const UMS_CustomerAIUnit* CustomerUnit = Cast<UMS_CustomerAIUnit>(Unit.Get()))
			{
				TArray<FMS_SlotData> CustomerSlotDatas;
				CustomerUnit->GetSlotDatas(CustomerSlotDatas);

				for (const FMS_SlotData& SlotData: CustomerSlotDatas)
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

int32 UMS_ItemManager::GetCustomerItemCount(int32 aItemId) const
{
	TMap<int32, int32> CustomerItems;
	GetStaffItems(CustomerItems);

	const int32* ItemCount = CustomerItems.Find(aItemId);
	if(!ItemCount)
	{
		return 0;
	}
	
	return *ItemCount;
}

void UMS_ItemManager::GetStorageItems(EMS_ZoneType aZoneType, TMap<int32, int32>& OutItems, EMS_TemperatureType aTemperatureType /*= EMS_TemperatureType::Undefined*/) const
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
			if (FurnitureUnit->GetZoneType() != aZoneType)
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

int32 UMS_ItemManager::GetStorageItemCount(EMS_ZoneType aZoneType, int32 aItemId) const
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
				if (FurnitureUnit->GetZoneType() != aZoneType)
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

bool UMS_ItemManager::CanReturnToStorage(int32 aItemId, int32 aReturnCount, EMS_ZoneType aZoneType) const
{
	FMS_ItemData* ItemData = gTableMng.GetTableRowData<FMS_ItemData>(EMS_TableDataType::ItemData, aItemId);
	if (ItemData == nullptr)
	{
		MS_ENSURE(false);
		return false;
	}
	
	int32 EmptyCount = 0;

	if (const TObjectPtr UnitManager = gUnitMng)
	{
		TArray<TObjectPtr<UMS_UnitBase>> Units;
		UnitManager->GetUnits(EMS_UnitType::Furniture, Units);

		for (TObjectPtr<UMS_UnitBase> Unit : Units)
		{
			if (UMS_FurnitureUnit* FurnitureUnit = Cast<UMS_FurnitureUnit>(Unit.Get()))
			{
				if (FurnitureUnit->GetZoneType() != aZoneType)
				{
					continue;
				}
				
				TArray<FMS_SlotData> FurnitureSlotDatas;
				FurnitureUnit->GetSlotDatas(FurnitureSlotDatas);

				for (const FMS_SlotData& SlotData: FurnitureSlotDatas)
				{
					if (SlotData.RequestItemTableId == aItemId)
					{
						if (SlotData.CurrentItemTableId == aItemId)
						{
							EmptyCount = EmptyCount + ItemData->BoxMaxCount - SlotData.CurrentItemCount;
						}

						else if (SlotData.CurrentItemCount == 0)
						{
							EmptyCount = EmptyCount + ItemData->BoxMaxCount;
						}
					}
				}
			}
		}
	}

	return EmptyCount >= aReturnCount;
}

void UMS_ItemManager::GetNotPlacedItems(TMap<int32, int32>& OutItems)
{
	CacheNotPlacedItems.Empty();
	GetRemainItems(CacheNotPlacedItems);

	// Staff
	TMap<int32, int32> StaffItems;
	GetStorageItems(EMS_ZoneType::Display, StaffItems);

	for (const auto& StaffItem : StaffItems)
	{
		int32& Count = CacheNotPlacedItems.FindOrAdd(StaffItem.Key);
		Count -= StaffItem.Value;
	}

	// Customer
	TMap<int32, int32> CustomerItems;
	GetStorageItems(EMS_ZoneType::Display, CustomerItems);

	for (const auto& CustomerItem : CustomerItems)
	{
		int32& Count = CacheNotPlacedItems.FindOrAdd(CustomerItem.Key);
		Count -= CustomerItem.Value;
	}
	
	// Display
	TMap<int32, int32> DisplayItems;
	GetStorageItems(EMS_ZoneType::Display, DisplayItems);

	for (const auto& DisplayItem : DisplayItems)
	{
		int32& Count = CacheNotPlacedItems.FindOrAdd(DisplayItem.Key);
		Count -= DisplayItem.Value;
	}

	// Shelf
	TMap<int32, int32> ShelfItems;
	GetStorageItems(EMS_ZoneType::Shelf, ShelfItems);

	for (const auto& ShelfItem : ShelfItems)
	{
		int32& Count = CacheNotPlacedItems.FindOrAdd(ShelfItem.Key);
		Count -= ShelfItem.Value;
	}

	// Pallet
	TMap<int32, int32> PalletItems;
	GetStorageItems(EMS_ZoneType::Pallet, PalletItems);

	for (const auto& PalletItem : PalletItems)
	{
		int32& Count = CacheNotPlacedItems.FindOrAdd(PalletItem.Key);
		Count -= PalletItem.Value;
	}

	OutItems = CacheNotPlacedItems;
}

int32 UMS_ItemManager::GetNotPlacedItemCount(int32 aItemId) const
{
	return GetRemainItemCount(aItemId) - GetStorageItemCount(EMS_ZoneType::Display, aItemId) - GetStorageItemCount(EMS_ZoneType::Shelf, aItemId) - GetStorageItemCount(EMS_ZoneType::Pallet, aItemId);
}

void UMS_ItemManager::GetCacheNotPlacedItems(TMap<int32, int32>& OutItems) const
{
	OutItems = CacheNotPlacedItems;
}

int32 UMS_ItemManager::GetCacheNotPlacedItemCount(int32 aItemId) const
{
	if (CacheNotPlacedItems.Contains(aItemId))
	{
		return *CacheNotPlacedItems.Find(aItemId);
	}

	return 0;
}

void UMS_ItemManager::UpdateNotPlacedItemsToPalletItems()
{
	TMap<int32, int32> NotPlacedItems = {};
	GetNotPlacedItems(NotPlacedItems);

	if (NotPlacedItems.IsEmpty())
	{
		return;
	}
	
	if (const TObjectPtr UnitManager = gUnitMng)
	{
		TArray<TObjectPtr<UMS_UnitBase>> Units;
		UnitManager->GetUnits(EMS_UnitType::Furniture, Units);

		for (TObjectPtr<UMS_UnitBase> Unit : Units)
		{
			UMS_FurnitureUnit* FurnitureUnit = Cast<UMS_FurnitureUnit>(Unit.Get());
			if (!FurnitureUnit)
			{
				continue;
			}
			
			if (FurnitureUnit->GetZoneType() != EMS_ZoneType::Pallet)
			{
				continue;
			}
				
			TArray<FMS_SlotData> FurnitureSlotDatas;
			FurnitureUnit->GetSlotDatas(FurnitureSlotDatas);

			for (int32 i = 0; i < FurnitureSlotDatas.Num(); ++i)
			{
				if (NotPlacedItems.IsEmpty())
				{
					return;
				}
				
				// 슬롯이 비었을 때
				if (FurnitureSlotDatas[i].CurrentItemTableId == INDEX_NONE || FurnitureSlotDatas[i].CurrentItemTableId == 0)
				{
					FMS_ItemData* NotPlacedItemData = gTableMng.GetTableRowData<FMS_ItemData>(EMS_TableDataType::ItemData, NotPlacedItems.begin().Key());
					if (NotPlacedItemData == nullptr)
					{
						MS_ENSURE(false);
						NotPlacedItems.Remove(NotPlacedItems.begin().Key());
						--i;
						continue;
					}

					if (NotPlacedItems.begin().Value() < NotPlacedItemData->BoxMaxCount)
					{
						FurnitureUnit->AddCurrentItemCount(i, NotPlacedItems.begin().Key(), NotPlacedItems.begin().Value(), false, false);

						NotPlacedItems.Remove(NotPlacedItems.begin().Key());
					}
					else
					{
						FurnitureUnit->AddCurrentItemCount(i, NotPlacedItems.begin().Key(), NotPlacedItemData->BoxMaxCount, false, false);

						NotPlacedItems.begin().Value() -= NotPlacedItemData->BoxMaxCount;
					}
					continue;
				}

				// 슬롯의 아이템이 다 안 찼을때
				FMS_ItemData* PalletSlotItemData = gTableMng.GetTableRowData<FMS_ItemData>(EMS_TableDataType::ItemData, FurnitureSlotDatas[i].CurrentItemTableId);
				if (PalletSlotItemData == nullptr)
				{
					MS_ENSURE(false);
					continue;
				}
				
				if (FurnitureSlotDatas[i].CurrentItemCount < PalletSlotItemData->BoxMaxCount)
				{
					if (!NotPlacedItems.Contains(FurnitureSlotDatas[i].CurrentItemTableId))
					{
						continue;
					}

					int32& NotPlacedItemCount = *NotPlacedItems.Find(FurnitureSlotDatas[i].CurrentItemTableId);

					int32 EmptyCount = PalletSlotItemData->BoxMaxCount - FurnitureSlotDatas[i].CurrentItemCount;

					if (NotPlacedItemCount < EmptyCount)
					{
						FurnitureUnit->AddCurrentItemCount(i, FurnitureSlotDatas[i].CurrentItemTableId, EmptyCount, false, false);

						NotPlacedItems.Remove(FurnitureSlotDatas[i].CurrentItemTableId);
					}
					else
					{
						FurnitureUnit->AddCurrentItemCount(i, FurnitureSlotDatas[i].CurrentItemTableId, NotPlacedItemCount, false, false);

						NotPlacedItemCount -= EmptyCount;
					}
				}
			}
		}
	}

	CacheNotPlacedItems = NotPlacedItems;
}

void UMS_ItemManager::UpdateNotPlacedItemsToPalletItems(TWeakObjectPtr<UMS_FurnitureUnit> aFurnitureUnit)
{
	TMap<int32, int32> NotPlacedItems = {};
	GetNotPlacedItems(NotPlacedItems);

	if (NotPlacedItems.IsEmpty())
	{
		return;
	}
	
	if (aFurnitureUnit->GetZoneType() != EMS_ZoneType::Pallet)
	{
		return;
	}
		
	TArray<FMS_SlotData> FurnitureSlotDatas;
	aFurnitureUnit->GetSlotDatas(FurnitureSlotDatas);

	for (int32 i = 0; i < FurnitureSlotDatas.Num(); ++i)
	{
		if (NotPlacedItems.IsEmpty())
		{
			return;
		}
		
		// 슬롯이 비었을 때
		if (FurnitureSlotDatas[i].CurrentItemTableId == INDEX_NONE || FurnitureSlotDatas[i].CurrentItemTableId == 0)
		{
			FMS_ItemData* NotPlacedItemData = gTableMng.GetTableRowData<FMS_ItemData>(EMS_TableDataType::ItemData, NotPlacedItems.begin().Key());
			if (NotPlacedItemData == nullptr)
			{
				MS_ENSURE(false);
				NotPlacedItems.Remove(NotPlacedItems.begin().Key());
				--i;
				continue;
			}

			if (NotPlacedItems.begin().Value() < NotPlacedItemData->BoxMaxCount)
			{
				aFurnitureUnit->AddCurrentItemCount(i, NotPlacedItems.begin().Key(), NotPlacedItems.begin().Value(), false, false);

				NotPlacedItems.Remove(NotPlacedItems.begin().Key());
			}
			else
			{
				aFurnitureUnit->AddCurrentItemCount(i, NotPlacedItems.begin().Key(), NotPlacedItemData->BoxMaxCount, false, false);

				NotPlacedItems.begin().Value() -= NotPlacedItemData->BoxMaxCount;
			}
			continue;
		}

		// 슬롯의 아이템이 다 안 찼을때
		FMS_ItemData* PalletSlotItemData = gTableMng.GetTableRowData<FMS_ItemData>(EMS_TableDataType::ItemData, FurnitureSlotDatas[i].CurrentItemTableId);
		if (PalletSlotItemData == nullptr)
		{
			MS_ENSURE(false);
			continue;
		}
		
		if (FurnitureSlotDatas[i].CurrentItemCount < PalletSlotItemData->BoxMaxCount)
		{
			if (!NotPlacedItems.Contains(FurnitureSlotDatas[i].CurrentItemTableId))
			{
				continue;
			}

			int32& NotPlacedItemCount = *NotPlacedItems.Find(FurnitureSlotDatas[i].CurrentItemTableId);

			int32 EmptyCount = PalletSlotItemData->BoxMaxCount - FurnitureSlotDatas[i].CurrentItemCount;

			if (NotPlacedItemCount < EmptyCount)
			{
				aFurnitureUnit->AddCurrentItemCount(i, FurnitureSlotDatas[i].CurrentItemTableId, NotPlacedItemCount, false, false);

				NotPlacedItems.Remove(FurnitureSlotDatas[i].CurrentItemTableId);
			}
			else
			{
				aFurnitureUnit->AddCurrentItemCount(i, FurnitureSlotDatas[i].CurrentItemTableId, EmptyCount, false, false);

				NotPlacedItemCount -= EmptyCount;
			}
		}
	}

	CacheNotPlacedItems = NotPlacedItems;
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
