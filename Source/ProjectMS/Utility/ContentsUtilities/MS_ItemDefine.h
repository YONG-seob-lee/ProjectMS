// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_ItemDefine.generated.h"

/**
 * 
 */
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
	Furniture
};

UENUM()
enum class EMS_TemperatureType : uint8
{
	Undefined = 0,
	Constant,
	Refrigeration,
	Freezing
};

UENUM()
enum class EMS_ItemSlotUIType : uint8
{
	None,
	StorageRequestStatus,
	StorageCurrentStatus,
	Requestable
};

USTRUCT()
struct FMS_SlotData
{
	GENERATED_BODY()

public:
	FMS_SlotData()
		: RequestItemTableId(INDEX_NONE), CurrentItemTableId(INDEX_NONE), CurrentItemCount(0)
	{
	}
	
	FMS_SlotData(int32 aRequestItemTableId, int32 aCurrentItemTableId, int32 aCurrentItemCount)
		: RequestItemTableId(aRequestItemTableId), CurrentItemTableId(aCurrentItemTableId), CurrentItemCount(aCurrentItemCount)
	{
	}
	
	void Empty()
	{
		RequestItemTableId = INDEX_NONE;
		CurrentItemTableId = INDEX_NONE;
		CurrentItemCount = 0;
	}
	
	UPROPERTY()
	int32 RequestItemTableId;
	
	UPROPERTY()
	int32 CurrentItemTableId;

	UPROPERTY()
	int32 CurrentItemCount;
};

namespace EquipmentName
{
	const FName BigBox = TEXT("BIGBOX");
	const FName SmallBox = TEXT("SMALLBOX");
	const FName StaffSkinA = TEXT("StaffSkinA");
	const FName StaffSkinB = TEXT("StaffSkinB");
	const FName StaffSkinC = TEXT("StaffSkinC");
}

namespace CommonItemTableKeyName
{
	const FString BIGBOX_COUNT = TEXT("BIGBOX_COUNT");
	const FString SMALLBOX_COUNT = TEXT("SMALLBOX_COUNT");
}