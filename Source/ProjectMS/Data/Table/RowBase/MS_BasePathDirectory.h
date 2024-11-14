// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_BasePathDirectory.generated.h"
    
USTRUCT()
struct FMS_BasePathDirectory: public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere)
	int32 Id = 0;
	UPROPERTY(EditAnywhere)
	FString Directory = FString();
};
