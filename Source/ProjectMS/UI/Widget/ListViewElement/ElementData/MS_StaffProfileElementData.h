// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "MS_StaffProfileElementData.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_StaffProfileElementData : public UObject
{
	GENERATED_BODY()
public:
	FORCEINLINE void SetStaffId(int32 aStaffId) { StaffId = aStaffId; }

	FORCEINLINE int32 GetStaffId() const { return StaffId; }
private:
	int32 StaffId = INDEX_NONE;
};
