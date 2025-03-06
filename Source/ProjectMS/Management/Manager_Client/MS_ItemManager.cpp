// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ItemManager.h"

#include "MS_ModeManager.h"
#include "MS_SceneManager.h"
#include "MS_ScheduleManager.h"
#include "Controller/MS_PlayerController.h"
#include "Manager_Both/MS_UnitManager.h"
#include "PlayerState/MS_PlayerState.h"
#include "Table/Caches/MS_FurnitureCacheTable.h"
#include "Table/Caches/MS_ItemCacheTable.h"
#include "Table/Caches/MS_StaffCacheTable.h"
#include "Units/MS_CustomerAIUnit.h"
#include "Units/MS_StorageUnit.h"
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

void UMS_ItemManager::InitSettleMoney()
{
	const TObjectPtr<UWorld> World = GetWorld();
	MS_CHECK(World);

	const TObjectPtr<AMS_PlayerController> PlayerController = World->GetFirstPlayerController<AMS_PlayerController>();
	MS_CHECK(PlayerController);

	const AMS_PlayerState* PlayerState = PlayerController->GetPlayerState<AMS_PlayerState>();
	MS_CHECK(PlayerState);

	// OrderItem
	const TObjectPtr<UMS_ItemCacheTable> ItemTable = Cast<UMS_ItemCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::ItemData));
	MS_ENSURE(ItemTable);
	const int32 TotalOrderItemPrice = (-1) * ItemTable->GetTotalItemPrice(OrderItems);
	int32& OrderItemMoney = DailySettleDetail.FindOrAdd(EMS_SettlementMoneyType::OrderItem);
	OrderItemMoney = TotalOrderItemPrice;
	
	// OrderFurniture
	const TObjectPtr<UMS_FurnitureCacheTable> FurnitureTable = Cast<UMS_FurnitureCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::Furniture));
	MS_ENSURE(FurnitureTable);
	const int32 TotalOrderFurniturePrice = (-1) * FurnitureTable->GetTotalFurniturePrice(OrderFurnitures);
	int32& OrderFurnitureMoney = DailySettleDetail.FindOrAdd(EMS_SettlementMoneyType::OrderFurniture);
	OrderFurnitureMoney = TotalOrderFurniturePrice;
	
	// ElectricityBill
	int32& ElectricityBill = DailySettleDetail.FindOrAdd(EMS_SettlementMoneyType::ElectricityBill);
	ElectricityBill = (-1) * PlayerState->GetOpenedZoneCount() * 10;

	// PersonalExpanses
	int32& PersonalExpanses = DailySettleDetail.FindOrAdd(EMS_SettlementMoneyType::PersonalExpanses);
	for(const auto& StaffProperty :StaffPropertys)
	{
		PersonalExpanses -= StaffProperty.Value->GetDailySalary();
	}

	// LoanInterest 나중에 계획
}

void UMS_ItemManager::EndSettleMoney()
{
	const TObjectPtr<UWorld> World = GetWorld();
	MS_CHECK(World);

	const TObjectPtr<AMS_PlayerController> PlayerController = World->GetFirstPlayerController<AMS_PlayerController>();
	MS_CHECK(PlayerController);
	
	AMS_PlayerState* PlayerState = PlayerController->GetPlayerState<AMS_PlayerState>();
	MS_CHECK(PlayerState);

	int32 TotalEarnMoney = 0;
	for(const auto& elem : DailySettleDetail)
	{
		TotalEarnMoney +=elem.Value;
	}
	PlayerState->SettleMoney(TotalEarnMoney);

	for(auto& Elem : DailySettleDetail)
	{
		Elem.Value = 0;
	}
}

void UMS_ItemManager::EarnMoney(const TMap<int32, int32>& SellItems)
{
	const TObjectPtr<UMS_ItemCacheTable> ItemTable = Cast<UMS_ItemCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::ItemData));
	MS_ENSURE(ItemTable);
	const int32 TotalPrice = ItemTable->GetTotalItemPrice(SellItems);
	int32& EarnMoney = DailySettleDetail.FindOrAdd(EMS_SettlementMoneyType::EarnMoney);
	EarnMoney += TotalPrice;
}

int32 UMS_ItemManager::GetTotalGoldMoney()
{
	const int32* EarnMoney = DailySettleDetail.Find(EMS_SettlementMoneyType::EarnMoney);
	if(!EarnMoney)
	{
		return 0;
	}
	
	const int32* GoldMoney = Moneys.Find(static_cast<int32>(EMS_MoneyType::Gold));
	if(!GoldMoney)
	{
		return *EarnMoney;
	}

	return *EarnMoney + *GoldMoney;
}

