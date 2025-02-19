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
	
protected:
	virtual int32 GetBlueprintPathId() const override;
	virtual UClass* GetBlueprintClass() const override;

	
public:
	int32 GetStaffActionNum() const { return StaffActions.Num(); }
	EMS_StaffActionType GetFirstStaffAction() const;
	
	
	void RegisterStaffAction(EMS_StaffActionType aStaffActionType);
	void UnregisterStaffAction(EMS_StaffActionType aStaffActionType);
	
	void OnRegisteredAsIssueTicketStaff(TWeakObjectPtr<class UMS_IssueTicket> aIssueTicket);
	void OnUnregisteredAsIssueTicketStaff();

private:
	struct FMS_Staff* StaffTableData = nullptr;

	TArray<EMS_StaffActionType> StaffActions = {};
	TWeakObjectPtr<UMS_IssueTicket> IssueTicket;

	TArray<FIntVector2> CacheTargetPositions = {};	// Blackboard에 Array형을 지원 안함
	TArray<FIntVector2> CachePath = {};
};
