// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_PlayerState.h"

#include "MS_Define.h"
#include "Kismet/GameplayStatics.h"
#include "Manager_Client/MS_ItemManager.h"
#include "Table/Caches/MS_StaffCacheTable.h"
#include "Test/TestServer/MS_TestDB.h"


AMS_PlayerState::AMS_PlayerState()
{
	SaveSlotName = FString("TestDB");
}

void AMS_PlayerState::PreInitializeComponents()
{
	InitPlayerData();
	
	Super::PreInitializeComponents();
}

const TArray<int32>& AMS_PlayerState::GetOpenedZoneIds()
{
	return OpenedZoneIds;
}

int32 AMS_PlayerState::GetOpenedZoneCount() const
{
	return OpenedZoneIds.Num();
}

void AMS_PlayerState::AddOpenedZoneId(int32 aZoneId)
{
	OpenedZoneIds.AddUnique(aZoneId);
}

void AMS_PlayerState::OrderItem(TMap<int32, int32>& aOrderItems)
{
	for(const auto& OrderItem : aOrderItems)
	{
		int32& OrderItemCount = OrderItems.FindOrAdd(OrderItem.Key);
		OrderItemCount += OrderItem.Value;
	}

	SavePlayerData();
	gItemMng.UpdateOrderItems(OrderItems);
}

void AMS_PlayerState::OrganizeItems()
{
	for(const auto& OrderItem : OrderItems)
	{
		int32& Item = Items.FindOrAdd(OrderItem.Key);
		Item += OrderItem.Value;
	}
	OrderItems.Empty();
	
	SavePlayerData();
	gItemMng.UpdateItems(Items);
	gItemMng.UpdateOrderItems(OrderItems);
}

void AMS_PlayerState::OrderFurniture(const TMap<int32, int32>& aOrderFurnitures)
{
	for(const auto& OrderFurniture : aOrderFurnitures)
	{
		int32& OrderCount = OrderFurnitures.FindOrAdd(OrderFurniture.Key);
		OrderCount += OrderFurniture.Value;
	}
	SavePlayerData();
}

void AMS_PlayerState::OrganizeFurniture()
{
	for(const auto& OrderFurniture : OrderFurnitures)
	{
		int32& FurnitureCount = Furnitures.FindOrAdd(OrderFurniture.Key);
		FurnitureCount += OrderFurniture.Value;
	}
	
	OrderFurnitures.Empty();
	gItemMng.UpdateOrderFurnitures(OrderFurnitures);
	gItemMng.UpdateFurnitures(Furnitures);
}

void AMS_PlayerState::SetFurnitureSlotDatas(const FIntVector2& aGridPosition, const TArray<FMS_SlotData>& aSlotData)
{
	// ToDo: 슬롯정보가 무결한지 체크
	if (!GridPositionToMarketFurnitureDatas.Contains(aGridPosition))
	{
		MS_LOG_VERBOSITY(Error, TEXT("[%s] There isn't Furniture at this grid position. [Grid Position : %d, %d]")
			, *MS_FUNC_STRING, aGridPosition.X, aGridPosition.Y);
		MS_ENSURE(false);
	}
	
	FMS_FurniturePositionData& FurnitureData = *GridPositionToMarketFurnitureDatas.Find(aGridPosition);
	FurnitureData.SlotDatas = aSlotData;
}

void AMS_PlayerState::SaveFurniturePositionDatas(TMap<FIntVector2, FMS_FurniturePositionData> aGridPositionToMarketFurnitureDatas)
{
	GridPositionToMarketFurnitureDatas = aGridPositionToMarketFurnitureDatas;
	SavePlayerData();
}

void AMS_PlayerState::RegisterStaff(int32 StaffId, int32 WorkDay)
{
	// Save ( 직원은 다음날 출근하기에 + 1일 )
	FMS_GameDate FirstDateOfWork = GameDate;
	FirstDateOfWork.Day += 1;
	StaffDatas.Emplace(FMS_PlayerStaffData(StaffId, FirstDateOfWork, WorkDay));
	SavePlayerData();
	
	// 아이템으로 재등록
	gItemMng.UpdateStaffProperty(StaffDatas);
}

