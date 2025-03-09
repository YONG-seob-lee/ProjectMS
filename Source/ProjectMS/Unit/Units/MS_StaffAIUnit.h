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
	FORCEINLINE TWeakObjectPtr<class AMS_DuckSplineActor> GetDuckSplineActor() const { return DuckSplineActor; }
	bool FindNearestSpline();
	bool ReachSplineEndPoint() const;
	bool ReachSplineStartPoint() const;
	void GoingToWork() const;
	void GoingToHome() const;
	
public:
	FORCEINLINE const FMS_PlayerStaffData& GetPlayerStaffData() const { return PlayerStaffData; }
	void SetPlayerStaffData(const FMS_PlayerStaffData& aPlayerStaffData);
	void UpdateSkin();

	void UpdateStaffPriorityOfWorks(EMS_StaffUIPriorityType aStaffUIPriorityType);
	
	bool HasStaffAction() const;
	EMS_StaffActionType GetFirstStaffAction(TWeakObjectPtr<class UMS_IssueTicket>& OutIssueTicket);
	
	void RegisterNoneIssueStaffAction(EMS_StaffActionType aStaffActionType);
	void UnregisterNoneIssueStaffAction(EMS_StaffActionType aStaffActionType);

	void SearchAndRegisterIssueTicket();
	
private:
	TWeakObjectPtr<class UMS_IssueTicket> SearchIssueTicket() const;
	bool UnregisterIssueTicket();
	
public:
	void RegisterAsIssueTicketStaff(TWeakObjectPtr<UMS_IssueTicket>& aTargetTicket);
	void UnregisterAsIssueTicketStaff();
	
	void OnRegisteredAsIssueTicketStaff(TWeakObjectPtr<class UMS_IssueTicket> aIssueTicket);
	void OnUnregisteredAsIssueTicketStaff();

	TWeakObjectPtr<class UMS_UnitBase> GetIssueTicketRequestUnit();
	bool GetIssueTicketPickUpTargetUnits(TArray<TWeakObjectPtr<class UMS_StorageUnit>>& aOutTargetUnits);
	bool GetIssueTicketDeliveryTargetUnits(TArray<TWeakObjectPtr<class UMS_StorageUnit>>& aOutTargetUnits);

	bool DeliveryItems();
	bool PickUpRequestItems();
	bool PickUpCurrentItems();

protected:
	virtual void OnChangeCurrentSlotDatas() override;

	
private:
	struct FMS_Staff* StaffTableData = nullptr;
	FMS_PlayerStaffData PlayerStaffData;
	
	TArray<EMS_StaffActionType> NoneIssueStaffActions = {};
	TWeakObjectPtr<UMS_IssueTicket> IssueTicket;

	TArray<FIntVector2> CacheTargetPositions = {};	// Blackboard에 Array형을 지원 안함
	TArray<FIntVector2> CachePath = {};
	
	TWeakObjectPtr<class AMS_DuckSplineActor> DuckSplineActor = nullptr;
};
