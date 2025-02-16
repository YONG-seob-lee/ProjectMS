// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MS_Define.h"
#include "ContentsUtilities/MS_AIDefine.h"
#include "MS_IssueTicketContainer.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_IssueTicket : public UObject
{
	GENERATED_BODY()

public:
	UMS_IssueTicket();
	
	void Initialize(EMS_IssueType aIssueType, TWeakObjectPtr<class UMS_UnitBase> aRequestUnit, int32 aRequestSlot);
	void Finalize();

	FORCEINLINE EMS_IssueType GetIssueType() const { return IssueType; }
	FORCEINLINE TWeakObjectPtr<class UMS_UnitBase> GetRequestUnit() const { return RequestUnit; }
	FORCEINLINE int32 GetRequestSlot() const { return RequestSlot; }
	FORCEINLINE TWeakObjectPtr<class UMS_StaffAIUnit> GetStaffUnit() const { return StaffUnit; }
	FORCEINLINE void SetStaffUnit(TWeakObjectPtr<class UMS_StaffAIUnit> aStaffUnit);

	bool IsSameIssue(EMS_IssueType aIssueType, MS_Handle aUnitHandle, int32 aRequestSlot) const;
	bool IsSameIssue(EMS_IssueType aIssueType, TWeakObjectPtr<class UMS_UnitBase> aRequestUnit, int32 aRequestSlot) const;
	bool IsSameIssue(const TWeakObjectPtr<UMS_IssueTicket> aOther) const;
	
	static bool AllowSameIssue(EMS_IssueType aIssueType);

private:
	UPROPERTY()
	EMS_IssueType IssueType;

	UPROPERTY()
	TWeakObjectPtr<class UMS_UnitBase> RequestUnit;

	UPROPERTY()
	int32 RequestSlot;

	UPROPERTY()
	TWeakObjectPtr<class UMS_StaffAIUnit> StaffUnit;
};

UCLASS()
class PROJECTMS_API UMS_IssueTicketContainer : public UObject
{
	GENERATED_BODY()

public:
	UMS_IssueTicketContainer();
	
	void Initialize();
	void Finalize();

	void RegisterIssueTicket(EMS_IssueType aIssueType, TWeakObjectPtr<class UMS_UnitBase> aRequestUnit = nullptr, int32 aSlotId = INDEX_NONE);

	void UnregisterAllIssueTickets();
	void UnregisterUnitIssueTickets(MS_Handle aUnitHandle);
	void UnregisterUnitSlotIssueTickets(MS_Handle aUnitHandle, int32 aSlotId);
	void UnregisterIssueTicket(TWeakObjectPtr<UMS_IssueTicket> aIssueTicket);

	void GetTypeIssueTickets(TArray<TWeakObjectPtr<UMS_IssueTicket>>& aOutTickets, EMS_IssueType aIssueType);
	void GetUnitIssueTickets(TArray<TWeakObjectPtr<UMS_IssueTicket>>& aOutTickets, MS_Handle aUnitHandle);
	void GetUnitIssueTickets(TArray<TWeakObjectPtr<UMS_IssueTicket>>& aOutTickets, MS_Handle aUnitHandle, int32 aSlotId);
	void GetIssueTickets(TArray<TWeakObjectPtr<UMS_IssueTicket>>& aOutTickets, EMS_IssueType aIssueType, MS_Handle aUnitHandle, int32 aSlotId);

	void RegisterIssueTicketStaff(TWeakObjectPtr<UMS_IssueTicket>& aTargetTicket, TWeakObjectPtr<class UMS_StaffAIUnit> aStaffUnit);
	
private:
	TArray<TObjectPtr<UMS_IssueTicket>> IssueTickets;
};