void AMS_PlayerState::InitDefaultPlayerData()
{
	// GameData
	GameDate = FMS_GameDate(1, 1, 1, EMS_DailyTimeZone::Morning);
	
	// OpenedZoneIds
	OpenedZoneIds.AddUnique(1);
	OpenedZoneIds.AddUnique(10);

	//Furniture
	FMS_FurniturePositionData Counter = FMS_FurniturePositionData(1, FIntVector2(13, 10), EMS_Rotation::Rot270);
	GridPositionToMarketFurnitureDatas.Emplace(Counter.GridPosition, Counter);

	FMS_FurniturePositionData RoomTemperature1 = FMS_FurniturePositionData(7, FIntVector2(7, 2), EMS_Rotation::Rot0);
	GridPositionToMarketFurnitureDatas.Emplace(RoomTemperature1.GridPosition, RoomTemperature1);

	FMS_FurniturePositionData RoomTemperature2 = FMS_FurniturePositionData(7, FIntVector2(9, 2), EMS_Rotation::Rot0);
	GridPositionToMarketFurnitureDatas.Emplace(RoomTemperature2.GridPosition, RoomTemperature2);

	FMS_FurniturePositionData VeggieStand = FMS_FurniturePositionData(8, FIntVector2(13, 2), EMS_Rotation::Rot0);
	GridPositionToMarketFurnitureDatas.Emplace(VeggieStand.GridPosition, VeggieStand);

	FMS_FurniturePositionData Rack = FMS_FurniturePositionData(11, FIntVector2(-3, 13), EMS_Rotation::Rot0);
	GridPositionToMarketFurnitureDatas.Emplace(Rack.GridPosition, Rack);
	
	FMS_FurniturePositionData Pallet = FMS_FurniturePositionData(10, FIntVector2(-4, 27), EMS_Rotation::Rot180);
	GridPositionToMarketFurnitureDatas.Emplace(Pallet.GridPosition, Pallet);
	
	// Items
	Items.Emplace(4, 30);
	Items.Emplace(5, 30);
	Items.Emplace(16, 20);
	Items.Emplace(17, 10);

	// Staff
	StaffDatas.Emplace(FMS_PlayerStaffData(1, FMS_GameDate(1, 1, 1)));
}

void AMS_PlayerState::InitPlayerData()
{
	UMS_TestDB* TestDB = Cast<UMS_TestDB>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));
	if (TestDB == nullptr)
	{
		TestDB = GetMutableDefault<UMS_TestDB>();
	}

	bInitDefaultData = TestDB->bInitDefaultData;

	GameDate = TestDB->GameDate;
	
	OpenedZoneIds = TestDB->OpenedZoneIds;

	GridPositionToMarketFurnitureDatas.Empty();
	for (const auto& MarketFurnitureData : TestDB->MarketFurnitureDatas)
	{
		if (GridPositionToMarketFurnitureDatas.Contains(MarketFurnitureData.GridPosition))
		{
			MS_LOG_VERBOSITY(Error, TEXT("[%s] There is alreay Furniture at this grid position. [Grid Position : %d, %d]")
				, *MS_FUNC_STRING, MarketFurnitureData.GridPosition.X, MarketFurnitureData.GridPosition.Y);
			MS_CHECK(false);
		}
		
		GridPositionToMarketFurnitureDatas.Emplace(MarketFurnitureData.GridPosition, MarketFurnitureData);
	}
	
	Items = TestDB->Items;
	OrderItems = TestDB->OrderItems;
	gItemMng.UpdateItems(Items);
	gItemMng.UpdateOrderItems(OrderItems);

	Furnitures = TestDB->Furnitures;
	OrderFurnitures = TestDB->OrderFurnitures;
	gItemMng.UpdateFurnitures(Furnitures);
	gItemMng.UpdateOrderFurnitures(OrderFurnitures);
	
	StaffDatas = TestDB->StaffDatas;
	gItemMng.UpdateStaffProperty(StaffDatas);

	if (!bInitDefaultData)
	{
		bInitDefaultData = true;
		InitDefaultPlayerData();
		SavePlayerData();
	}
}

void AMS_PlayerState::SavePlayerData()
{
	UMS_TestDB* NewTestDBData = NewObject<UMS_TestDB>();
	
	NewTestDBData->bInitDefaultData = bInitDefaultData;

	FMS_GameDate SaveGameDate = GameDate;
	if (GameDate.DailyTimeZone == EMS_DailyTimeZone::DayTimeWork)
	{
		SaveGameDate.DailyTimeZone = EMS_DailyTimeZone::Morning;
	}
	else if (GameDate.DailyTimeZone == EMS_DailyTimeZone::EveningWork)
	{
		SaveGameDate.DailyTimeZone = EMS_DailyTimeZone::Evening;
	}
	NewTestDBData->GameDate = SaveGameDate;

	NewTestDBData->OpenedZoneIds = OpenedZoneIds;
	
	for (auto MarketFurnitureData : GridPositionToMarketFurnitureDatas)
	{
		NewTestDBData->MarketFurnitureDatas.Emplace(MarketFurnitureData.Value);
	}
	
	NewTestDBData->OrderItems = OrderItems;
	NewTestDBData->Items = Items;

	NewTestDBData->OrderFurnitures = OrderFurnitures;
	NewTestDBData->Furnitures = Furnitures;
	
	NewTestDBData->StaffDatas = StaffDatas;
	
	if (!UGameplayStatics::SaveGameToSlot(NewTestDBData, SaveSlotName, 0))
	{
		MS_LOG_VERBOSITY(Error, TEXT("SaveGameError"));
		MS_ENSURE(false);
	}
}
