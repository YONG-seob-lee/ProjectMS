// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ContentsUtilities/MS_GameProcessDefine.h"
#include "MathUtility/MS_MathUtility.h"
#include "MS_AIDefine.generated.h"

UENUM()
enum class EMS_ActionType
{
	None = 0,
	PersonalAction = 1,
	Issue = 2,
};

UENUM()
enum class EMS_PersonalActionType
{
	None = 0,
	ChangeClothes = 1,
};

UENUM()
enum class EMS_IssueType
{
	None = 0,
	Payment = 1,
	RemoveItemsFromDisplay = 2,
	AddItemsToDisplay = 3,
	RemoveItemsFromShelf = 4,
	AddItemsToShelf = 5,
};

USTRUCT()
struct FMS_StaffData
{
	GENERATED_BODY()

public:
	FMS_StaffData()
		: StaffId(INDEX_NONE)
	{
		WorkingDays.Empty();
	}

	FMS_StaffData(int32 aStaffId)
		: StaffId(aStaffId), FirstDateOfWork(FMS_GameDate(1, 1, 1))
	{
		WorkingDays.Empty();
	}

	FMS_StaffData(int32 aStaffId, const FMS_GameDate& aFirstDateOfWork)
		: StaffId(aStaffId), FirstDateOfWork(aFirstDateOfWork)
	{
		WorkingDays.Empty();
	}
	
	UPROPERTY()
	int32 StaffId;

	UPROPERTY()
	TArray<EMS_IssueType> PriorityOfWoks;
	
	UPROPERTY()
	FMS_GameDate FirstDateOfWork;

	UPROPERTY()
	TArray<EMS_DayOfWeek> WorkingDays;
};