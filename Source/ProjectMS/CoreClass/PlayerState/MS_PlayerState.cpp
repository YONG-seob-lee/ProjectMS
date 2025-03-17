// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_PlayerState.h"

#include "MS_Define.h"
#include "Kismet/GameplayStatics.h"
#include "Manager_Client/MS_ItemManager.h"
#include "Manager_Client/MS_ScheduleManager.h"
#include "Table/Caches/MS_FurnitureCacheTable.h"
#include "Table/Caches/MS_ItemCacheTable.h"
#include "Test/PlayerData/MS_PlayerData.h"


AMS_PlayerState::AMS_PlayerState()
{
	SaveSlotName = FString("MS_PlayerData");
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

void AMS_PlayerState::SettleMoney(int32 aEarnMoney)
{
	int32& GoldMoney = Money.FindOrAdd(static_cast<int32>(EMS_MoneyType::Gold));
	GoldMoney += aEarnMoney;
	
	SavePlayerData();
	gItemMng.UpdateMoney(Money);
}

void AMS_PlayerState::OrderItem(TMap<int32, int32>& aOrderItems)
{
	for(const auto& OrderItem : aOrderItems)
	{
		int32& OrderItemCount = OrderItems.FindOrAdd(OrderItem.Key);
		OrderItemCount += OrderItem.Value;
	}

	const TObjectPtr<UMS_ItemCacheTable> ItemTable = Cast<UMS_ItemCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::ItemData));
	if(!ItemTable)
	{
		MS_ENSURE(false);
		MS_LOG_VERBOSITY(Error, TEXT("Please Check Item Table."));
	}

	int32& GoldMoney = Money.FindOrAdd((static_cast<int32>(EMS_MoneyType::Gold)));
	GoldMoney -= ItemTable->GetTotalItemPrice(aOrderItems);
	
	SavePlayerData();

	gItemMng.UpdateMoney(Money);
	gItemMng.UpdateOrderItems(OrderItems);
	gItemMng.OnUpdateEarnMoneyDelegate.Broadcast(true);
}

void AMS_PlayerState::OrganizeItems()
{
	for(const auto& OrderItem : OrderItems)
	{
		if (OrderItem.Value != 0)
		{
			int32& Item = Items.FindOrAdd(OrderItem.Key);
			Item += OrderItem.Value;
		}
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

	const TObjectPtr<UMS_FurnitureCacheTable> FurnitureTable = Cast<UMS_FurnitureCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::Furniture));
	if(!FurnitureTable)
	{
		MS_ENSURE(false);
		MS_LOG_VERBOSITY(Error, TEXT("Please Check Item Table."));
	}
	
	int32& GoldMoney = Money.FindOrAdd((static_cast<int32>(EMS_MoneyType::Gold)));
	GoldMoney -= FurnitureTable->GetTotalFurniturePrice(aOrderFurnitures);
	
	SavePlayerData();

	gItemMng.UpdateMoney(Money);
	gItemMng.OnUpdateEarnMoneyDelegate.Broadcast(true);
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

void AMS_PlayerState::RegisterStaff(int32 aStaffId, int32 aWorkDay)
{
	// StaffIdTag 발급
	int32 MaxIdTag = INDEX_NONE;
	for (auto& StaffData : StaffDatas)
	{
		if (StaffData.StaffId == aStaffId)
		{
			if (StaffData.StaffIdTag > MaxIdTag)
			{
				MaxIdTag = StaffData.StaffIdTag;
			}
		}
	}
	
	int32 StaffIdTag = MaxIdTag + 1;
		
	// Save ( 직원은 다음날 출근하기에 + 1일 )
	FMS_GameDate FirstDateOfWork = GameDate;
	FirstDateOfWork.Day += 1;
	StaffDatas.Emplace(FMS_PlayerStaffData(aStaffId, StaffIdTag, FirstDateOfWork, aWorkDay));
	SavePlayerData();
	
	// 아이템으로 재등록
	gItemMng.UpdateStaffProperty(StaffDatas);
}

void AMS_PlayerState::RegisterStaffPriorityOfWorks(int32 aStaffId, int32 aStaffIdTag,
	const TArray<EMS_StaffIssueType>& aPriorityOfWorks, EMS_StaffUIPriorityType aStaffUIPriorityType)
{
	for (auto& StaffData : StaffDatas)
	{
		if (StaffData.StaffId == aStaffId && StaffData.StaffIdTag == aStaffIdTag)
		{
			StaffData.StaffUIPriorityType = aStaffUIPriorityType;
			StaffData.PriorityOfWorks = aPriorityOfWorks;
			return;
		}
	}
}

void AMS_PlayerState::WriteDiary(const FMS_SettlementSheet& Sheet)
{
	for(int32 i = 0 ; i < Diary.Num() ; i++)
	{
		if(Diary[i].Date == Sheet.Date)
		{
			Diary[i] = Sheet;
			return;
		}
	}
	Diary.Emplace(Sheet);
	
	SavePlayerData();
	
	gScheduleMng.UpdateDiary(Diary);
}

