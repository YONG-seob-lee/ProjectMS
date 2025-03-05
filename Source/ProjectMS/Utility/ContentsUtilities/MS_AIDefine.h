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
	GoToWork = 2,
	GoHome = 3,
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
enum class EMS_StaffUIPriorityType : uint8
{
	PaymentFirst = 0,
	DisplayFirst = 1,
	ShelfFirst = 2,
	PaymentOnly = 3,
	DisplayOnly = 4,
	ShelfOnly = 5,

	EMS_StaffUIPriorityType_Max = 6
};


UENUM(BlueprintType)
enum class EMS_StaffActionState : uint8
{
	None = 0,
	Deactive = 1,

	// 물건 빼기
	Return_PickUp_SearchRequestUnit = 3,
	Return_PickUp_GoToRequestUnit = 4,
	Return_PickUp_InteractRequestUnit = 5,

	Return_Delivery_SearchTargets = 6,
	Return_Delivery_GoToTargetUnit = 7,
	Return_Delivery_InteractTargetUnit = 8,

	// 물건 채우기
	Add_PickUp_SearchTargets = 9,
	Add_PickUp_GoToTargetUnit = 10,
	Add_PickUp_InteractTargetUnit = 11,

	Add_Delivery_SearchRequestUnit = 12,
	Add_Delivery_GoToRequestUnit = 13,
	Add_Delivery_InteractRequestUnit = 14,

	// Storage 외의 타겟이 있는 행동
	NoStorage_SearchRequestUnit = 15,
	NoStorage_GoToRequestUnit = 16,
	NoStorage_InteractRequestUnit = 17,
	
	// Random Point로 이동
	None_SearchRandomPoint = 18,
	None_GoToRandomPoint = 19,

	// Idle
	None_Idle = 20,
	None_IdleAction = 21,

	// Spline으로 이동
	Spline_GoToWork = 22,
	Spline_GoHome = 23,

	// Payment
	Payment_Waiting,
	Payment_Doing,
};

UENUM(BlueprintType)
enum class EMS_CustomerActionType : uint8
{
	None = 0,
	GoToMarket = 2,
	GoHome = 3,
	PickUpItems = 4,
	Payment = 5,
};

UENUM(BlueprintType)
enum class EMS_CustomerActionState : uint8
{
	None = 0,
	DeActive = 1,

	// Spline으로 이동 (마켓 이동 및 회귀용)
	Spline_GoToMarket = 2,
	Spline_GoHome = 3,

	// PickUp
	PickUp_SearchTargets = 4,
	PickUp_GoToTargetUnit = 5,
	PickUp_InteractTargetUnit = 6,

	// Payment
	Payment_SearchTargets = 7,
	Payment_GoToTargetUnit = 8,
	Payment_BeforePayment = 9,
	Payment_MoveWithinCounter = 10,
	Payment_AfterPayment = 11,
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
		
		StaffUIPriorityType = EMS_StaffUIPriorityType::PaymentFirst;
		
