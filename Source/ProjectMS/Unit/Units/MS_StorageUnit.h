// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_FurnitureUnit.h"
#include "ContentsUtilities/MS_ItemDefine.h"
#include "ContentsUtilities/MS_LevelDefine.h"
#include "Table/RowBase/MS_StorageData.h"
#include "MS_StorageUnit.generated.h"

enum class EMS_StaffIssueType : uint8;
class UMS_IssueTicket;
/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_StorageUnit : public UMS_FurnitureUnit
{
	GENERATED_BODY()

public:
	virtual void Initialize(MS_Handle aUnitHandle, EMS_UnitType aUnitType, int32 aTableId) override;
	virtual void Finalize() override;
	virtual void PostInitialize() override;
	virtual void Tick(float aDeltaTime) override;
	
	// Slot Datas
	FORCEINLINE int32 GetSlotCount() const { 	return FurnitureData->SlotCount; }
	FORCEINLINE void GetSlotDatas(TArray<FMS_SlotData>& aOutSlotDatas) const { aOutSlotDatas = SlotDatas; }
	FMS_SlotData GetSlotData(int32 aSlotId) const;
	
	void SetSlotDatas(const TArray<FMS_SlotData>& aSlotDatas, bool bSavePlayerData = false);

	bool AddCurrentItemCount(int32 aSlotId, int32 aItemId, int32 aCount, bool bSavePlayerData = false, bool bUpdateNotPlacedItems = true);
	int32 AddAnySlotCurrentItemCount(int32 aItemId, int32 aCount, bool bSavePlayerData = false, bool bUpdateNotPlacedItems = true);

	bool SubtractCurrentItemCount(int32 aSlotId, int32 aItemId, int32 aCount, bool bSavePlayerData = false, bool bUpdateNotPlacedItems = true);
	int32 SubtractAnySlotCurrentItemCount(int32 aItemId, int32 aCount, bool bSavePlayerData = false, bool bUpdateNotPlacedItems = true);

	UFUNCTION()
	virtual void SetRequestItem(int32 aSlotId, int32 aItemId, bool bSavePlayerData = true);

	UFUNCTION()
	virtual void TakeItemsImmediately(int32 aSlotId, int32 aItemId, bool bSavePlayerData = true);
	
private:
	void OnChangeRequestSlotDatas();
	void OnChangeCurrentSlotDatas(bool bUpdateNotPlacedItems = true);

public:
	// IssueTickets
	virtual void UpdateIssueTickets() override;
	virtual void ClearIssueTickets(bool bNeedToUpdateIssueTicketContainer) override;

private:
	void UpdateStorageSlotIssueTickets();
	
private:
	// Property
	UPROPERTY()
	TArray<FMS_SlotData> SlotDatas;
	
	float AddPercentage = 1.f;
};
