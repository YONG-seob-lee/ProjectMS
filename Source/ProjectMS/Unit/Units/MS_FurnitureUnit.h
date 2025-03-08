// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_ActorUnitBase.h"
#include "ContentsUtilities/MS_ItemDefine.h"
#include "ContentsUtilities/MS_LevelDefine.h"
#include "ContentsUtilities/MS_AIDefine.h"
#include "MS_FurnitureUnit.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_FurnitureUnit : public UMS_ActorUnitBase
{
	GENERATED_BODY()

public:
	virtual void Initialize(MS_Handle aUnitHandle, EMS_UnitType aUnitType, int32 aTableId) override;
	virtual void Finalize() override;
	virtual void PostInitialize() override;
	virtual void Tick(float aDeltaTime) override;
	
	virtual int32 GetBlueprintPathId() const override;

	FRotator GetActorRotator() const;

	// Property :: Getter
	EMS_ZoneType GetZoneType() const;
	EMS_TemperatureType GetTemperatureType() const;
	
	FIntVector2 GetGridPosition() const;

	TArray<class UMS_PropSpaceComponent*> GetPropPurposeSpaceComponents(EMS_PurposeType aPropPurposeSpace) const;
	
	// IssueTickets
	virtual void UpdateIssueTicket();
	virtual void ClearIssueTickets(bool bNeedToUpdateIssueTicketContainer);

	void OnChangeIssueTicketRequestUnitToStaffUnit(TWeakObjectPtr<class UMS_IssueTicket> aTargetTicket);

	
protected:
	virtual bool RegisterIssueTicket(EMS_StaffIssueType aIssueType, int32 aSlotId = INDEX_NONE);
	virtual bool UnregisterIssueTicket(TWeakObjectPtr<class UMS_IssueTicket> aIssueTicket);

	
protected:
	struct FMS_FurnitureData* FurnitureData = nullptr;
	
	UPROPERTY()
	TArray<TWeakObjectPtr<class UMS_IssueTicket>> IssueTickets;
};
