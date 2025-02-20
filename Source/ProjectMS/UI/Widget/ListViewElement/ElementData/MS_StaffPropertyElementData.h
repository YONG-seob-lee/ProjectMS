// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ContentsUtilities/MS_GameProcessDefine.h"

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
	FORCEINLINE void SetWorkDay(int32 aWorkDay) { WorkDay = aWorkDay; }
	FORCEINLINE void SetHP(int32 aHP) { HP = aHP; }
	FORCEINLINE void SetCondition(int32 aCondition) { Condition = aCondition; }
	FORCEINLINE void SetFeeling(int32 aFeeling) { Feeling = aFeeling; }
	FORCEINLINE void SetFirstDateOfWork(FMS_GameDate aFirstDate) { FirstDateOfWork = aFirstDate; }
	FORCEINLINE void SetExpirationDate(FMS_GameDate aExpireDate) { ExpirationDate = aExpireDate;}

	FORCEINLINE int32 GetStaffId() const { return StaffId; }
	FORCEINLINE int32 GetWorkDay() const { return WorkDay; }
	FORCEINLINE int32 GetHP() const { return HP; }
	FORCEINLINE int32 GetCondition() const { return Condition; }
	FORCEINLINE int32 GetFeeling() const { return Feeling; }
	FORCEINLINE FMS_GameDate& GetFirstDateOfWork() { return FirstDateOfWork; }
	FORCEINLINE FMS_GameDate& GetExpirationDate() { return ExpirationDate; }

private:
	int32 StaffId = INDEX_NONE;
	int32 WorkDay = 0;
	int32 HP = 100;
	int32 Condition = 100;
	int32 Feeling = 0;
	FMS_GameDate FirstDateOfWork = FMS_GameDate();
	FMS_GameDate ExpirationDate = FMS_GameDate();
};