void AMS_PlayerState::InitDefaultPlayerData()
{
	// GameData
	GameDate = FMS_GameDate(1, 1, 1, EMS_DailyTimeZone::Morning);
	
	// OpenedZoneIds
	OpenedZoneIds.AddUnique(1);
	OpenedZoneIds.AddUnique(10);

	// Money
	Money.Emplace(1, 1500);
	Money.Emplace(2, 0);
	Money.Emplace(3, 0);
	gItemMng.UpdateMoney(Money);
	
	// Items
	Items.Emplace(4, 10);
	Items.Emplace(5, 10);
	Items.Emplace(12, 10);
	Items.Emplace(13, 10);
	Items.Emplace(21, 10);
	Items.Emplace(22, 10);
	Items.Emplace(25, 10);
	Items.Emplace(26, 10);
	Items.Emplace(27, 10);
	Items.Emplace(31, 10);
	Items.Emplace(32, 10);
	Items.Emplace(33, 10);
	Items.Emplace(34, 10);
	Items.Emplace(35, 10);
	Items.Emplace(40, 10);
	Items.Emplace(41, 10);
	
	//Furniture
	FMS_FurniturePositionData Counter = FMS_FurniturePositionData(1, FIntVector2(13, 10), EMS_Rotation::Rot270);
	GridPositionToMarketFurnitureDatas.Emplace(Counter.GridPosition, Counter);

	FMS_FurniturePositionData RoomTemperature1 = FMS_FurniturePositionData(7, FIntVector2(7, 2), EMS_Rotation::Rot0);
	RoomTemperature1.SlotDatas.Emplace(FMS_SlotData(4, 4, 10));
	RoomTemperature1.SlotDatas.Emplace(FMS_SlotData(5, 5, 10));
	RoomTemperature1.SlotDatas.Emplace(FMS_SlotData(6, 6, 10));
	GridPositionToMarketFurnitureDatas.Emplace(RoomTemperature1.GridPosition, RoomTemperature1);

	FMS_FurniturePositionData RoomTemperature2 = FMS_FurniturePositionData(7, FIntVector2(9, 2), EMS_Rotation::Rot0);
	RoomTemperature2.SlotDatas.Emplace(FMS_SlotData(12, 12, 10));
	RoomTemperature2.SlotDatas.Emplace(FMS_SlotData(13, 13, 10));
	RoomTemperature2.SlotDatas.Emplace(FMS_SlotData(14, 14, 10));
	RoomTemperature2.SlotDatas.Emplace(FMS_SlotData(15, 15, 10));
	GridPositionToMarketFurnitureDatas.Emplace(RoomTemperature2.GridPosition, RoomTemperature2);
	
	FMS_FurniturePositionData VeggieStand = FMS_FurniturePositionData(8, FIntVector2(13, 2), EMS_Rotation::Rot0);
	VeggieStand.SlotDatas.Emplace(FMS_SlotData(25, 25, 10));
	GridPositionToMarketFurnitureDatas.Emplace(VeggieStand.GridPosition, VeggieStand);

	FMS_FurniturePositionData Rack = FMS_FurniturePositionData(11, FIntVector2(-3, 13), EMS_Rotation::Rot0);
	GridPositionToMarketFurnitureDatas.Emplace(Rack.GridPosition, Rack);
	
	FMS_FurniturePositionData Pallet1 = FMS_FurniturePositionData(10, FIntVector2(-4, 28), EMS_Rotation::Rot180);
	GridPositionToMarketFurnitureDatas.Emplace(Pallet1.GridPosition, Pallet1);

	FMS_FurniturePositionData Pallet2 = FMS_FurniturePositionData(10, FIntVector2(-6, 28), EMS_Rotation::Rot180);
	GridPositionToMarketFurnitureDatas.Emplace(Pallet2.GridPosition, Pallet2);
	
	FMS_FurniturePositionData Pallet3 = FMS_FurniturePositionData(10, FIntVector2(-8, 28), EMS_Rotation::Rot180);
	GridPositionToMarketFurnitureDatas.Emplace(Pallet3.GridPosition, Pallet3);

	FMS_FurniturePositionData Pallet4 = FMS_FurniturePositionData(10, FIntVector2(-10, 28), EMS_Rotation::Rot180);
	GridPositionToMarketFurnitureDatas.Emplace(Pallet4.GridPosition, Pallet4);
	
	FMS_FurniturePositionData Pallet5 = FMS_FurniturePositionData(10, FIntVector2(-12, 28), EMS_Rotation::Rot180);
	GridPositionToMarketFurnitureDatas.Emplace(Pallet5.GridPosition, Pallet5);

	FMS_FurniturePositionData Pallet6 = FMS_FurniturePositionData(10, FIntVector2(-14, 28), EMS_Rotation::Rot180);
	GridPositionToMarketFurnitureDatas.Emplace(Pallet6.GridPosition, Pallet6);

	for(const auto& GridPositionToMarketFurnitureData : GridPositionToMarketFurnitureDatas)
	{
		int32& FurnitureCount = Furnitures.FindOrAdd(GridPositionToMarketFurnitureData.Value.FurnitureTableId);
		FurnitureCount++;
	}
	// Staff
	StaffDatas.Emplace(FMS_PlayerStaffData(1, 1, FMS_GameDate(1, 1, 1)));

	// Diary
	Diary.Emplace(FMS_SettlementSheet());
}

