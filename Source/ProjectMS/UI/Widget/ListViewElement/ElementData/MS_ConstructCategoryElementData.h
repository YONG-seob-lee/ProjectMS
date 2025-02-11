// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_ConstructCategoryElementData.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_ConstructCategoryElementData : public UObject
{
	GENERATED_BODY()
public:
	FORCEINLINE void SetZoneType(int32 aZoneType) { ZoneType = aZoneType; }
	FORCEINLINE int32 GetZoneType() const { return ZoneType; }

private:
	int32 ZoneType = 0;
};
