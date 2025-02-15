// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Save/MS_SaveData.h"
#include "ContentsUtilities/MS_GameProcessDefine.h"
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

	void GetAllMarketFurnitureDatas(TMap<FIntVector2, FMS_LevelFurnitureSaveData>& aOutFurnitureDatas) const;
	bool GetMarketFurnitureData(const FIntVector2& aInGridPosition, FMS_LevelFurnitureSaveData& aOutFurnitureData) const;
	void AddFurnitureData(int32 aFurnitureTableId, const FIntVector2& aGridPosition, EMS_Rotation aRotation);
	void AddFurnitureData(FMS_LevelFurnitureSaveData aFurnitureData);
	void RemoveFurnitureData(FIntVector2 aGridPosition);

	void SetFurnitureSlotDatas(const FIntVector2& aGridPosition, const TArray<FMS_SlotData>& aSlotData);

	void GetAllItems(TMap<int32, int32>& aOutItems) const { aOutItems = Items; }
	int32 GetItemCount(int32 aItemId) const;

	
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
	
	UPROPERTY()
	TMap<FIntVector2, FMS_LevelFurnitureSaveData> GridPositionToMarketFurnitureDatas;

	UPROPERTY()
	TMap<int32, int32> Items;
};
