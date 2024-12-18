// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_SaleStand.generated.h"

/**
 * 
 */
USTRUCT()
struct FMS_SaleStand : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	int32 Index = 0;
	UPROPERTY(EditAnywhere)
	int32 StorageType = 0;
	UPROPERTY(EditAnywhere)
	FName StandName = FName();
	UPROPERTY(EditAnywhere)
	int32 StandLv = 0;
	UPROPERTY(EditAnywhere)
	int32 FloorCount = 0;
	UPROPERTY(EditAnywhere)
	int32 SlotCount = 0;
	UPROPERTY(EditAnywhere)
	int32 Price = 0;
	UPROPERTY(EditAnywhere)
	int32 PathFile = 0;
};
