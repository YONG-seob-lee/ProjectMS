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
	FString Directory = FString();
};