		PriorityOfWorks = {EMS_StaffIssueType::Payment,
			EMS_StaffIssueType::ReturnItemsFromDisplay, EMS_StaffIssueType::AddItemsToDisplay,
			EMS_StaffIssueType::ReturnItemsFromShelf, EMS_StaffIssueType::AddItemsToShelf};
	}

	FMS_PlayerStaffData(int32 aStaffId)
		: StaffId(aStaffId), StaffIdTag(INDEX_NONE), FirstDateOfWork(FMS_GameDate(1, 1, 1))
	{
		WorkingDays.Empty();

		StaffUIPriorityType = EMS_StaffUIPriorityType::PaymentFirst;
		
		PriorityOfWorks = {EMS_StaffIssueType::Payment,
			EMS_StaffIssueType::ReturnItemsFromDisplay, EMS_StaffIssueType::AddItemsToDisplay,
			EMS_StaffIssueType::ReturnItemsFromShelf, EMS_StaffIssueType::AddItemsToShelf};
	}

	FMS_PlayerStaffData(int32 aStaffId, int32 aStaffIdTag)
	: StaffId(aStaffId), StaffIdTag(aStaffIdTag), FirstDateOfWork(FMS_GameDate(1, 1, 1))
	{
		WorkingDays.Empty();

		StaffUIPriorityType = EMS_StaffUIPriorityType::PaymentFirst;
		
		PriorityOfWorks = {EMS_StaffIssueType::Payment,
			EMS_StaffIssueType::ReturnItemsFromDisplay, EMS_StaffIssueType::AddItemsToDisplay,
			EMS_StaffIssueType::ReturnItemsFromShelf, EMS_StaffIssueType::AddItemsToShelf};
	}

	FMS_PlayerStaffData(int32 aStaffId, int32 aStaffIdTag, const FMS_GameDate& aFirstDateOfWork)
		: StaffId(aStaffId), StaffIdTag(aStaffIdTag), FirstDateOfWork(aFirstDateOfWork)
	{
		WorkingDays.Empty();

		StaffUIPriorityType = EMS_StaffUIPriorityType::PaymentFirst;
		
		PriorityOfWorks = {EMS_StaffIssueType::Payment,
			EMS_StaffIssueType::ReturnItemsFromDisplay, EMS_StaffIssueType::AddItemsToDisplay,
			EMS_StaffIssueType::ReturnItemsFromShelf, EMS_StaffIssueType::AddItemsToShelf};
	}

	FMS_PlayerStaffData(int32 aStaffId, int32 aStaffIdTag, const FMS_GameDate& aFirstDateOfWork, int32 aWorkDay)
		: StaffId(aStaffId), StaffIdTag(aStaffIdTag), FirstDateOfWork(aFirstDateOfWork), ExpirationDate(FMS_GameDate(aFirstDateOfWork, aWorkDay)), WorkDay(aWorkDay)
	{
		StaffUIPriorityType = EMS_StaffUIPriorityType::PaymentFirst;
		
		PriorityOfWorks = {EMS_StaffIssueType::Payment,
			EMS_StaffIssueType::ReturnItemsFromDisplay, EMS_StaffIssueType::AddItemsToDisplay,
			EMS_StaffIssueType::ReturnItemsFromShelf, EMS_StaffIssueType::AddItemsToShelf};
	}
	
	
	UPROPERTY()
	int32 StaffId;

	UPROPERTY()
	int32 StaffIdTag;	// StaffId #1, #2 ...

	UPROPERTY()
	EMS_StaffUIPriorityType StaffUIPriorityType;	// ToDo : PriorityOfWorks와 중복 데이터. 정리하자.
	
	UPROPERTY()
	TArray<EMS_StaffIssueType> PriorityOfWorks;

	UPROPERTY()
	FMS_GameDate FirstDateOfWork;

	UPROPERTY()
	FMS_GameDate ExpirationDate;

	UPROPERTY()
	int32 WorkDay = 0;
	
	UPROPERTY()
	int32 DailyPrice = 0;
	
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
	const FName StaffAction = TEXT("StaffAction");
	const FName StaffIssueType = TEXT("StaffIssueType");
	const FName StaffActionState = TEXT("StaffActionState");
}

namespace CustomerBoardKeyName
{
	const FName CustomerAction = TEXT("CustomerAction");
	const FName CustomerActionState = TEXT("CustomerActionState");
	const FName IsCustomerPickUpAllItem = TEXT("IsCustomerPickUpAllItem");
	const FName IsCustomerPutDownAllItems = TEXT("IsCustomerPutDownAllItems");
}

namespace SocketName
{
	const FName Equipment = TEXT("Equipment");
	const FName HeadItem = TEXT("HeadItem");
	const FName RightItem = TEXT("RightItem");
	const FName LeftItem = TEXT("LeftItem");
}
