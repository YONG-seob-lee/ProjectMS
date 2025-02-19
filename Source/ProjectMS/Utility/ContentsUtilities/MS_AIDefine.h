// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ContentsUtilities/MS_GameProcessDefine.h"
#include "MS_AIDefine.generated.h"


UENUM()
enum class EMS_StaffActionType : uint8
{
	None = 0,
	Issue = 1,
	GoingWork = 2,
	GoingHome = 3,
	ChangeClothes = 4,
};

UENUM()
enum class EMS_StaffIssueType : uint8
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
	TArray<EMS_StaffIssueType> PriorityOfWoks;
	
	UPROPERTY()
	FMS_GameDate FirstDateOfWork;

	UPROPERTY()
	TArray<EMS_DayOfWeek> WorkingDays;
};

// Board Key Name
namespace OutsideBoardKeyName
{
	const FName bFinishedIdleAnimation = TEXT("bFinishedIdleAnimation");
	const FName RemainIdleTime = TEXT("RemainIdleTime");
	const FName RemainWalkTime = TEXT("RemainWalkTime");
	const FName RemainWalkToMarketTime = TEXT("RemainWalkToMarketTime");
	const FName MarketFront = TEXT("MarketFront");
}

namespace StaffBoardKeyName
{
	const FName SelectedStaffAction = TEXT("SelectedStaffAction");
}