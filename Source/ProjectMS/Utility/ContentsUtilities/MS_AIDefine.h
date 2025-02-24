// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ContentsUtilities/MS_GameProcessDefine.h"
#include "MS_AIDefine.generated.h"


UENUM(BlueprintType)
enum class EMS_StaffActionType : uint8
{
	None = 0,
	Issue = 1,
	GoingWork = 2,
	GoingHome = 3,
	ChangeClothes = 4,
};

UENUM(BlueprintType)
enum class EMS_StaffIssueType : uint8
{
	None = 0,
	Payment = 1,
	ReturnItemsFromDisplay = 2,
	AddItemsToDisplay = 3,
	ReturnItemsFromShelf = 4,
	AddItemsToShelf = 5,
};

UENUM(BlueprintType)
enum class EMS_StaffActionProcess : uint8
{
	None = 0,
	Deactive = 1,

	Return_PickUp_SearchRequestUnit = 3,
	Return_PickUp_GoToRequestUnit = 4,
	Return_PickUp_InteractRequestUnit = 5,

	Return_Delivery_SearchTargets = 6,
	Return_Delivery_GoToTargetUnit = 7,
	Return_Delivery_InteractTargetUnit = 8,

	Add_PickUp_SearchTargets = 9,
	Add_PickUp_GoToTargetUnit = 10,
	Add_PickUp_InteractTargetUnit = 11,

	Add_Delivery_SearchRequestUnit = 12,
	Add_Delivery_GoToRequestUnit = 13,
	Add_Delivery_InteractRequestUnit = 14,
};

USTRUCT()
struct FMS_PlayerStaffData
{
	GENERATED_BODY()

public:
	FMS_PlayerStaffData()
		: StaffId(INDEX_NONE)
	{
		WorkingDays.Empty();

		// ToDo : Test를 위해 임시 배치
		PriorityOfWorks.Emplace(EMS_StaffIssueType::Payment);
		PriorityOfWorks.Emplace(EMS_StaffIssueType::ReturnItemsFromDisplay);
		PriorityOfWorks.Emplace(EMS_StaffIssueType::AddItemsToDisplay);
		PriorityOfWorks.Emplace(EMS_StaffIssueType::ReturnItemsFromShelf);
		PriorityOfWorks.Emplace(EMS_StaffIssueType::AddItemsToShelf);
	}

	FMS_PlayerStaffData(int32 aStaffId)
		: StaffId(aStaffId), FirstDateOfWork(FMS_GameDate(1, 1, 1))
	{
		WorkingDays.Empty();

		PriorityOfWorks.Emplace(EMS_StaffIssueType::Payment);
		PriorityOfWorks.Emplace(EMS_StaffIssueType::ReturnItemsFromDisplay);
		PriorityOfWorks.Emplace(EMS_StaffIssueType::AddItemsToDisplay);
		PriorityOfWorks.Emplace(EMS_StaffIssueType::ReturnItemsFromShelf);
		PriorityOfWorks.Emplace(EMS_StaffIssueType::AddItemsToShelf);
	}

	FMS_PlayerStaffData(int32 aStaffId, const FMS_GameDate& aFirstDateOfWork)
		: StaffId(aStaffId), FirstDateOfWork(aFirstDateOfWork)
	{
		WorkingDays.Empty();

		PriorityOfWorks.Emplace(EMS_StaffIssueType::Payment);
		PriorityOfWorks.Emplace(EMS_StaffIssueType::ReturnItemsFromDisplay);
		PriorityOfWorks.Emplace(EMS_StaffIssueType::AddItemsToDisplay);
		PriorityOfWorks.Emplace(EMS_StaffIssueType::ReturnItemsFromShelf);
		PriorityOfWorks.Emplace(EMS_StaffIssueType::AddItemsToShelf);
	}

	FMS_PlayerStaffData(int32 aStaffId, const FMS_GameDate& aFirstDateOfWork, int32 aWorkDay)
		: StaffId(aStaffId), FirstDateOfWork(aFirstDateOfWork), ExpirationDate(FMS_GameDate(aFirstDateOfWork, aWorkDay)), WorkDay(aWorkDay)
	{
		
		PriorityOfWorks.Emplace(EMS_StaffIssueType::Payment);
		PriorityOfWorks.Emplace(EMS_StaffIssueType::ReturnItemsFromDisplay);
		PriorityOfWorks.Emplace(EMS_StaffIssueType::AddItemsToDisplay);
		PriorityOfWorks.Emplace(EMS_StaffIssueType::ReturnItemsFromShelf);
		PriorityOfWorks.Emplace(EMS_StaffIssueType::AddItemsToShelf);
	}

	
	UPROPERTY()
	int32 StaffId;

	UPROPERTY()
	TArray<EMS_StaffIssueType> PriorityOfWorks;
	
	UPROPERTY()
	FMS_GameDate FirstDateOfWork;

	UPROPERTY()
	FMS_GameDate ExpirationDate;

	UPROPERTY()
	int32 WorkDay = 0;

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
	const FName CurrentIssueType = TEXT("CurrentIssueType");
	const FName CurrentActionProcess = TEXT("CurrentActionProcess");
}

namespace SocketName
{
	const FName Equipment = TEXT("Equipment");
}
