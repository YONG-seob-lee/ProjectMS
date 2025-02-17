// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ContentsUtilities/MS_GameProcessDefine.h"
#include "MS_AIDefine.generated.h"

UENUM()
enum class EMS_ActionType : uint8
{
	None = 0,
	PersonalAction = 1,
	Issue = 2,
};

UENUM()
enum class EMS_PersonalActionType : uint8
{
	None = 0,
	ChangeClothes = 1,
};

UENUM()
enum class EMS_IssueType : uint8
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
	const FName SelectedPersonalAction = TEXT("SelectedPersonalAction");
}