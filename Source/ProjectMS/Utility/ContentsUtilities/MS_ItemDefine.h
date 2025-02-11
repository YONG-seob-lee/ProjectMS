// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_ItemDefine.generated.h"

/**
 * 
 */
USTRUCT()
struct FMS_SlotData
{
	GENERATED_BODY()

public:
	FMS_SlotData()
	{
	}
	
	UPROPERTY()
	int32 RequestItemTableId;
	
	UPROPERTY()
	int32 CurrentItemTableId;

	UPROPERTY()
	int32 CurrentItemAmount;
};

// 임시
struct FPacketItemDatas
{
public:
	int32 ItemId = 0;
	FVector Vector;
	FRotator Rotator;
};

UENUM()
enum class EMS_ItemType : uint8
{
	Undefined = 0,
	Money,
	Cash,
	Fruit,
	Fish,
	Beverage,
	Frozen,
	Snack,
	FrozenSnack,
	Storage
};

UENUM(BlueprintType)
enum class EMS_StorageType : uint8
{
	Undefined = 0,
	Display			UMETA(DisplayName = "Display"),
	Shelf			UMETA(DisplayName = "Shelf"),
	Pallet			UMETA(DisplayName = "Pallet"),
	Counter			UMETA(DisplayName = "Counter"),
};

UENUM()
enum class EMS_TemperatureType : uint8
{
	Undefined = 0,
	Constant,
	Refrigeration,
	Freezing
};