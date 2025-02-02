// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "MS_Common.generated.h"

/**
 * 
 */
USTRUCT()
struct FMS_Common : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere)
	FString Contents = FString();
	UPROPERTY(EditAnywhere)
	int32 Parameter01 = 0;
	UPROPERTY(EditAnywhere)
	float Parameter02 = 0.f;
};
