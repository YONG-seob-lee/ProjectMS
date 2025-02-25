// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_MarketAIUnit.h"
#include "ContentsUtilities/MS_AIDefine.h"
#include "MS_StaffAIUnit.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_StaffAIUnit : public UMS_MarketAIUnit
{
	GENERATED_BODY()

public:
	virtual void Initialize(MS_Handle aUnitHandle, EMS_UnitType aUnitType, int32 aTableId) override;
	virtual void Finalize() override;
	virtual void PostInitialize() override;
	virtual void Tick(float aDeltaTime) override;

	virtual void DestroyUnitActor() override;

protected:
	virtual int32 GetBlueprintPathId() const override;
	virtual UClass* GetBlueprintClass() const override;

public:
	bool FindNearestSpline();
	bool ReachSplineEndPoint() const;
	void GoingToWork() const;
	
public:
	FORCEINLINE const FMS_PlayerStaffData& GetPlayerStaffData() const { return PlayerStaffData; }
	FORCEINLINE void SetPlayerStaffData(const FMS_PlayerStaffData& aPlayerStaffData) { PlayerStaffData = aPlayerStaffData; }
	
	bool HasStaffAction() const;
	EMS_StaffActionType GetFirstStaffAction(TWeakObjectPtr<class UMS_IssueTicket>& OutIssueTicket);
	
	void RegisterNoneIssueStaffAction(EMS_StaffActionType aStaffActionType);
	void UnregisterNoneIssueStaffAction(EMS_StaffActionType aStaffActionType);

	void SearchAndRegisterIssueTicket();
	
private:
	TWeakObjectPtr<class UMS_IssueTicket> SearchIssueTicket() const;
	void RegisterAsIssueTicketStaff(TWeakObjectPtr<UMS_IssueTicket>& aTargetTicket);

public:
	void UnregisterAsIssueTicketStaff();
	
	void OnRegisteredAsIssueTicketStaff(TWeakObjectPtr<class UMS_IssueTicket> aIssueTicket);
	void OnUnregisteredAsIssueTicketStaff();

	TWeakObjectPtr<class UMS_FurnitureUnit> GetIssueTicketRequestFurnitrueUnit() const;
	bool GetIssueTicketTakeOutTargetUnits(TArray<TWeakObjectPtr<class UMS_FurnitureUnit>>& aOutTargetUnits) const;
	bool GetIssueTicketTakeInTargetUnits(TArray<TWeakObjectPtr<class UMS_FurnitureUnit>>& aOutTargetUnits) const;

	void TakeInItems();
	void TakeOutRequestItems();
	void TakeOutCurrentItems();

	TWeakObjectPtr<class UMS_FurnitureUnit> GetInteractableFurnitureUnit();

	
private:
	struct FMS_Staff* StaffTableData = nullptr;
	FMS_PlayerStaffData PlayerStaffData;
	
	TArray<EMS_StaffActionType> NoneIssueStaffActions = {};
	TWeakObjectPtr<UMS_IssueTicket> IssueTicket;

	TArray<FIntVector2> CacheTargetPositions = {};	// Blackboard에 Array형을 지원 안함
	TArray<FIntVector2> CachePath = {};

	bool bGotoWork = false;
	TWeakObjectPtr<class AMS_DuckSplineActor> DuckSplineActor = nullptr;
};
