// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MathUtility/MS_MathUtility.h"
#include "ContentsUtilities/MS_ItemDefine.h"
#include "MS_SaveData.generated.h"

/**
 * 
 */
USTRUCT()
struct FMS_LevelFurnitureSaveData
{
	GENERATED_BODY()

public:
	FMS_LevelFurnitureSaveData()
	{
	}

	FMS_LevelFurnitureSaveData(int32 aFurnitureTableId, FIntVector2 aGridPosition,
	EMS_Rotation aRotation)
		: FurnitureTableId(aFurnitureTableId), GridPosition(aGridPosition), Rotation(aRotation)
	{
		SlotDatas.Empty();
	}
	
	UPROPERTY()
	int32 FurnitureTableId;

	UPROPERTY()
	FIntVector2 GridPosition;
	
	UPROPERTY()
	EMS_Rotation Rotation;

	UPROPERTY()
	TArray<FMS_SlotData> SlotDatas;
};