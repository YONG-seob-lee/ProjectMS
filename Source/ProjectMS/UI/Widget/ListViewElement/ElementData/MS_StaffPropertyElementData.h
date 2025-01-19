// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "MS_StaffPropertyElementData.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_StaffPropertyElementData : public UObject
{
	GENERATED_BODY()
public:
	FORCEINLINE void SetStaffId(int32 aStaffId) { StaffId = aStaffId; }
	FORCEINLINE void SetHP(int32 aHP) { HP = aHP; }
	FORCEINLINE void SetCondition(int32 aCondition) { Condition = aCondition; }
	FORCEINLINE void SetFeeling(int32 aFeeling) { Feeling = aFeeling; }
	FORCEINLINE void SetExpirationDate(int32 aExpirationMonth, int32 aExpirationDay) { ExpirationMonth = aExpirationMonth; ExpirationDay = aExpirationDay; }

	FORCEINLINE int32 GetStaffId() const { return StaffId; }
	FORCEINLINE int32 GetHP() const { return HP; }
	FORCEINLINE int32 GetCondition() const { return Condition; }
	FORCEINLINE int32 GetFeeling() const { return Feeling; }
	FORCEINLINE int32 GetExpirationMonth() const { return ExpirationMonth; }
	FORCEINLINE int32 GetExpirationDay() const { return ExpirationDay; }
private:
	int32 StaffId = INDEX_NONE;
	int32 HP = 100;
	int32 Condition = 100;
	int32 Feeling = 0;
	int32 ExpirationMonth = 0;
	int32 ExpirationDay = 0;
};
