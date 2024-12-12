// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_ResourceUnit.generated.h"

/**
 * 
 */
USTRUCT()
struct FMS_ResourceUnit : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere)
	int32 Base_Path = 0;
	UPROPERTY(EditAnywhere)
	int32 UnitType = 0;
	UPROPERTY(EditAnywhere)
	int32 GridPatternX = 0;
	UPROPERTY(EditAnywhere)
	int32 GridPatternY = 0;
};
