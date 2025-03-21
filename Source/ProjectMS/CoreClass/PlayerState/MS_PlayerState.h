// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "ContentsUtilities/MS_GameProcessDefine.h"
#include "ContentsUtilities/MS_LevelDefine.h"
#include "ContentsUtilities/MS_AIDefine.h"
#include "Manager_Client/MS_ScheduleManager.h"
#include "MS_PlayerState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API AMS_PlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	AMS_PlayerState();

	virtual void PreInitializeComponents() override;

	const FMS_GameDate& GetGameDate() const { return GameDate; }
	void SetGameDate(FMS_GameDate aGameDate) { GameDate = aGameDate; }
	
	const TArray<int32>& GetOpenedZoneIds();
	int32 GetOpenedZoneCount() const;
	void AddOpenedZoneId(int32 aZoneId);

	// Money
	void SettleMoney(int32 aEarnMoney);

	// Items
	void OrderItem(TMap<int32, int32>& aOrderItems);
	FORCEINLINE void GetOrderItems(TMap<int32, int32>& aOrderItems) const { aOrderItems = OrderItems; }
	void OrganizeItems();

	FORCEINLINE void GetAllItems(TMap<int32, int32>& aItems) const
	{
		aItems = Items;
	}
	
	// Furniture
	void OrderFurniture(const TMap<int32, int32>& aOrderFurnitures);
	void OrganizeFurniture();
	FORCEINLINE void GetOrderFurnitures(TMap<int32, int32>& aOrderFurnitures) const { aOrderFurnitures = OrderFurnitures; }

	FORCEINLINE void GetAllFurnitureDatas(TMap<FIntVector2, FMS_FurniturePositionData>& aOutFurnitureDatas) const
	{
		aOutFurnitureDatas = GridPositionToMarketFurnitureDatas;
	}
	
	void SetFurnitureSlotDatas(const FIntVector2& aGridPosition, const TArray<FMS_SlotData>& aSlotData);
	void SaveFurniturePositionDatas(TMap<FIntVector2, FMS_FurniturePositionData> aGridPositionToMarketFurnitureDatas);
	
	// Staff
	void RegisterStaff(int32 aStaffId, int32 aWorkDay);
	void RegisterStaffPriorityOfWorks(int32 aStaffId, int32 aStaffIdTag, const TArray<EMS_StaffIssueType>& aPriorityOfWorks, EMS_StaffUIPriorityType aStaffUIPriorityType);
	const TArray<FMS_PlayerStaffData>& GetStaffDatas() const { return StaffDatas; }

	void WriteDiary(const FMS_SettlementSheet& Sheet);
	FORCEINLINE TArray<FMS_SettlementSheet>& GetDiary() { return Diary; }

	void ResetPlayerData();
	void InitDefaultPlayerData();
	void InitDesignedPlayerData1();
	
	void InitPlayerData();
	void SavePlayerData();

private:
	FString SaveSlotName;

	UPROPERTY()
	bool bInitDefaultData;

	UPROPERTY()
	FMS_GameDate GameDate;
	
	UPROPERTY()
	TArray<int32> OpenedZoneIds;

	// Money
	TMap<int32, int32> Money;
	
	// Items
	UPROPERTY()
	TMap<int32, int32> Items;

	UPROPERTY()
	TMap<int32, int32> OrderItems;

	// Furniture
	UPROPERTY()
	TMap<FIntVector2, FMS_FurniturePositionData> GridPositionToMarketFurnitureDatas;
		
	UPROPERTY()
	TMap<int32, int32> Furnitures;
	
	UPROPERTY()
	TMap<int32, int32> OrderFurnitures;
	
	//Staff
	UPROPERTY()
	TArray<FMS_PlayerStaffData> StaffDatas;

	UPROPERTY()
	TArray<FMS_SettlementSheet> Diary;
};
