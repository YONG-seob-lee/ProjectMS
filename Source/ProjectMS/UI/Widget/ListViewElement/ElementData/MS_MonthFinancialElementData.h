﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "MS_MonthFinancialElementData.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_MonthFinancialElementData : public UObject
{
	GENERATED_BODY()
	
public:	
	FORCEINLINE void SetMonth(int32 aMonth) { Month = aMonth; }
	FORCEINLINE void AddCostBuildingStorage(int32 aCostBuildingStorage) { CostBuildingStorage += aCostBuildingStorage; }
	FORCEINLINE void AddMaintenanceCostMart(int32 aMaintenanceCostMart) { MaintenanceCostMart += aMaintenanceCostMart; }
	FORCEINLINE void AddLandPurchaseNumber(int32 aLandPurchasesNumber) { LandPurchasesNumber += aLandPurchasesNumber; }
	FORCEINLINE void AddAverageAmount(int32 aAverageAmount, int32 aLastDay)
	{
		AverageAmount = aAverageAmount;
		LastDay = aLastDay;
	}
	FORCEINLINE void AddShelfCapacity(int32 aShelfCapacity) { ShelfCapacity += aShelfCapacity; }
	FORCEINLINE void AddStaffSalary(int32 aStaffSalary) { StaffSalary += aStaffSalary; }
	FORCEINLINE void AddLoanInterest(int32 aLoanInterest) { LoanInterest += aLoanInterest; }

	FORCEINLINE int32 GetMonth() const { return Month; }
	FORCEINLINE int32 GetCostBuildingStorage() const { return CostBuildingStorage; }
	FORCEINLINE int32 GetMaintenanceCostMart() const { return MaintenanceCostMart; }
	FORCEINLINE int32 GetLandPurchasesNumber() const { return LandPurchasesNumber; }
	FORCEINLINE int32 GetAverageAmount() const
	{
		
		return AverageAmount / LastDay;
	}
	FORCEINLINE int32 GetShelfCapacity() const { return ShelfCapacity; }
	FORCEINLINE int32 GetStaffSalary() const { return StaffSalary; }
	FORCEINLINE int32 GetLoanInterest() const { return LoanInterest; }
	
private:
	int32 Month = 0;
	int32 CostBuildingStorage = 0;
	int32 MaintenanceCostMart = 0;
	int32 LandPurchasesNumber = 0;
	int32 AverageAmount = 0;
	int32 LastDay = 0;
	int32 ShelfCapacity = 0;
	int32 StaffSalary = 0;
	int32 LoanInterest = 0;
};
