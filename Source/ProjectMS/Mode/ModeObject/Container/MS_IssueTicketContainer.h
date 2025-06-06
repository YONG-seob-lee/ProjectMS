﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MS_Define.h"
#include "ContentsUtilities/MS_AIDefine.h"
#include "ContentsUtilities/MS_LevelDefine.h"
#include "ContentsUtilities/MS_ItemDefine.h"
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
	
	void Initialize(EMS_StaffIssueType aIssueType, TWeakObjectPtr<class UMS_UnitBase> aRequestUnit, int32 aRequestSlot);
	void Finalize();

	FORCEINLINE EMS_StaffIssueType GetIssueType() const { return IssueType; }
	FORCEINLINE TWeakObjectPtr<class UMS_UnitBase> GetRequestUnit() const { return RequestUnit; }
	FORCEINLINE int32 GetRequestSlotId() const { return RequestSlotId; }
	FORCEINLINE TWeakObjectPtr<class UMS_StaffAIUnit> GetStaffUnit() const { return StaffUnit; }
	void SetStaffUnit(TWeakObjectPtr<class UMS_StaffAIUnit> aStaffUnit);

	void ChangeRequestUnitToStaffUnit(int32 aStaffSlotId = 0);	// 가구 유닛에서 아이템을 빼면서 가구 유닛이 이슈랑 상관없어지면 스태프에게 일임하여 이슈가 사라지는 것을 방지

	FMS_SlotData GetRequestSlotData() const;
	
	bool IsSameIssue(EMS_StaffIssueType aIssueType, MS_Handle aUnitHandle, int32 aRequestSlot) const;
	bool IsSameIssue(EMS_StaffIssueType aIssueType, TWeakObjectPtr<class UMS_UnitBase> aRequestUnit, int32 aRequestSlot) const;
	bool IsSameIssue(const TWeakObjectPtr<UMS_IssueTicket> aOther) const;
	
	static bool AllowSameIssue(EMS_StaffIssueType aIssueType);

	FORCEINLINE bool IsEnabled() const { return bIsEnabled; }
	FORCEINLINE void SetIsEnabled(bool bEnabled) { bIsEnabled = bEnabled; }
	void UpdateEnabled();

private:
	UPROPERTY()
	EMS_StaffIssueType IssueType;

	UPROPERTY()
	TWeakObjectPtr<class UMS_UnitBase> RequestUnit;

	UPROPERTY()
	int32 RequestSlotId;

	UPROPERTY()
	TWeakObjectPtr<class UMS_StaffAIUnit> StaffUnit;
	
	UPROPERTY()
	bool bIsEnabled = true;
};

UCLASS()
class PROJECTMS_API UMS_IssueTicketContainer : public UObject
{
	GENERATED_BODY()

public:
	UMS_IssueTicketContainer();
	
	void Initialize();
	void Finalize();

	TWeakObjectPtr<UMS_IssueTicket> RegisterIssueTicket(EMS_StaffIssueType aIssueType, TWeakObjectPtr<class UMS_UnitBase> aRequestUnit = nullptr, int32 aSlotId = INDEX_NONE);

	void UnregisterAllIssueTickets();
	void UnregisterUnitIssueTickets(MS_Handle aUnitHandle);
	void UnregisterUnitIssueTickets(TWeakObjectPtr<class UMS_UnitBase> aUnitHandle);
	void UnregisterUnitSlotIssueTickets(MS_Handle aUnitHandle, int32 aSlotId);
	void UnregisterUnitSlotIssueTickets(TWeakObjectPtr<class UMS_UnitBase> aRequestUnit, int32 aSlotId);
	bool UnregisterIssueTicket(TWeakObjectPtr<UMS_IssueTicket> aIssueTicket);

	void GetTypeIssueTickets(TArray<TWeakObjectPtr<UMS_IssueTicket>>& aOutTickets, EMS_StaffIssueType aIssueType, bool NoneStaffOnly = false, bool bEnableOnly = false);
	void GetUnitIssueTickets(TArray<TWeakObjectPtr<UMS_IssueTicket>>& aOutTickets, MS_Handle aUnitHandle, bool NoneStaffOnly = false, bool bEnableOnly = false);
	void GetUnitIssueTickets(TArray<TWeakObjectPtr<UMS_IssueTicket>>& aOutTickets, MS_Handle aUnitHandle, int32 aSlotId, bool NoneStaffOnly = false, bool bEnableOnly = false);
	void GetIssueTickets(TArray<TWeakObjectPtr<UMS_IssueTicket>>& aOutTickets, EMS_StaffIssueType aIssueType, MS_Handle aUnitHandle, int32 aSlotId);

	TWeakObjectPtr<class UMS_IssueTicket> SearchStaffIssueTicket(TWeakObjectPtr<class UMS_StaffAIUnit> aStaffUnit);
	TWeakObjectPtr<class UMS_IssueTicket> SearchStaffIssueTicket(const FMS_PlayerStaffData& aPlayerStaffData, const FIntVector2& aStaffGridPosition);
	void RegisterIssueTicketStaff(TWeakObjectPtr<UMS_IssueTicket> aTargetTicket, TWeakObjectPtr<class UMS_StaffAIUnit> aStaffUnit);
	void UnregisterIssueTicketStaff(TWeakObjectPtr<class UMS_IssueTicket> aTargetTicket);
	
	void UpdateAllZoneStorageIssueTicketsEnabled(EMS_ZoneType aZoneType);
	void UpdateIssueTicketsEnabled(TWeakObjectPtr<UMS_IssueTicket> aTargetTicket);

	
private:
	UPROPERTY()
	TArray<TObjectPtr<UMS_IssueTicket>> IssueTickets;
};
