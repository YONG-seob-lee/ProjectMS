// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_Item.generated.h"

/**
 * 
 */
USTRUCT()
struct FMS_Item : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	int32 Index = 0;
	UPROPERTY(EditAnywhere)
	int32 ItemType = 0;
	UPROPERTY(EditAnywhere)
	FName ItemName = FName();
	UPROPERTY(EditAnywhere)
	int32 StorageType = 0;
	UPROPERTY(EditAnywhere)
	int32 TakeMinCount = 0;
	UPROPERTY(EditAnywhere)
	int32 PriceMin = 0;
	UPROPERTY(EditAnywhere)
	int32 PriceMax = 0;
	UPROPERTY(EditAnywhere)
	int32 PathFile = 0;
};
