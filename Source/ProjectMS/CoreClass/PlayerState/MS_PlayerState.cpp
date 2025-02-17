// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_PlayerState.h"

#include "MS_Define.h"
#include "Kismet/GameplayStatics.h"
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

void AMS_PlayerState::AddOpenedZoneId(int32 aZoneId)
{
	OpenedZoneIds.AddUnique(aZoneId);
}

void AMS_PlayerState::GetAllMarketFurnitureDatas(
	TMap<FIntVector2, FMS_LevelFurnitureSaveData>& aOutFurnitureDatas) const
{
	aOutFurnitureDatas = GridPositionToMarketFurnitureDatas;
}

bool AMS_PlayerState::GetMarketFurnitureData(const FIntVector2& aInGridPosition, FMS_LevelFurnitureSaveData& aOutFurnitureData) const
{
	if (!GridPositionToMarketFurnitureDatas.Contains(aInGridPosition))
	{
		MS_LOG_VERBOSITY(Error, TEXT("[%s] There isn't Furniture at this grid position. [Grid Position : %d, %d]")
			, *MS_FUNC_STRING, aInGridPosition.X, aInGridPosition.Y);
		MS_ENSURE(false);

		return false;
	}

	aOutFurnitureData = *GridPositionToMarketFurnitureDatas.Find(aInGridPosition);
	return true;
}

void AMS_PlayerState::AddFurnitureData(int32 aFurnitureTableId, const FIntVector2& aGridPosition,
                                   EMS_Rotation aRotation)
{
	if (GridPositionToMarketFurnitureDatas.Contains(aGridPosition))
	{
		MS_LOG_VERBOSITY(Error, TEXT("[%s] There is alreay Furniture at this grid position. [Grid Position : %d, %d]")
			, *MS_FUNC_STRING, aGridPosition.X, aGridPosition.Y);
		MS_CHECK(false);
	}
	
	GridPositionToMarketFurnitureDatas.Emplace(aGridPosition, FMS_LevelFurnitureSaveData(aFurnitureTableId, aGridPosition, aRotation));
}

void AMS_PlayerState::AddFurnitureData(FMS_LevelFurnitureSaveData aFurnitureData)
{
	if (GridPositionToMarketFurnitureDatas.Contains(aFurnitureData.GridPosition))
	{
		MS_LOG_VERBOSITY(Error, TEXT("[%s] There is alreay Furniture at this grid position. [Grid Position : %d, %d]")
			, *MS_FUNC_STRING, aFurnitureData.GridPosition.X, aFurnitureData.GridPosition.Y);
		MS_CHECK(false);
	}
	
	GridPositionToMarketFurnitureDatas.Emplace(aFurnitureData.GridPosition, aFurnitureData);
}

void AMS_PlayerState::RemoveFurnitureData(FIntVector2 aGridPosition)
{
	if (!GridPositionToMarketFurnitureDatas.Contains(aGridPosition))
	{
		MS_LOG_VERBOSITY(Error, TEXT("[%s] There isn't Furniture at this grid position. [Grid Position : %d, %d]")
			, *MS_FUNC_STRING, aGridPosition.X, aGridPosition.Y);
		MS_ENSURE(false);
	}
	
	GridPositionToMarketFurnitureDatas.Remove(aGridPosition);
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
	
	FMS_LevelFurnitureSaveData& FurnitureData = *GridPositionToMarketFurnitureDatas.Find(aGridPosition);
	FurnitureData.SlotDatas = aSlotData;
}

int32 AMS_PlayerState::GetItemCount(int32 aItemId) const
{
	if (!Items.Contains(aItemId))
	{
		return 0;
	}

	return *Items.Find(aItemId);
}

void AMS_PlayerState::InitDefaultPlayerData()
{
	// GameData
	GameDate = FMS_GameDate(1, 1, 1, EMS_DailyTimeZone::Morning);
	
	// OpenedZoneIds
	OpenedZoneIds.AddUnique(1);
	OpenedZoneIds.AddUnique(10);

	//Furniture
	FMS_LevelFurnitureSaveData Counter = FMS_LevelFurnitureSaveData(1, FIntVector2(13, 15), EMS_Rotation::Rot270);
	GridPositionToMarketFurnitureDatas.Emplace(Counter.GridPosition, Counter);

	FMS_LevelFurnitureSaveData RoomTemperature1 = FMS_LevelFurnitureSaveData(7, FIntVector2(7, 4), EMS_Rotation::Rot0);
	GridPositionToMarketFurnitureDatas.Emplace(RoomTemperature1.GridPosition, RoomTemperature1);

	FMS_LevelFurnitureSaveData RoomTemperature2 = FMS_LevelFurnitureSaveData(7, FIntVector2(9, 4), EMS_Rotation::Rot0);
	GridPositionToMarketFurnitureDatas.Emplace(RoomTemperature2.GridPosition, RoomTemperature2);

	FMS_LevelFurnitureSaveData VeggieStand = FMS_LevelFurnitureSaveData(8, FIntVector2(13, 4), EMS_Rotation::Rot0);
	GridPositionToMarketFurnitureDatas.Emplace(VeggieStand.GridPosition, VeggieStand);

	FMS_LevelFurnitureSaveData Rack = FMS_LevelFurnitureSaveData(11, FIntVector2(-3, 13), EMS_Rotation::Rot0);
	GridPositionToMarketFurnitureDatas.Emplace(Rack.GridPosition, Rack);

	FMS_LevelFurnitureSaveData Wardrobe = FMS_LevelFurnitureSaveData(12, FIntVector2(-10, 11), EMS_Rotation::Rot270);
	GridPositionToMarketFurnitureDatas.Emplace(Wardrobe.GridPosition, Wardrobe);
	
	// Items
	Items.Emplace(4, 30);
	Items.Emplace(5, 30);
	Items.Emplace(16, 20);
	Items.Emplace(17, 10);

	// Staff
	StaffDatas.Emplace(FMS_StaffData(1));
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
	for (const FMS_LevelFurnitureSaveData MarketFurnitureData : TestDB->MarketFurnitureDatas)
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

	StaffDatas = TestDB->StaffDatas;

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

	NewTestDBData->Items = Items;

	NewTestDBData->StaffDatas = StaffDatas;
	
	if (!UGameplayStatics::SaveGameToSlot(NewTestDBData, SaveSlotName, 0))
	{
		MS_LOG_VERBOSITY(Error, TEXT("SaveGameError"));
		MS_ENSURE(false);
	}
}
