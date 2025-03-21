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
		MS_ERROR(TEXT("Please Check Item Table."));
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
		MS_ERROR(TEXT("Please Check Item Table."));
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
		MS_ERROR(TEXT("[%s] There isn't Furniture at this grid position. [Grid Position : %d, %d]")
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

void AMS_PlayerState::ResetPlayerData()
{
	bInitDefaultData = false;
	
	OpenedZoneIds.Reset();

	Money.Reset();

	Items.Reset();
	OrderItems.Reset();
	
	GridPositionToMarketFurnitureDatas.Reset();
	Furnitures.Reset();
	OrderFurnitures.Reset();

	StaffDatas.Reset();
	
	Diary.Reset();
}

void AMS_PlayerState::InitDefaultPlayerData()
{
	bInitDefaultData = true;
	
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

void AMS_PlayerState::InitDesignedPlayerData1()
{
#if WITH_EDITOR
	bInitDefaultData = true;

	
	// GameData
	GameDate = FMS_GameDate(1, 1, 1, EMS_DailyTimeZone::Morning);
	
	// OpenedZoneIds
	OpenedZoneIds.AddUnique(1);
	OpenedZoneIds.AddUnique(2);
	OpenedZoneIds.AddUnique(3);
	OpenedZoneIds.AddUnique(4);
	OpenedZoneIds.AddUnique(5);
	OpenedZoneIds.AddUnique(6);
	OpenedZoneIds.AddUnique(7);
	OpenedZoneIds.AddUnique(8);
	OpenedZoneIds.AddUnique(9);
	OpenedZoneIds.AddUnique(10);
	OpenedZoneIds.AddUnique(11);
	OpenedZoneIds.AddUnique(12);
	OpenedZoneIds.AddUnique(13);

	// Money
	Money.Emplace(1, 150000);
	Money.Emplace(2, 0);
	Money.Emplace(3, 0);
	gItemMng.UpdateMoney(Money);
	
	// Items
	Items.Emplace(4, 300);
	Items.Emplace(5, 300);
	Items.Emplace(6, 300);
	Items.Emplace(7, 300);
	Items.Emplace(8, 300);
	Items.Emplace(9, 300);
	Items.Emplace(10, 300);
	Items.Emplace(11, 300);
	Items.Emplace(12, 100);
	Items.Emplace(13, 100);
	Items.Emplace(14, 100);
	Items.Emplace(15, 100);
	Items.Emplace(16, 100);
	Items.Emplace(17, 100);
	Items.Emplace(18, 100);
	Items.Emplace(19, 100);
	Items.Emplace(20, 100);
	Items.Emplace(21, 100);
	Items.Emplace(22, 100);
	Items.Emplace(23, 100);
	Items.Emplace(24, 100);
	Items.Emplace(25, 100);
	Items.Emplace(26, 100);
	Items.Emplace(27, 100);
	Items.Emplace(28, 100);
	Items.Emplace(29, 100);
	Items.Emplace(30, 100);
	Items.Emplace(31, 100);
	Items.Emplace(32, 100);
	Items.Emplace(33, 100);
	Items.Emplace(34, 200);
	Items.Emplace(35, 200);
	Items.Emplace(36, 200);
	Items.Emplace(37, 200);
	Items.Emplace(38, 200);
	Items.Emplace(39, 200);
	Items.Emplace(40, 200);
	Items.Emplace(41, 200);
	Items.Emplace(42, 200);
	Items.Emplace(43, 200);
	Items.Emplace(44, 200);
	Items.Emplace(45, 200);
	Items.Emplace(46, 200);
	
	//Furniture
	FMS_FurniturePositionData Counter1 = FMS_FurniturePositionData(2, FIntVector2(18, 15), EMS_Rotation::Rot90);
	GridPositionToMarketFurnitureDatas.Emplace(Counter1.GridPosition, Counter1);

	FMS_FurniturePositionData Counter2 = FMS_FurniturePositionData(1, FIntVector2(24, 15), EMS_Rotation::Rot270);
	GridPositionToMarketFurnitureDatas.Emplace(Counter2.GridPosition, Counter2);
	
	FMS_FurniturePositionData Counter3 = FMS_FurniturePositionData(2, FIntVector2(30, 15), EMS_Rotation::Rot90);
	GridPositionToMarketFurnitureDatas.Emplace(Counter3.GridPosition, Counter3);

	FMS_FurniturePositionData Counter4 = FMS_FurniturePositionData(1, FIntVector2(36, 15), EMS_Rotation::Rot270);
	GridPositionToMarketFurnitureDatas.Emplace(Counter4.GridPosition, Counter4);
	

	FMS_FurniturePositionData RoomTemperature1 = FMS_FurniturePositionData(7, FIntVector2(17, -3), EMS_Rotation::Rot90);
	RoomTemperature1.SlotDatas.Emplace(FMS_SlotData(4, 4, 16));
	RoomTemperature1.SlotDatas.Emplace(FMS_SlotData(4, 4, 16));
	RoomTemperature1.SlotDatas.Emplace(FMS_SlotData(4, 4, 16));
	GridPositionToMarketFurnitureDatas.Emplace(RoomTemperature1.GridPosition, RoomTemperature1);

	FMS_FurniturePositionData RoomTemperature2 = FMS_FurniturePositionData(7, FIntVector2(19, -3), EMS_Rotation::Rot180);
	RoomTemperature2.SlotDatas.Emplace(FMS_SlotData(5, 5, 16));
	RoomTemperature2.SlotDatas.Emplace(FMS_SlotData(5, 5, 16));
	RoomTemperature2.SlotDatas.Emplace(FMS_SlotData(5, 5, 16));
	GridPositionToMarketFurnitureDatas.Emplace(RoomTemperature2.GridPosition, RoomTemperature2);

	FMS_FurniturePositionData RoomTemperature3 = FMS_FurniturePositionData(7, FIntVector2(21, -3), EMS_Rotation::Rot180);
	RoomTemperature3.SlotDatas.Emplace(FMS_SlotData(6, 6, 16));
	RoomTemperature3.SlotDatas.Emplace(FMS_SlotData(6, 6, 16));
	RoomTemperature3.SlotDatas.Emplace(FMS_SlotData(6, 6, 16));
	GridPositionToMarketFurnitureDatas.Emplace(RoomTemperature3.GridPosition, RoomTemperature3);

	FMS_FurniturePositionData RoomTemperature4 = FMS_FurniturePositionData(7, FIntVector2(23, -3), EMS_Rotation::Rot270);
	RoomTemperature4.SlotDatas.Emplace(FMS_SlotData(7, 7, 16));
	RoomTemperature4.SlotDatas.Emplace(FMS_SlotData(7, 7, 16));
	RoomTemperature4.SlotDatas.Emplace(FMS_SlotData(7, 7, 16));
	GridPositionToMarketFurnitureDatas.Emplace(RoomTemperature4.GridPosition, RoomTemperature4);

	FMS_FurniturePositionData RoomTemperature5 = FMS_FurniturePositionData(7, FIntVector2(17, -1), EMS_Rotation::Rot90);
	RoomTemperature5.SlotDatas.Emplace(FMS_SlotData(4, 4, 16));
	RoomTemperature5.SlotDatas.Emplace(FMS_SlotData(4, 4, 16));
	RoomTemperature5.SlotDatas.Emplace(FMS_SlotData(4, 4, 16));
	GridPositionToMarketFurnitureDatas.Emplace(RoomTemperature5.GridPosition, RoomTemperature5);

	FMS_FurniturePositionData RoomTemperature6 = FMS_FurniturePositionData(7, FIntVector2(19, -1), EMS_Rotation::Rot0);
	RoomTemperature6.SlotDatas.Emplace(FMS_SlotData(5, 5, 16));
	RoomTemperature6.SlotDatas.Emplace(FMS_SlotData(5, 5, 16));
	RoomTemperature6.SlotDatas.Emplace(FMS_SlotData(5, 5, 16));
	GridPositionToMarketFurnitureDatas.Emplace(RoomTemperature6.GridPosition, RoomTemperature6);

	FMS_FurniturePositionData RoomTemperature7 = FMS_FurniturePositionData(7, FIntVector2(21, -1), EMS_Rotation::Rot0);
	RoomTemperature7.SlotDatas.Emplace(FMS_SlotData(6, 6, 16));
	RoomTemperature7.SlotDatas.Emplace(FMS_SlotData(6, 6, 16));
	RoomTemperature7.SlotDatas.Emplace(FMS_SlotData(6, 6, 16));
	GridPositionToMarketFurnitureDatas.Emplace(RoomTemperature7.GridPosition, RoomTemperature7);

	FMS_FurniturePositionData RoomTemperature8 = FMS_FurniturePositionData(7, FIntVector2(23, -1), EMS_Rotation::Rot270);
	RoomTemperature8.SlotDatas.Emplace(FMS_SlotData(7, 7, 16));
	RoomTemperature8.SlotDatas.Emplace(FMS_SlotData(7, 7, 16));
	RoomTemperature8.SlotDatas.Emplace(FMS_SlotData(7, 7, 16));
	GridPositionToMarketFurnitureDatas.Emplace(RoomTemperature8.GridPosition, RoomTemperature8);

	FMS_FurniturePositionData RoomTemperature9 = FMS_FurniturePositionData(7, FIntVector2(29, -3), EMS_Rotation::Rot90);
	RoomTemperature9.SlotDatas.Emplace(FMS_SlotData(8, 8, 16));
	RoomTemperature9.SlotDatas.Emplace(FMS_SlotData(8, 8, 16));
	RoomTemperature9.SlotDatas.Emplace(FMS_SlotData(8, 8, 16));
	GridPositionToMarketFurnitureDatas.Emplace(RoomTemperature9.GridPosition, RoomTemperature9);

	FMS_FurniturePositionData RoomTemperature10 = FMS_FurniturePositionData(7, FIntVector2(31, -3), EMS_Rotation::Rot180);
	RoomTemperature10.SlotDatas.Emplace(FMS_SlotData(9, 9, 16));
	RoomTemperature10.SlotDatas.Emplace(FMS_SlotData(9, 9, 16));
	RoomTemperature10.SlotDatas.Emplace(FMS_SlotData(9, 9, 16));
	GridPositionToMarketFurnitureDatas.Emplace(RoomTemperature10.GridPosition, RoomTemperature10);

	FMS_FurniturePositionData RoomTemperature11 = FMS_FurniturePositionData(7, FIntVector2(33, -3), EMS_Rotation::Rot180);
	RoomTemperature11.SlotDatas.Emplace(FMS_SlotData(10, 10, 16));
	RoomTemperature11.SlotDatas.Emplace(FMS_SlotData(10, 10, 16));
	RoomTemperature11.SlotDatas.Emplace(FMS_SlotData(10, 10, 16));
	GridPositionToMarketFurnitureDatas.Emplace(RoomTemperature11.GridPosition, RoomTemperature11);

	FMS_FurniturePositionData RoomTemperature12 = FMS_FurniturePositionData(7, FIntVector2(35, -3), EMS_Rotation::Rot270);
	RoomTemperature12.SlotDatas.Emplace(FMS_SlotData(11, 11, 16));
	RoomTemperature12.SlotDatas.Emplace(FMS_SlotData(11, 11, 16));
	RoomTemperature12.SlotDatas.Emplace(FMS_SlotData(11, 11, 16));
	GridPositionToMarketFurnitureDatas.Emplace(RoomTemperature12.GridPosition, RoomTemperature12);

	FMS_FurniturePositionData RoomTemperature13 = FMS_FurniturePositionData(7, FIntVector2(29, -1), EMS_Rotation::Rot90);
	RoomTemperature13.SlotDatas.Emplace(FMS_SlotData(8, 8, 16));
	RoomTemperature13.SlotDatas.Emplace(FMS_SlotData(8, 8, 16));
	RoomTemperature13.SlotDatas.Emplace(FMS_SlotData(8, 8, 16));
	GridPositionToMarketFurnitureDatas.Emplace(RoomTemperature13.GridPosition, RoomTemperature13);

	FMS_FurniturePositionData RoomTemperature14 = FMS_FurniturePositionData(7, FIntVector2(31, -1), EMS_Rotation::Rot0);
	RoomTemperature14.SlotDatas.Emplace(FMS_SlotData(9, 9, 16));
	RoomTemperature14.SlotDatas.Emplace(FMS_SlotData(9, 9, 16));
	RoomTemperature14.SlotDatas.Emplace(FMS_SlotData(9, 9, 16));
	GridPositionToMarketFurnitureDatas.Emplace(RoomTemperature14.GridPosition, RoomTemperature14);

	FMS_FurniturePositionData RoomTemperature15 = FMS_FurniturePositionData(7, FIntVector2(33, -1), EMS_Rotation::Rot0);
	RoomTemperature15.SlotDatas.Emplace(FMS_SlotData(10, 10, 16));
	RoomTemperature15.SlotDatas.Emplace(FMS_SlotData(10, 10, 16));
	RoomTemperature15.SlotDatas.Emplace(FMS_SlotData(10, 10, 16));
	GridPositionToMarketFurnitureDatas.Emplace(RoomTemperature15.GridPosition, RoomTemperature15);

	FMS_FurniturePositionData RoomTemperature16 = FMS_FurniturePositionData(7, FIntVector2(35, -1), EMS_Rotation::Rot270);
	RoomTemperature16.SlotDatas.Emplace(FMS_SlotData(11, 11, 16));
	RoomTemperature16.SlotDatas.Emplace(FMS_SlotData(11, 11, 16));
	RoomTemperature16.SlotDatas.Emplace(FMS_SlotData(11, 11, 16));
	GridPositionToMarketFurnitureDatas.Emplace(RoomTemperature16.GridPosition, RoomTemperature16);

	FMS_FurniturePositionData RoomTemperature17 = FMS_FurniturePositionData(7, FIntVector2(17, 5), EMS_Rotation::Rot90);
	RoomTemperature17.SlotDatas.Emplace(FMS_SlotData(6, 6, 16));
	RoomTemperature17.SlotDatas.Emplace(FMS_SlotData(7, 7, 16));
	RoomTemperature17.SlotDatas.Emplace(FMS_SlotData(8, 8, 16));
	GridPositionToMarketFurnitureDatas.Emplace(RoomTemperature17.GridPosition, RoomTemperature17);

	FMS_FurniturePositionData RoomTemperature18 = FMS_FurniturePositionData(7, FIntVector2(19, 5), EMS_Rotation::Rot180);
	RoomTemperature18.SlotDatas.Emplace(FMS_SlotData(9, 9, 16));
	RoomTemperature18.SlotDatas.Emplace(FMS_SlotData(9, 9, 16));
	RoomTemperature18.SlotDatas.Emplace(FMS_SlotData(5, 5, 16));
	GridPositionToMarketFurnitureDatas.Emplace(RoomTemperature18.GridPosition, RoomTemperature18);

	FMS_FurniturePositionData RoomTemperature19 = FMS_FurniturePositionData(7, FIntVector2(21, 5), EMS_Rotation::Rot180);
	RoomTemperature19.SlotDatas.Emplace(FMS_SlotData(10, 10, 16));
	RoomTemperature19.SlotDatas.Emplace(FMS_SlotData(10, 10, 16));
	RoomTemperature19.SlotDatas.Emplace(FMS_SlotData(6, 6, 16));
	GridPositionToMarketFurnitureDatas.Emplace(RoomTemperature19.GridPosition, RoomTemperature19);

	FMS_FurniturePositionData RoomTemperature20 = FMS_FurniturePositionData(7, FIntVector2(23, 5), EMS_Rotation::Rot270);
	RoomTemperature20.SlotDatas.Emplace(FMS_SlotData(7, 7, 16));
	RoomTemperature20.SlotDatas.Emplace(FMS_SlotData(4, 4, 16));
	RoomTemperature20.SlotDatas.Emplace(FMS_SlotData(4, 4, 16));
	GridPositionToMarketFurnitureDatas.Emplace(RoomTemperature20.GridPosition, RoomTemperature20);

	FMS_FurniturePositionData RoomTemperature21 = FMS_FurniturePositionData(7, FIntVector2(17, 7), EMS_Rotation::Rot90);
	RoomTemperature21.SlotDatas.Emplace(FMS_SlotData(11, 11, 16));
	RoomTemperature21.SlotDatas.Emplace(FMS_SlotData(8, 8, 16));
	RoomTemperature21.SlotDatas.Emplace(FMS_SlotData(8, 8, 16));
	GridPositionToMarketFurnitureDatas.Emplace(RoomTemperature21.GridPosition, RoomTemperature21);

	FMS_FurniturePositionData RoomTemperature22 = FMS_FurniturePositionData(7, FIntVector2(19, 7), EMS_Rotation::Rot0);
	RoomTemperature22.SlotDatas.Emplace(FMS_SlotData(8, 8, 16));
	RoomTemperature22.SlotDatas.Emplace(FMS_SlotData(9, 9, 16));
	RoomTemperature22.SlotDatas.Emplace(FMS_SlotData(9, 9, 16));
	GridPositionToMarketFurnitureDatas.Emplace(RoomTemperature22.GridPosition, RoomTemperature22);

	FMS_FurniturePositionData RoomTemperature23 = FMS_FurniturePositionData(7, FIntVector2(21, 7), EMS_Rotation::Rot0);
	RoomTemperature23.SlotDatas.Emplace(FMS_SlotData(7, 7, 16));
	RoomTemperature23.SlotDatas.Emplace(FMS_SlotData(10, 10, 16));
	RoomTemperature23.SlotDatas.Emplace(FMS_SlotData(10, 10, 16));
	GridPositionToMarketFurnitureDatas.Emplace(RoomTemperature23.GridPosition, RoomTemperature23);

	FMS_FurniturePositionData RoomTemperature24 = FMS_FurniturePositionData(7, FIntVector2(23, 7), EMS_Rotation::Rot270);
	RoomTemperature24.SlotDatas.Emplace(FMS_SlotData(6, 6, 16));
	RoomTemperature24.SlotDatas.Emplace(FMS_SlotData(6, 6, 16));
	RoomTemperature24.SlotDatas.Emplace(FMS_SlotData(5, 5, 16));
	GridPositionToMarketFurnitureDatas.Emplace(RoomTemperature24.GridPosition, RoomTemperature24);

	FMS_FurniturePositionData RoomTemperature25 = FMS_FurniturePositionData(7, FIntVector2(29, 5), EMS_Rotation::Rot90);
	RoomTemperature25.SlotDatas.Emplace(FMS_SlotData(4, 4, 16));
	RoomTemperature25.SlotDatas.Emplace(FMS_SlotData(5, 5, 16));
	RoomTemperature25.SlotDatas.Emplace(FMS_SlotData(6, 6, 16));
	GridPositionToMarketFurnitureDatas.Emplace(RoomTemperature25.GridPosition, RoomTemperature25);

	FMS_FurniturePositionData RoomTemperature26 = FMS_FurniturePositionData(7, FIntVector2(31, 5), EMS_Rotation::Rot180);
	RoomTemperature26.SlotDatas.Emplace(FMS_SlotData(5, 5, 16));
	RoomTemperature26.SlotDatas.Emplace(FMS_SlotData(7, 7, 16));
	RoomTemperature26.SlotDatas.Emplace(FMS_SlotData(7, 7, 16));
	GridPositionToMarketFurnitureDatas.Emplace(RoomTemperature26.GridPosition, RoomTemperature26);

	FMS_FurniturePositionData RoomTemperature27 = FMS_FurniturePositionData(7, FIntVector2(33, 5), EMS_Rotation::Rot180);
	RoomTemperature27.SlotDatas.Emplace(FMS_SlotData(6, 6, 16));
	RoomTemperature27.SlotDatas.Emplace(FMS_SlotData(7, 7, 16));
	RoomTemperature27.SlotDatas.Emplace(FMS_SlotData(7, 7, 16));
	GridPositionToMarketFurnitureDatas.Emplace(RoomTemperature27.GridPosition, RoomTemperature27);

	FMS_FurniturePositionData RoomTemperature28 = FMS_FurniturePositionData(7, FIntVector2(35, 5), EMS_Rotation::Rot270);
	RoomTemperature28.SlotDatas.Emplace(FMS_SlotData(4, 4, 16));
	RoomTemperature28.SlotDatas.Emplace(FMS_SlotData(5, 5, 16));
	RoomTemperature28.SlotDatas.Emplace(FMS_SlotData(6, 6, 16));
	GridPositionToMarketFurnitureDatas.Emplace(RoomTemperature28.GridPosition, RoomTemperature28);

	FMS_FurniturePositionData RoomTemperature29 = FMS_FurniturePositionData(7, FIntVector2(29, 7), EMS_Rotation::Rot90);
	RoomTemperature29.SlotDatas.Emplace(FMS_SlotData(8, 8, 16));
	RoomTemperature29.SlotDatas.Emplace(FMS_SlotData(9, 9, 16));
	RoomTemperature29.SlotDatas.Emplace(FMS_SlotData(10, 10, 16));
	GridPositionToMarketFurnitureDatas.Emplace(RoomTemperature29.GridPosition, RoomTemperature29);

	FMS_FurniturePositionData RoomTemperature30 = FMS_FurniturePositionData(7, FIntVector2(31, 7), EMS_Rotation::Rot0);
	RoomTemperature30.SlotDatas.Emplace(FMS_SlotData(9, 9, 16));
	RoomTemperature30.SlotDatas.Emplace(FMS_SlotData(11, 11, 16));
	RoomTemperature30.SlotDatas.Emplace(FMS_SlotData(11, 11, 16));
	GridPositionToMarketFurnitureDatas.Emplace(RoomTemperature30.GridPosition, RoomTemperature30);

	FMS_FurniturePositionData RoomTemperature31 = FMS_FurniturePositionData(7, FIntVector2(33, 7), EMS_Rotation::Rot0);
	RoomTemperature31.SlotDatas.Emplace(FMS_SlotData(10, 10, 16));
	RoomTemperature31.SlotDatas.Emplace(FMS_SlotData(11, 11, 16));
	RoomTemperature31.SlotDatas.Emplace(FMS_SlotData(11, 11, 16));
	GridPositionToMarketFurnitureDatas.Emplace(RoomTemperature31.GridPosition, RoomTemperature31);

	FMS_FurniturePositionData RoomTemperature32 = FMS_FurniturePositionData(7, FIntVector2(35, 7), EMS_Rotation::Rot270);
	RoomTemperature32.SlotDatas.Emplace(FMS_SlotData(8, 8, 16));
	RoomTemperature32.SlotDatas.Emplace(FMS_SlotData(9, 9, 16));
	RoomTemperature32.SlotDatas.Emplace(FMS_SlotData(10, 10, 16));
	GridPositionToMarketFurnitureDatas.Emplace(RoomTemperature32.GridPosition, RoomTemperature32);
	
	
	FMS_FurniturePositionData VeggieStand1 = FMS_FurniturePositionData(12, FIntVector2(2, -2), EMS_Rotation::Rot270);
	VeggieStand1.SlotDatas.Emplace(FMS_SlotData(21, 21, 16));
	VeggieStand1.SlotDatas.Emplace(FMS_SlotData(22, 22, 16));
	GridPositionToMarketFurnitureDatas.Emplace(VeggieStand1.GridPosition, VeggieStand1);

	FMS_FurniturePositionData VeggieStand2 = FMS_FurniturePositionData(12, FIntVector2(2, 0), EMS_Rotation::Rot270);
	VeggieStand2.SlotDatas.Emplace(FMS_SlotData(21, 21, 16));
	VeggieStand2.SlotDatas.Emplace(FMS_SlotData(22, 22, 16));
	GridPositionToMarketFurnitureDatas.Emplace(VeggieStand2.GridPosition, VeggieStand2);

	FMS_FurniturePositionData VeggieStand3 = FMS_FurniturePositionData(12, FIntVector2(2, 2), EMS_Rotation::Rot270);
	VeggieStand3.SlotDatas.Emplace(FMS_SlotData(21, 21, 16));
	VeggieStand3.SlotDatas.Emplace(FMS_SlotData(22, 22, 16));
	GridPositionToMarketFurnitureDatas.Emplace(VeggieStand3.GridPosition, VeggieStand3);

	FMS_FurniturePositionData VeggieStand4 = FMS_FurniturePositionData(12, FIntVector2(2, 4), EMS_Rotation::Rot270);
	VeggieStand4.SlotDatas.Emplace(FMS_SlotData(21, 21, 16));
	VeggieStand4.SlotDatas.Emplace(FMS_SlotData(22, 22, 16));
	GridPositionToMarketFurnitureDatas.Emplace(VeggieStand4.GridPosition, VeggieStand4);

	FMS_FurniturePositionData VeggieStand5 = FMS_FurniturePositionData(8, FIntVector2(9, -2), EMS_Rotation::Rot90);
	VeggieStand5.SlotDatas.Emplace(FMS_SlotData(23, 23, 16));
	GridPositionToMarketFurnitureDatas.Emplace(VeggieStand5.GridPosition, VeggieStand5);

	FMS_FurniturePositionData VeggieStand6 = FMS_FurniturePositionData(8, FIntVector2(9, 0), EMS_Rotation::Rot90);
	VeggieStand6.SlotDatas.Emplace(FMS_SlotData(24, 24, 16));
	GridPositionToMarketFurnitureDatas.Emplace(VeggieStand6.GridPosition, VeggieStand6);

	FMS_FurniturePositionData VeggieStand7 = FMS_FurniturePositionData(8, FIntVector2(9, 2), EMS_Rotation::Rot90);
	VeggieStand7.SlotDatas.Emplace(FMS_SlotData(25, 25, 10));
	GridPositionToMarketFurnitureDatas.Emplace(VeggieStand7.GridPosition, VeggieStand7);

	FMS_FurniturePositionData VeggieStand8 = FMS_FurniturePositionData(8, FIntVector2(9, 4), EMS_Rotation::Rot90);
	VeggieStand8.SlotDatas.Emplace(FMS_SlotData(25, 25, 10));
	GridPositionToMarketFurnitureDatas.Emplace(VeggieStand8.GridPosition, VeggieStand8);
	
	FMS_FurniturePositionData VeggieStand9 = FMS_FurniturePositionData(8, FIntVector2(11, -2), EMS_Rotation::Rot270);
	VeggieStand9.SlotDatas.Emplace(FMS_SlotData(23, 23, 16));
	GridPositionToMarketFurnitureDatas.Emplace(VeggieStand9.GridPosition, VeggieStand9);

	FMS_FurniturePositionData VeggieStand10 = FMS_FurniturePositionData(8, FIntVector2(11, 0), EMS_Rotation::Rot270);
	VeggieStand10.SlotDatas.Emplace(FMS_SlotData(24, 24, 16));
	GridPositionToMarketFurnitureDatas.Emplace(VeggieStand10.GridPosition, VeggieStand10);

	FMS_FurniturePositionData VeggieStand11 = FMS_FurniturePositionData(8, FIntVector2(11, 2), EMS_Rotation::Rot270);
	VeggieStand11.SlotDatas.Emplace(FMS_SlotData(25, 25, 10));
	GridPositionToMarketFurnitureDatas.Emplace(VeggieStand11.GridPosition, VeggieStand11);

	FMS_FurniturePositionData VeggieStand12 = FMS_FurniturePositionData(8, FIntVector2(11, 4), EMS_Rotation::Rot270);
	VeggieStand12.SlotDatas.Emplace(FMS_SlotData(25, 25, 10));
	GridPositionToMarketFurnitureDatas.Emplace(VeggieStand12.GridPosition, VeggieStand12);


	FMS_FurniturePositionData Discount1 = FMS_FurniturePositionData(3, FIntVector2(1, 10), EMS_Rotation::Rot270);
	Discount1.SlotDatas.Emplace(FMS_SlotData(4, 4, 16));
	GridPositionToMarketFurnitureDatas.Emplace(Discount1.GridPosition, Discount1);

	FMS_FurniturePositionData Discount2 = FMS_FurniturePositionData(3, FIntVector2(1, 12), EMS_Rotation::Rot270);
	Discount2.SlotDatas.Emplace(FMS_SlotData(5, 5, 16));
	GridPositionToMarketFurnitureDatas.Emplace(Discount2.GridPosition, Discount2);

	
	FMS_FurniturePositionData FridgerSmall1 = FMS_FurniturePositionData(5, FIntVector2(9, 10), EMS_Rotation::Rot90);
	FridgerSmall1.SlotDatas.Emplace(FMS_SlotData(26, 26, 9));
	GridPositionToMarketFurnitureDatas.Emplace(FridgerSmall1.GridPosition, FridgerSmall1);

	FMS_FurniturePositionData FridgerSmall2 = FMS_FurniturePositionData(5, FIntVector2(9, 12), EMS_Rotation::Rot90);
	FridgerSmall2.SlotDatas.Emplace(FMS_SlotData(27, 27, 9));
	GridPositionToMarketFurnitureDatas.Emplace(FridgerSmall2.GridPosition, FridgerSmall2);

	FMS_FurniturePositionData FridgerSmall3 = FMS_FurniturePositionData(5, FIntVector2(11, 10), EMS_Rotation::Rot270);
	FridgerSmall3.SlotDatas.Emplace(FMS_SlotData(28, 28, 9));
	GridPositionToMarketFurnitureDatas.Emplace(FridgerSmall3.GridPosition, FridgerSmall3);

	FMS_FurniturePositionData FridgerSmall4 = FMS_FurniturePositionData(5, FIntVector2(11, 12), EMS_Rotation::Rot270);
	FridgerSmall4.SlotDatas.Emplace(FMS_SlotData(30, 30, 9));
	GridPositionToMarketFurnitureDatas.Emplace(FridgerSmall4.GridPosition, FridgerSmall4);

	
	FMS_FurniturePositionData Fridger1 = FMS_FurniturePositionData(4, FIntVector2(3, -9), EMS_Rotation::Rot0);
	Fridger1.SlotDatas.Emplace(FMS_SlotData(34, 34, 16));
	Fridger1.SlotDatas.Emplace(FMS_SlotData(34, 34, 16));
	Fridger1.SlotDatas.Emplace(FMS_SlotData(35, 35, 16));
	GridPositionToMarketFurnitureDatas.Emplace(Fridger1.GridPosition, Fridger1);
	
	FMS_FurniturePositionData Fridger2 = FMS_FurniturePositionData(4, FIntVector2(5, -9), EMS_Rotation::Rot0);
	Fridger2.SlotDatas.Emplace(FMS_SlotData(34, 34, 16));
	Fridger2.SlotDatas.Emplace(FMS_SlotData(34, 34, 16));
	Fridger2.SlotDatas.Emplace(FMS_SlotData(35, 35, 16));
	GridPositionToMarketFurnitureDatas.Emplace(Fridger2.GridPosition, Fridger2);
	
	FMS_FurniturePositionData Fridger3 = FMS_FurniturePositionData(4, FIntVector2(7, -9), EMS_Rotation::Rot0);
	Fridger3.SlotDatas.Emplace(FMS_SlotData(36, 36, 16));
	Fridger3.SlotDatas.Emplace(FMS_SlotData(36, 36, 16));
	Fridger3.SlotDatas.Emplace(FMS_SlotData(35, 35, 16));
	GridPositionToMarketFurnitureDatas.Emplace(Fridger3.GridPosition, Fridger3);

	FMS_FurniturePositionData Fridger4 = FMS_FurniturePositionData(4, FIntVector2(9, -9), EMS_Rotation::Rot0);
	Fridger4.SlotDatas.Emplace(FMS_SlotData(36, 36, 16));
	Fridger4.SlotDatas.Emplace(FMS_SlotData(36, 36, 16));
	Fridger4.SlotDatas.Emplace(FMS_SlotData(35, 35, 16));
	GridPositionToMarketFurnitureDatas.Emplace(Fridger4.GridPosition, Fridger4);

	FMS_FurniturePositionData Fridger5 = FMS_FurniturePositionData(4, FIntVector2(11, -9), EMS_Rotation::Rot0);
	Fridger5.SlotDatas.Emplace(FMS_SlotData(37, 37, 16));
	Fridger5.SlotDatas.Emplace(FMS_SlotData(37, 37, 16));
	Fridger5.SlotDatas.Emplace(FMS_SlotData(38, 38, 16));
	GridPositionToMarketFurnitureDatas.Emplace(Fridger5.GridPosition, Fridger5);

	FMS_FurniturePositionData Fridger6 = FMS_FurniturePositionData(4, FIntVector2(13, -9), EMS_Rotation::Rot0);
	Fridger6.SlotDatas.Emplace(FMS_SlotData(37, 37, 16));
	Fridger6.SlotDatas.Emplace(FMS_SlotData(37, 37, 16));
	Fridger6.SlotDatas.Emplace(FMS_SlotData(38, 38, 16));
	GridPositionToMarketFurnitureDatas.Emplace(Fridger6.GridPosition, Fridger6);

	FMS_FurniturePositionData Fridger7 = FMS_FurniturePositionData(4, FIntVector2(15, -9), EMS_Rotation::Rot0);
	Fridger7.SlotDatas.Emplace(FMS_SlotData(39, 39, 16));
	Fridger7.SlotDatas.Emplace(FMS_SlotData(39, 39, 16));
	Fridger7.SlotDatas.Emplace(FMS_SlotData(39, 39, 16));
	GridPositionToMarketFurnitureDatas.Emplace(Fridger7.GridPosition, Fridger7);

	FMS_FurniturePositionData Fridger8 = FMS_FurniturePositionData(4, FIntVector2(17, -9), EMS_Rotation::Rot0);
	Fridger8.SlotDatas.Emplace(FMS_SlotData(41, 41, 16));
	Fridger8.SlotDatas.Emplace(FMS_SlotData(42, 42, 16));
	Fridger8.SlotDatas.Emplace(FMS_SlotData(43, 43, 16));
	GridPositionToMarketFurnitureDatas.Emplace(Fridger8.GridPosition, Fridger8);

	FMS_FurniturePositionData Fridger9 = FMS_FurniturePositionData(4, FIntVector2(19, -9), EMS_Rotation::Rot0);
	Fridger9.SlotDatas.Emplace(FMS_SlotData(44, 44, 16));
	Fridger9.SlotDatas.Emplace(FMS_SlotData(45, 45, 16));
	Fridger9.SlotDatas.Emplace(FMS_SlotData(46, 46, 16));
	GridPositionToMarketFurnitureDatas.Emplace(Fridger9.GridPosition, Fridger9);

	FMS_FurniturePositionData Fridger10 = FMS_FurniturePositionData(4, FIntVector2(21, -9), EMS_Rotation::Rot0);
	Fridger10.SlotDatas.Emplace(FMS_SlotData(40, 40, 16));
	Fridger10.SlotDatas.Emplace(FMS_SlotData(40, 40, 16));
	Fridger10.SlotDatas.Emplace(FMS_SlotData(40, 40, 16));
	GridPositionToMarketFurnitureDatas.Emplace(Fridger10.GridPosition, Fridger10);

	FMS_FurniturePositionData Fridger11 = FMS_FurniturePositionData(4, FIntVector2(23, -9), EMS_Rotation::Rot0);
	Fridger11.SlotDatas.Emplace(FMS_SlotData(40, 40, 16));
	Fridger11.SlotDatas.Emplace(FMS_SlotData(40, 40, 16));
	Fridger11.SlotDatas.Emplace(FMS_SlotData(40, 40, 16));
	GridPositionToMarketFurnitureDatas.Emplace(Fridger11.GridPosition, Fridger11);

	FMS_FurniturePositionData Fridger12 = FMS_FurniturePositionData(4, FIntVector2(25, -9), EMS_Rotation::Rot0);
	Fridger12.SlotDatas.Emplace(FMS_SlotData(40, 40, 16));
	Fridger12.SlotDatas.Emplace(FMS_SlotData(40, 40, 16));
	Fridger12.SlotDatas.Emplace(FMS_SlotData(40, 40, 16));
	GridPositionToMarketFurnitureDatas.Emplace(Fridger12.GridPosition, Fridger12);
	
	
	FMS_FurniturePositionData Freezer1 = FMS_FurniturePositionData(6, FIntVector2(27, -9), EMS_Rotation::Rot0);
	Freezer1.SlotDatas.Emplace(FMS_SlotData(12, 12, 6));
	Freezer1.SlotDatas.Emplace(FMS_SlotData(13, 13, 6));
	Freezer1.SlotDatas.Emplace(FMS_SlotData(14, 14, 6));
	GridPositionToMarketFurnitureDatas.Emplace(Freezer1.GridPosition, Freezer1);

	FMS_FurniturePositionData Freezer2 = FMS_FurniturePositionData(6, FIntVector2(29, -9), EMS_Rotation::Rot0);
	Freezer2.SlotDatas.Emplace(FMS_SlotData(15, 15, 6));
	Freezer2.SlotDatas.Emplace(FMS_SlotData(16, 16, 12));
	Freezer2.SlotDatas.Emplace(FMS_SlotData(17, 17, 12));
	GridPositionToMarketFurnitureDatas.Emplace(Freezer2.GridPosition, Freezer2);
	
	FMS_FurniturePositionData Freezer3 = FMS_FurniturePositionData(6, FIntVector2(31, -9), EMS_Rotation::Rot0);
	Freezer3.SlotDatas.Emplace(FMS_SlotData(18, 18, 12));
	Freezer3.SlotDatas.Emplace(FMS_SlotData(19, 19, 12));
	Freezer3.SlotDatas.Emplace(FMS_SlotData(20, 20, 12));
	GridPositionToMarketFurnitureDatas.Emplace(Freezer3.GridPosition, Freezer3);

	FMS_FurniturePositionData Freezer4 = FMS_FurniturePositionData(6, FIntVector2(33, -9), EMS_Rotation::Rot0);
	Freezer4.SlotDatas.Emplace(FMS_SlotData(32, 32, 12));
	Freezer4.SlotDatas.Emplace(FMS_SlotData(32, 32, 12));
	Freezer4.SlotDatas.Emplace(FMS_SlotData(31, 31, 6));
	GridPositionToMarketFurnitureDatas.Emplace(Freezer4.GridPosition, Freezer4);

	FMS_FurniturePositionData Freezer5 = FMS_FurniturePositionData(6, FIntVector2(35, -9), EMS_Rotation::Rot0);
	Freezer5.SlotDatas.Emplace(FMS_SlotData(32, 32, 12));
	Freezer5.SlotDatas.Emplace(FMS_SlotData(32, 32, 12));
	Freezer5.SlotDatas.Emplace(FMS_SlotData(31, 31, 6));
	GridPositionToMarketFurnitureDatas.Emplace(Freezer5.GridPosition, Freezer5);
	
	FMS_FurniturePositionData Freezer6 = FMS_FurniturePositionData(6, FIntVector2(37, -9), EMS_Rotation::Rot0);
	Freezer6.SlotDatas.Emplace(FMS_SlotData(33, 33, 16));
	Freezer6.SlotDatas.Emplace(FMS_SlotData(33, 33, 16));
	Freezer6.SlotDatas.Emplace(FMS_SlotData(33, 33, 16));
	GridPositionToMarketFurnitureDatas.Emplace(Freezer6.GridPosition, Freezer6);

	
	FMS_FurniturePositionData Rack1 = FMS_FurniturePositionData(11, FIntVector2(-18, 2), EMS_Rotation::Rot0);
	GridPositionToMarketFurnitureDatas.Emplace(Rack1.GridPosition, Rack1);

	FMS_FurniturePositionData Rack2 = FMS_FurniturePositionData(11, FIntVector2(-14, 2), EMS_Rotation::Rot0);
	GridPositionToMarketFurnitureDatas.Emplace(Rack2.GridPosition, Rack2);
	
	FMS_FurniturePositionData Rack3 = FMS_FurniturePositionData(11, FIntVector2(-10, 2), EMS_Rotation::Rot0);
	GridPositionToMarketFurnitureDatas.Emplace(Rack3.GridPosition, Rack3);

	FMS_FurniturePositionData Rack4 = FMS_FurniturePositionData(11, FIntVector2(-6, 2), EMS_Rotation::Rot0);
	GridPositionToMarketFurnitureDatas.Emplace(Rack4.GridPosition, Rack4);

	FMS_FurniturePositionData Rack5 = FMS_FurniturePositionData(11, FIntVector2(-18, 7), EMS_Rotation::Rot0);
	GridPositionToMarketFurnitureDatas.Emplace(Rack5.GridPosition, Rack5);

	FMS_FurniturePositionData Rack6 = FMS_FurniturePositionData(11, FIntVector2(-14, 7), EMS_Rotation::Rot0);
	GridPositionToMarketFurnitureDatas.Emplace(Rack6.GridPosition, Rack6);
	
	FMS_FurniturePositionData Rack7 = FMS_FurniturePositionData(11, FIntVector2(-10, 7), EMS_Rotation::Rot0);
	GridPositionToMarketFurnitureDatas.Emplace(Rack7.GridPosition, Rack7);

	FMS_FurniturePositionData Rack8 = FMS_FurniturePositionData(11, FIntVector2(-6, 7), EMS_Rotation::Rot0);
	GridPositionToMarketFurnitureDatas.Emplace(Rack8.GridPosition, Rack8);
	
	FMS_FurniturePositionData Rack9 = FMS_FurniturePositionData(11, FIntVector2(-18, 12), EMS_Rotation::Rot0);
	GridPositionToMarketFurnitureDatas.Emplace(Rack9.GridPosition, Rack9);

	FMS_FurniturePositionData Rack10 = FMS_FurniturePositionData(11, FIntVector2(-14, 12), EMS_Rotation::Rot0);
	GridPositionToMarketFurnitureDatas.Emplace(Rack10.GridPosition, Rack10);
	
	FMS_FurniturePositionData Rack11 = FMS_FurniturePositionData(11, FIntVector2(-10, 12), EMS_Rotation::Rot0);
	GridPositionToMarketFurnitureDatas.Emplace(Rack11.GridPosition, Rack11);

	FMS_FurniturePositionData Rack12 = FMS_FurniturePositionData(11, FIntVector2(-6, 12), EMS_Rotation::Rot0);
	GridPositionToMarketFurnitureDatas.Emplace(Rack12.GridPosition, Rack12);

	FMS_FurniturePositionData Rack13 = FMS_FurniturePositionData(11, FIntVector2(-18, 17), EMS_Rotation::Rot0);
	GridPositionToMarketFurnitureDatas.Emplace(Rack13.GridPosition, Rack13);

	FMS_FurniturePositionData Rack14 = FMS_FurniturePositionData(11, FIntVector2(-14, 17), EMS_Rotation::Rot0);
	GridPositionToMarketFurnitureDatas.Emplace(Rack14.GridPosition, Rack14);
	
	
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
#endif
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
			MS_ERROR(TEXT("[%s] There is alreay Furniture at this grid position. [Grid Position : %d, %d]")
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
		ResetPlayerData();
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
		MS_ERROR(TEXT("SaveGameError"));
		MS_ENSURE(false);
	}
}
