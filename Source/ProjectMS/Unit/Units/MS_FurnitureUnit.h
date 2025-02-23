// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_ActorUnitBase.h"
#include "ContentsUtilities/MS_ItemDefine.h"
#include "ContentsUtilities/MS_LevelDefine.h"
#include "Table/RowBase/MS_StorageData.h"
#include "MS_FurnitureUnit.generated.h"

enum class EMS_StaffIssueType : uint8;
class UMS_IssueTicket;
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
	
	FORCEINLINE virtual int32 GetBlueprintPathId() const override;

	// Property :: Getter
	FORCEINLINE EMS_ZoneType GetZoneType() const;
	FORCEINLINE EMS_TemperatureType GetTemperatureType() const { return static_cast<EMS_TemperatureType>(FurnitureData->TemperatureType); }
	
	FIntVector2 GetGridPosition() const;

	TArray<class UMS_PropSpaceComponent*> GetPropPurposeSpaceComponents(EMS_PurposeType aPropPurposeSpace) const;

	
	// Slot Datas
	FORCEINLINE int32 GetSlotCount() const;
	FORCEINLINE void GetSlotDatas(TArray<FMS_SlotData>& aOutSlotDatas) const { aOutSlotDatas = SlotDatas; }
	
	void SetSlotDatas(const TArray<FMS_SlotData>& aSlotDatas, bool bSavePlayerData = false);

	bool AddCurrentItemCount(int32 aSlotId, int32 aItemId, int32 aCount, bool bSavePlayerData = false, bool bUpdateNotPlacedItems = true);
	bool SubtractCurrentItemCount(int32 aSlotId, int32 aItemId, int32 aCount, bool bSavePlayerData = false, bool bUpdateNotPlacedItems = true);

	UFUNCTION()
	virtual void SetRequestItem(int32 aSlotId, int32 aItemId, bool bSavePlayerData = true);

	UFUNCTION()
	virtual void TakeItemsImmediately(int32 aSlotId, int32 aItemId, bool bSavePlayerData = true);
	
private:
	void OnChangeRequestSlotDatas();
	void OnChangeCurrentSlotDatas(bool bUpdateNotPlacedItems = true);

public:
	// IssueTickets
	void UpdateIssueTickets();
	void ClearIssueTickets(bool bNeedToUpdateIssueTicketContainer);

private:
	void UpdateStorageSlotIssueTickets();
	
	bool RegisterIssueTicket(EMS_StaffIssueType aIssueType, int32 aSlotId = INDEX_NONE);
	bool UnregisterIssueTicket(TWeakObjectPtr<UMS_IssueTicket> aIssueTicket);
	
	
private:
	struct FMS_StorageData* FurnitureData = nullptr;

	// Property
	UPROPERTY()
	TArray<FMS_SlotData> SlotDatas;
	
	UPROPERTY()
	TArray<TWeakObjectPtr<class UMS_IssueTicket>> IssueTickets;

	float AddPercentage = 1.f;
};