bool UMS_ItemManager::IsHaveEnoughMoney(const TMap<int32, int32>& aOrderItems, bool bItemTypeIsFurniture /* = false */, EMS_MoneyType aMoneyType /* = EMS_MoneyType::Gold */)
{
	const int32* GoldMoney = Moneys.Find(static_cast<int32>(aMoneyType));
	if(!GoldMoney)
	{
		return false;
	}

	int32 TotalPrice = 0;
	if(bItemTypeIsFurniture == false)
	{
		const TObjectPtr<UMS_ItemCacheTable> ItemTable = Cast<UMS_ItemCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::ItemData));
		MS_ENSURE(ItemTable);
		TotalPrice = ItemTable->GetTotalItemPrice(aOrderItems);
	}
	else
	{
		const TObjectPtr<UMS_FurnitureCacheTable> FurnitureTable = Cast<UMS_FurnitureCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::Furniture));
		MS_ENSURE(FurnitureTable);
		TotalPrice = FurnitureTable->GetTotalFurniturePrice(aOrderItems);
	}

	return *GoldMoney >= TotalPrice;
}

void UMS_ItemManager::GetDeployableItems(TMap<int32, int32>& OutItems, EMS_TemperatureType aTemperatureType) const
{
	TMap<int32, int32> TestItems = Items;

	for (const auto& OrderItem : OrderItems)
	{
		int32& Count = OutItems.FindOrAdd(OrderItem.Key);
		Count += OrderItem.Value;
	}

	for (const auto& TestItem : TestItems)
	{
		if(aTemperatureType != EMS_TemperatureType::Undefined)
		{
			TObjectPtr<UMS_ItemCacheTable> ItemTable = Cast<UMS_ItemCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::ItemData));
			MS_ENSURE(ItemTable);
					
			if(ItemTable->GetItemTemperature(TestItem.Key) != aTemperatureType)
			{
				continue;
			}	
		}

		OutItems.Emplace(TestItem.Key, TestItem.Value);
	}
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
		UnitManager->GetUnits(EMS_UnitType::Storage, Units);

		for (TObjectPtr<UMS_UnitBase> Unit : Units)
		{
			const UMS_StorageUnit* StorageUnit = Cast<UMS_StorageUnit>(Unit.Get());
			if (!StorageUnit)
			{
				continue;
			}
			if (StorageUnit->GetZoneType() != aZoneType)
			{
				continue;
			}
				
			TArray<FMS_SlotData> StorageSlotDatas;
			StorageUnit->GetSlotDatas(StorageSlotDatas);

			for (const FMS_SlotData& SlotData: StorageSlotDatas)
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
		UnitManager->GetUnits(EMS_UnitType::Storage, Units);

		for (TObjectPtr<UMS_UnitBase> Unit : Units)
		{
			if (UMS_StorageUnit* StorageUnit = Cast<UMS_StorageUnit>(Unit.Get()))
			{
				if (StorageUnit->GetZoneType() != aZoneType)
				{
					continue;
				}
				
				TArray<FMS_SlotData> StorageSlotDatas;
				StorageUnit->GetSlotDatas(StorageSlotDatas);

				for (const FMS_SlotData& SlotData: StorageSlotDatas)
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

bool UMS_ItemManager::CanDeliveryToStorage(int32 aItemId, int32 aDeliveryCount, EMS_ZoneType aZoneType, TArray<TWeakObjectPtr<class UMS_StorageUnit>>& aOutDeliveryTargetStrage) const
{
	aOutDeliveryTargetStrage.Empty();
	
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
		UnitManager->GetUnits(EMS_UnitType::Storage, Units);

		for (TObjectPtr<UMS_UnitBase> Unit : Units)
		{
			if (UMS_StorageUnit* StorageUnit = Cast<UMS_StorageUnit>(Unit.Get()))
			{
				if (StorageUnit->GetZoneType() != aZoneType)
				{
					continue;
				}
				
				TArray<FMS_SlotData> StorageSlotDatas;
				StorageUnit->GetSlotDatas(StorageSlotDatas);

				if (aZoneType == EMS_ZoneType::Pallet)
				{
					for (const FMS_SlotData& SlotData: StorageSlotDatas)
					{
						if (SlotData.CurrentItemTableId == aItemId)
						{
							EmptyCount = EmptyCount + ItemData->BoxMaxCount - SlotData.CurrentItemCount;
							aOutDeliveryTargetStrage.AddUnique(StorageUnit);
						}
						
						else if (SlotData.CurrentItemCount == 0)
						{
							EmptyCount = EmptyCount + ItemData->BoxMaxCount;
							aOutDeliveryTargetStrage.AddUnique(StorageUnit);
						}
					}
				}
				else
				{
					for (const FMS_SlotData& SlotData: StorageSlotDatas)
					{
						if (SlotData.RequestItemTableId == aItemId)
						{
							if (SlotData.CurrentItemTableId == aItemId)
							{
								EmptyCount = EmptyCount + ItemData->BoxMaxCount - SlotData.CurrentItemCount;
								aOutDeliveryTargetStrage.AddUnique(StorageUnit);
							}

							else if (SlotData.CurrentItemCount == 0)
							{
								EmptyCount = EmptyCount + ItemData->BoxMaxCount;
								aOutDeliveryTargetStrage.AddUnique(StorageUnit);
							}
						}
					}
				}
			}
		}
	}

	return EmptyCount >= aDeliveryCount;
}

bool UMS_ItemManager::CanPickUpFromStorage(int32 aItemId, EMS_ZoneType aZoneType,
	TArray<TWeakObjectPtr<UMS_StorageUnit>>& aOutPickUpTargetStorages) const
{
	aOutPickUpTargetStorages.Empty();
	
	FMS_ItemData* ItemData = gTableMng.GetTableRowData<FMS_ItemData>(EMS_TableDataType::ItemData, aItemId);
	if (ItemData == nullptr)
	{
		MS_ENSURE(false);
		return false;
	}

	if (const TObjectPtr UnitManager = gUnitMng)
	{
		TArray<TObjectPtr<UMS_UnitBase>> Units;
		UnitManager->GetUnits(EMS_UnitType::Storage, Units);

		for (TObjectPtr<UMS_UnitBase> Unit : Units)
		{
			if (UMS_StorageUnit* StorageUnit = Cast<UMS_StorageUnit>(Unit.Get()))
			{
				if (StorageUnit->GetZoneType() != aZoneType)
				{
					continue;
				}
				
				TArray<FMS_SlotData> StorageSlotDatas;
				StorageUnit->GetSlotDatas(StorageSlotDatas);

				for (const FMS_SlotData& SlotData: StorageSlotDatas)
				{
					if (SlotData.CurrentItemTableId == aItemId && SlotData.CurrentItemCount != 0)
					{
						aOutPickUpTargetStorages.AddUnique(StorageUnit);
					}
				}
			}
		}
	}

	return !aOutPickUpTargetStorages.IsEmpty();
}

void UMS_ItemManager::GetNotPlacedItems(TMap<int32, int32>& OutItems)
{
	CacheNotPlacedItems.Empty();
	GetRemainItems(CacheNotPlacedItems);

	// Staff
	TMap<int32, int32> StaffItems;
	GetStaffItems(StaffItems);

	for (const auto& StaffItem : StaffItems)
	{
		int32& Count = CacheNotPlacedItems.FindOrAdd(StaffItem.Key);
		Count -= StaffItem.Value;
	}

	// Customer
	TMap<int32, int32> CustomerItems;
	GetCustomerItems(CustomerItems);

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
		UnitManager->GetUnits(EMS_UnitType::Storage, Units);

		for (TObjectPtr<UMS_UnitBase> Unit : Units)
		{
			UMS_StorageUnit* StorageUnit = Cast<UMS_StorageUnit>(Unit.Get());
			if (!StorageUnit)
			{
				continue;
			}
			
			if (StorageUnit->GetZoneType() != EMS_ZoneType::Pallet)
			{
				continue;
			}
				
			TArray<FMS_SlotData> StorageSlotDatas;
			StorageUnit->GetSlotDatas(StorageSlotDatas);

			for (int32 i = 0; i < StorageSlotDatas.Num(); ++i)
			{
				if (NotPlacedItems.IsEmpty())
				{
					return;
				}
				
				// 슬롯이 비었을 때
				if (StorageSlotDatas[i].CurrentItemTableId == INDEX_NONE || StorageSlotDatas[i].CurrentItemTableId == 0)
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
						StorageUnit->AddCurrentItemCount(i, NotPlacedItems.begin().Key(), NotPlacedItems.begin().Value());

						NotPlacedItems.Remove(NotPlacedItems.begin().Key());
					}
					else
					{
						StorageUnit->AddCurrentItemCount(i, NotPlacedItems.begin().Key(), NotPlacedItemData->BoxMaxCount);

						NotPlacedItems.begin().Value() -= NotPlacedItemData->BoxMaxCount;
					}
					continue;
				}

				// 슬롯의 아이템이 다 안 찼을때
				FMS_ItemData* PalletSlotItemData = gTableMng.GetTableRowData<FMS_ItemData>(EMS_TableDataType::ItemData, StorageSlotDatas[i].CurrentItemTableId);
				if (PalletSlotItemData == nullptr)
				{
					MS_ENSURE(false);
					continue;
				}
				
				if (StorageSlotDatas[i].CurrentItemCount < PalletSlotItemData->BoxMaxCount)
				{
					if (!NotPlacedItems.Contains(StorageSlotDatas[i].CurrentItemTableId))
					{
						continue;
					}

					int32& NotPlacedItemCount = *NotPlacedItems.Find(StorageSlotDatas[i].CurrentItemTableId);

					int32 EmptyCount = PalletSlotItemData->BoxMaxCount - StorageSlotDatas[i].CurrentItemCount;

					if (NotPlacedItemCount < EmptyCount)
					{
						StorageUnit->AddCurrentItemCount(i, StorageSlotDatas[i].CurrentItemTableId, NotPlacedItemCount);

						NotPlacedItems.Remove(StorageSlotDatas[i].CurrentItemTableId);
					}
					else
					{
						StorageUnit->AddCurrentItemCount(i, StorageSlotDatas[i].CurrentItemTableId, EmptyCount);

						NotPlacedItemCount -= EmptyCount;
					}
				}
			}
		}
	}

	CacheNotPlacedItems = NotPlacedItems;
}

