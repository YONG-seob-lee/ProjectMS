// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UtilityFunctions.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UUtilityFunctions : public UObject
{
	GENERATED_BODY()

public:
	static UClass* GetClassByTablePathId(int32 aPathId);
};
