// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_SaveData.generated.h"

/**
 * 
 */
USTRUCT()
struct FMS_StorageSaveData
{
	GENERATED_BODY()

public:
	FMS_StorageSaveData()
	{
	}

	UPROPERTY()
	int32 ItemTableId;

	UPROPERTY()
	int32 ItemAmount;
};

USTRUCT()
struct FMS_LevelFurnitureSaveData
{
	GENERATED_BODY()

public:
	FMS_LevelFurnitureSaveData()
	{
	}

	UPROPERTY()
	int32 LevelId;

	UPROPERTY()
	FIntVector2 GridPosition;
	
	UPROPERTY()
	int32 FurnitureTableId;

	UPROPERTY()
	TArray<FMS_StorageSaveData> StorageData;
};