void AMS_PlayerState::InitPlayerData()
{
	UMS_PlayerData* PlayerData = Cast<UMS_PlayerData>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));
	if (PlayerData == nullptr)
	{
		PlayerData = GetMutableDefault<UMS_PlayerData>();
	}

	bInitDefaultData = PlayerData->bInitDefaultData;

	GameDate = PlayerData->GameDate;
	
	OpenedZoneIds = PlayerData->OpenedZoneIds;

	GridPositionToMarketFurnitureDatas.Empty();
	for (const auto& MarketFurnitureData : PlayerData->MarketFurnitureDatas)
	{
		if (GridPositionToMarketFurnitureDatas.Contains(MarketFurnitureData.GridPosition))
		{
			MS_LOG_VERBOSITY(Error, TEXT("[%s] There is alreay Furniture at this grid position. [Grid Position : %d, %d]")
				, *MS_FUNC_STRING, MarketFurnitureData.GridPosition.X, MarketFurnitureData.GridPosition.Y);
			MS_CHECK(false);
		}
		
		GridPositionToMarketFurnitureDatas.Emplace(MarketFurnitureData.GridPosition, MarketFurnitureData);
	}

	Money = PlayerData->Money;
	gItemMng.UpdateMoney(Money);
	
	Items = PlayerData->Items;

	TArray<int32> ItemKeyArray;
	Items.GenerateKeyArray(ItemKeyArray);
	for (auto& Key : ItemKeyArray)
	{
		if (*Items.Find(Key) == 0)
		{
			Items.Remove(Key);
		}
	}
	
	gItemMng.UpdateItems(Items);
	
	OrderItems = PlayerData->OrderItems;
	
	TArray<int32> OrderItemKeyArray;
	OrderItems.GenerateKeyArray(OrderItemKeyArray);
	for (auto& Key : OrderItemKeyArray)
	{
		if (*OrderItems.Find(Key) == 0)
		{
			OrderItems.Remove(Key);
		}
	}
	
	gItemMng.UpdateOrderItems(OrderItems);

	Furnitures = PlayerData->Furnitures;
	OrderFurnitures = PlayerData->OrderFurnitures;
	gItemMng.UpdateFurnitures(Furnitures);
	gItemMng.UpdateOrderFurnitures(OrderFurnitures);
	
	StaffDatas = PlayerData->StaffDatas;
	gItemMng.UpdateStaffProperty(StaffDatas);

	Diary = PlayerData->Diary;
	if(Diary.Num() == 1)
	{
		Diary[0].Date = gScheduleMng.GetGameDate();
	}
	gScheduleMng.UpdateDiary(Diary);
	
	if (!bInitDefaultData)
	{
		bInitDefaultData = true;
		InitDefaultPlayerData();
		SavePlayerData();
	}
}

void AMS_PlayerState::SavePlayerData()
{
	UMS_PlayerData* NewPlayerData = NewObject<UMS_PlayerData>();
	
	NewPlayerData->bInitDefaultData = bInitDefaultData;

	FMS_GameDate SaveGameDate = GameDate;
	if (GameDate.DailyTimeZone == EMS_DailyTimeZone::DayTimeWork)
	{
		SaveGameDate.DailyTimeZone = EMS_DailyTimeZone::Morning;
	}
	else if (GameDate.DailyTimeZone == EMS_DailyTimeZone::EveningWork)
	{
		SaveGameDate.DailyTimeZone = EMS_DailyTimeZone::Evening;
	}
	NewPlayerData->GameDate = SaveGameDate;

	NewPlayerData->OpenedZoneIds = OpenedZoneIds;
	
	for (auto MarketFurnitureData : GridPositionToMarketFurnitureDatas)
	{
		NewPlayerData->MarketFurnitureDatas.Emplace(MarketFurnitureData.Value);
	}

	NewPlayerData->Money = Money;
	NewPlayerData->OrderItems = OrderItems;
	NewPlayerData->Items = Items;

	NewPlayerData->OrderFurnitures = OrderFurnitures;
	NewPlayerData->Furnitures = Furnitures;
	
	NewPlayerData->StaffDatas = StaffDatas;

	NewPlayerData->Diary = Diary;
	
	if (!UGameplayStatics::SaveGameToSlot(NewPlayerData, SaveSlotName, 0))
	{
		MS_LOG_VERBOSITY(Error, TEXT("SaveGameError"));
		MS_ENSURE(false);
	}
}
