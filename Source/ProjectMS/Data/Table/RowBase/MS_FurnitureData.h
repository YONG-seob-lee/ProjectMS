// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_FurnitureData.generated.h"

/**
 * 
 */
USTRUCT()
struct FMS_FurnitureData : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	int32 FurnitureType = 0;
	UPROPERTY(EditAnywhere)
	int32 ZoneType = 0;
	UPROPERTY(EditAnywhere)
	int32 TemperatureType = 0;
	UPROPERTY(EditAnywhere)
	FName StandName = FName();
	UPROPERTY(EditAnywhere)
	int32 StandLv = 0;
	UPROPERTY(EditAnywhere)
	int32 SlotCount = 0;
	UPROPERTY(EditAnywhere)
	int32 Price = 0;
	UPROPERTY(EditAnywhere)
	int32 PathFile = 0;
	UPROPERTY(EditAnywhere)
	int32 ImagePath = 0;
	UPROPERTY(EditAnywhere)
	FString Desc = FString();
	UPROPERTY(EditAnywhere)
	float ArrangementOffsetX = 0;
	UPROPERTY(EditAnywhere)
	float ArrangementOffsetY = 0;
};
