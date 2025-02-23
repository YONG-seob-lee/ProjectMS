// Fill out your copyright notice in the Description page of Project Settings.

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
	
	void Initialize(EMS_StaffIssueType aIssueType, TWeakObjectPtr<class UMS_FurnitureUnit> aRequestFurnitureUnit, int32 aRequestSlot);
	void Finalize();

	FORCEINLINE EMS_StaffIssueType GetIssueType() const { return IssueType; }
	FORCEINLINE TWeakObjectPtr<class UMS_FurnitureUnit> GetRequestFurnitureUnit() const { return RequestFurnitureUnit; }
	FORCEINLINE int32 GetRequestSlot() const { return RequestSlot; }
	FORCEINLINE TWeakObjectPtr<class UMS_StaffAIUnit> GetStaffUnit() const { return StaffUnit; }
	FORCEINLINE void SetStaffUnit(TWeakObjectPtr<class UMS_StaffAIUnit> aStaffUnit);

	FORCEINLINE FMS_SlotData GetRequestFurnitureSlot() const;
	
	bool IsSameIssue(EMS_StaffIssueType aIssueType, MS_Handle aUnitHandle, int32 aRequestSlot) const;
	bool IsSameIssue(EMS_StaffIssueType aIssueType, TWeakObjectPtr<class UMS_FurnitureUnit> aRequestUnit, int32 aRequestSlot) const;
	bool IsSameIssue(const TWeakObjectPtr<UMS_IssueTicket> aOther) const;
	
	static bool AllowSameIssue(EMS_StaffIssueType aIssueType);

	FORCEINLINE bool IsEnabled() const { return bIsEnabled; }
	FORCEINLINE void SetIsEnabled(bool bEnabled) { bIsEnabled = bEnabled; }
	void UpdateEnabled();

private:
	UPROPERTY()
	EMS_StaffIssueType IssueType;

	UPROPERTY()
	TWeakObjectPtr<class UMS_FurnitureUnit> RequestFurnitureUnit;

	UPROPERTY()
	int32 RequestSlot;

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

	TWeakObjectPtr<UMS_IssueTicket> RegisterIssueTicket(EMS_StaffIssueType aIssueType, TWeakObjectPtr<class UMS_FurnitureUnit> aRequestUnit = nullptr, int32 aSlotId = INDEX_NONE);

	void UnregisterAllIssueTickets();
	void UnregisterUnitIssueTickets(MS_Handle aUnitHandle);
	void UnregisterUnitIssueTickets(TWeakObjectPtr<class UMS_FurnitureUnit> aUnitHandle);
	void UnregisterUnitSlotIssueTickets(MS_Handle aUnitHandle, int32 aSlotId);
	void UnregisterUnitSlotIssueTickets(TWeakObjectPtr<class UMS_FurnitureUnit> aFurnitureUnit, int32 aSlotId);
	bool UnregisterIssueTicket(TWeakObjectPtr<UMS_IssueTicket> aIssueTicket);

	void GetTypeIssueTickets(TArray<TWeakObjectPtr<UMS_IssueTicket>>& aOutTickets, EMS_StaffIssueType aIssueType);
	void GetUnitIssueTickets(TArray<TWeakObjectPtr<UMS_IssueTicket>>& aOutTickets, MS_Handle aUnitHandle);
	void GetUnitIssueTickets(TArray<TWeakObjectPtr<UMS_IssueTicket>>& aOutTickets, MS_Handle aUnitHandle, int32 aSlotId);
	void GetIssueTickets(TArray<TWeakObjectPtr<UMS_IssueTicket>>& aOutTickets, EMS_StaffIssueType aIssueType, MS_Handle aUnitHandle, int32 aSlotId);

	void RegisterIssueTicketStaff(TWeakObjectPtr<UMS_IssueTicket>& aTargetTicket, TWeakObjectPtr<class UMS_StaffAIUnit> aStaffUnit);

	void UpdateAllZoneStorageIssueTicketsEnabled(EMS_ZoneType aZoneType);

	
private:
	UPROPERTY()
	TArray<TObjectPtr<UMS_IssueTicket>> IssueTickets;
};
