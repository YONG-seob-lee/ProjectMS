﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ContentsUtilities/MS_GameProcessDefine.h"
#include "ContentsUtilities/MS_LevelDefine.h"
#include "ContentsUtilities/MS_AIDefine.h"
#include "Manager_Client/MS_ScheduleManager.h"
#include "MS_PlayerData.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_PlayerData : public USaveGame
{
	GENERATED_BODY()

public:
	UMS_PlayerData();

	UPROPERTY()
	bool bInitDefaultData;

	UPROPERTY()
	FMS_GameDate GameDate;
	
	UPROPERTY()
	TArray<int32> OpenedZoneIds;

	UPROPERTY()
	TArray<FMS_FurniturePositionData> MarketFurnitureDatas;

	UPROPERTY()
	TMap<int32, int32> Money;
	
	UPROPERTY()
	TMap<int32, int32> Items;

	UPROPERTY()
	TMap<int32, int32>OrderItems;

	UPROPERTY()
	TMap<int32, int32> Furnitures;
	
	UPROPERTY()
	TMap<int32, int32> OrderFurnitures;
	
	UPROPERTY()
	TArray<FMS_PlayerStaffData> StaffDatas;

	UPROPERTY()
	TArray<FMS_SettlementSheet> Diary;
};
