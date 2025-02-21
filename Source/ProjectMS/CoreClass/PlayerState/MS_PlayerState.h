// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "ContentsUtilities/MS_GameProcessDefine.h"
#include "ContentsUtilities/MS_LevelDefine.h"
#include "ContentsUtilities/MS_AIDefine.h"
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
	void AddOpenedZoneId(int32 aZoneId);

	// Items
	void OrderItem(TMap<int32, int32>& aOrderItems);
	void OrganizeItems();

	// Furniture
	void OrderFurniture(const TMap<int32, int32>& aOrderFurnitures);
	void OrganizeFurniture();

	void SetFurnitureSlotDatas(const FIntVector2& aGridPosition, const TArray<FMS_SlotData>& aSlotData);
	void SaveFurniturePositionDatas(TMap<FIntVector2, FMS_FurniturePositionData> aGridPositionToMarketFurnitureDatas);
	
	// Staff
	void RegisterStaff(int32 StaffId, int32 WorkDay);
	const TArray<FMS_StaffData>& GetStaffDatas() const { return StaffDatas; }

	
	void InitDefaultPlayerData();
	
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
	
	//Items
	UPROPERTY()
	TMap<int32, int32> Items;

	UPROPERTY()
	TMap<int32, int32> OrderItems;

	//Furniture
	UPROPERTY()
	TMap<FIntVector2, FMS_FurniturePositionData> GridPositionToMarketFurnitureDatas;
		
	UPROPERTY()
	TMap<int32, int32> Furnitures;
	
	UPROPERTY()
	TMap<int32, int32> OrderFurnitures;
	
	//Staff
	UPROPERTY()
	TArray<FMS_StaffData> StaffDatas;
};