void UMS_ItemManager::UpdateNotPlacedItemsToPalletItems(TWeakObjectPtr<UMS_StorageUnit> aStorageUnit)
{
	TMap<int32, int32> NotPlacedItems = {};
	GetNotPlacedItems(NotPlacedItems);

	if (NotPlacedItems.IsEmpty())
	{
		return;
	}
	
	if (aStorageUnit->GetZoneType() != EMS_ZoneType::Pallet)
	{
		return;
	}
		
	TArray<FMS_SlotData> StorageSlotDatas;
	aStorageUnit->GetSlotDatas(StorageSlotDatas);

	for (int32 i = 0; i < StorageSlotDatas.Num(); ++i)
	{
		if (NotPlacedItems.IsEmpty())
		{
			return;
		}
		
		// 슬롯이 비었을 때
		if (StorageSlotDatas[i].CurrentItemTableId == INDEX_NONE || StorageSlotDatas[i].CurrentItemTableId == 0)
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
				aStorageUnit->AddCurrentItemCount(i, NotPlacedItems.begin().Key(), NotPlacedItems.begin().Value());

				NotPlacedItems.Remove(NotPlacedItems.begin().Key());
			}
			else
			{
				aStorageUnit->AddCurrentItemCount(i, NotPlacedItems.begin().Key(), NotPlacedItemData->BoxMaxCount);

				NotPlacedItems.begin().Value() -= NotPlacedItemData->BoxMaxCount;
			}
			continue;
		}

		// 슬롯의 아이템이 다 안 찼을때
		FMS_ItemData* PalletSlotItemData = gTableMng.GetTableRowData<FMS_ItemData>(EMS_TableDataType::ItemData, StorageSlotDatas[i].CurrentItemTableId);
		if (PalletSlotItemData == nullptr)
		{
			MS_ENSURE(false);
			continue;
		}
		
		if (StorageSlotDatas[i].CurrentItemCount < PalletSlotItemData->BoxMaxCount)
		{
			if (!NotPlacedItems.Contains(StorageSlotDatas[i].CurrentItemTableId))
			{
				continue;
			}

			int32& NotPlacedItemCount = *NotPlacedItems.Find(StorageSlotDatas[i].CurrentItemTableId);

			int32 EmptyCount = PalletSlotItemData->BoxMaxCount - StorageSlotDatas[i].CurrentItemCount;

			if (NotPlacedItemCount < EmptyCount)
			{
				aStorageUnit->AddCurrentItemCount(i, StorageSlotDatas[i].CurrentItemTableId, NotPlacedItemCount);

				NotPlacedItems.Remove(StorageSlotDatas[i].CurrentItemTableId);
			}
			else
			{
				aStorageUnit->AddCurrentItemCount(i, StorageSlotDatas[i].CurrentItemTableId, EmptyCount);

				NotPlacedItemCount -= EmptyCount;
			}
		}
	}

	CacheNotPlacedItems = NotPlacedItems;
}

