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

UENUM()
enum class EMS_TemperatureType : uint8
{
	Undefined = 0,
	Constant,
	Refrigeration,
	Freezing
};