void UMS_ItemManager::PurchaseItems(const TMap<int32, int32>& aSoldItems)
{
	for(const auto& aSoldItem : aSoldItems)
	{
		int32& SoldItemCount = SoldItems.FindOrAdd(aSoldItem.Key);
		SoldItemCount += aSoldItem.Value;
	}
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

void UMS_ItemManager::GetOrderFurnitures(TMap<int32, int32> aOrderFurniture)
{
	const TObjectPtr<UWorld> World = GetWorld();
	MS_CHECK(World);

	const TObjectPtr<AMS_PlayerController> PlayerController = World->GetFirstPlayerController<AMS_PlayerController>();
	MS_CHECK(PlayerController);
	
	AMS_PlayerState* PlayerState = PlayerController->GetPlayerState<AMS_PlayerState>();
	MS_CHECK(PlayerState);

	PlayerState->GetOrderFurnitures(aOrderFurniture);
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

void UMS_ItemManager::UpdateStaffProperty(TArray<FMS_PlayerStaffData>& aStaffDatas)
{
	StaffPropertys.Empty();
	for(const auto& StaffData : aStaffDatas)
	{
		if(UMS_StaffPropertyElementData* StaffProperty = MS_NewObject<UMS_StaffPropertyElementData>())
    	{
    		StaffProperty->SetStaffId(StaffData.StaffId);
    		StaffProperty->SetStaffIdTag(StaffData.StaffIdTag);
    		StaffProperty->SetStaffUIPriorityType(StaffData.StaffUIPriorityType);
			StaffProperty->SetWorkDay(StaffData.WorkDay);
    		StaffProperty->SetHP(100);
    		StaffProperty->SetCondition(100);
    		StaffProperty->SetFeeling(1);
			StaffProperty->SetDailySalary(StaffData.DailyPrice);
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

void UMS_ItemManager::UpdateStaffPriorityOfWorks(int32 aStaffId, int32 aStaffIdTag, EMS_StaffUIPriorityType aStaffUIPriorityType)
{
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
	
	TArray<EMS_StaffIssueType> PriorityOfWorks;
	
	switch (aStaffUIPriorityType)
	{
	case EMS_StaffUIPriorityType::PaymentFirst :
		{
			PriorityOfWorks = {EMS_StaffIssueType::Payment,
				EMS_StaffIssueType::ReturnItemsFromDisplay, EMS_StaffIssueType::AddItemsToDisplay,
				EMS_StaffIssueType::ReturnItemsFromShelf, EMS_StaffIssueType::AddItemsToShelf};
			break;
		}

	case EMS_StaffUIPriorityType::DisplayFirst :
		{
			PriorityOfWorks = {EMS_StaffIssueType::ReturnItemsFromDisplay, EMS_StaffIssueType::AddItemsToDisplay,
				EMS_StaffIssueType::Payment,
				EMS_StaffIssueType::ReturnItemsFromShelf, EMS_StaffIssueType::AddItemsToShelf};
			break;
		}
		
	case EMS_StaffUIPriorityType::ShelfFirst :
		{
			PriorityOfWorks = {EMS_StaffIssueType::ReturnItemsFromShelf, EMS_StaffIssueType::AddItemsToShelf,
				EMS_StaffIssueType::Payment,
				EMS_StaffIssueType::ReturnItemsFromDisplay, EMS_StaffIssueType::AddItemsToDisplay};
			break;
		}

	case EMS_StaffUIPriorityType::PaymentOnly :
		{
			PriorityOfWorks = {EMS_StaffIssueType::Payment};
			break;
		}

	case EMS_StaffUIPriorityType::DisplayOnly :
		{
			PriorityOfWorks = {EMS_StaffIssueType::ReturnItemsFromDisplay, EMS_StaffIssueType::AddItemsToDisplay};
			break;
		}

	case EMS_StaffUIPriorityType::ShelfOnly :
		{
			PriorityOfWorks = {EMS_StaffIssueType::ReturnItemsFromShelf, EMS_StaffIssueType::AddItemsToShelf};
			break;
		}

	default:
		{
			PriorityOfWorks = {EMS_StaffIssueType::Payment,
				EMS_StaffIssueType::ReturnItemsFromDisplay, EMS_StaffIssueType::AddItemsToDisplay,
				EMS_StaffIssueType::ReturnItemsFromShelf, EMS_StaffIssueType::AddItemsToShelf};
			break;
		}
	}
	
	// Write To Player Data
	PlayerState->RegisterStaffPriorityOfWorks(aStaffId, aStaffIdTag, PriorityOfWorks, aStaffUIPriorityType);
	PlayerState->SavePlayerData();
}

UMS_ItemManager* UMS_ItemManager::GetInstance()
{
	return ItemManager;
}
