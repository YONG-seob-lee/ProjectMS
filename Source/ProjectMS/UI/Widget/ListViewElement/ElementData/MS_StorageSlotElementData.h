// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ContentsUtilities/MS_LevelDefine.h"
#include "ContentsUtilities/MS_ItemDefine.h"
#include "MS_StorageSlotElementData.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FMS_OnClickStorageSlot, int32)
/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_StorageSlotElementData : public UObject
{
	GENERATED_BODY()
public:
	FORCEINLINE void SetOwnerZoneType(EMS_ZoneType aOwnerZoneType) { OwnerZoneType = aOwnerZoneType; }
	FORCEINLINE void SetSlotType(EMS_ItemSlotUIType aSlotUIType) { SlotUIType = aSlotUIType; }
	FORCEINLINE void SetSlotIndex(int32 aSlotIndex) { SlotIndex = aSlotIndex; }
	FORCEINLINE void SetSlotData(const FMS_SlotData& aSlotData) { SlotData = aSlotData; }

	FORCEINLINE EMS_ZoneType GetOwnerZoneType() const { return OwnerZoneType; }
	FORCEINLINE EMS_ItemSlotUIType GetSlotUIType() const { return SlotUIType; }
	FORCEINLINE int32 GetSlotIndex() const { return SlotIndex; }
	FORCEINLINE const FMS_SlotData& GetSlotData() const { return SlotData; }

	FMS_OnClickStorageSlot OnClickDisplaySlotDelegate;
	FMS_OnClickStorageSlot OnClickShelfSlotDelegate;

private:
	EMS_ZoneType OwnerZoneType = EMS_ZoneType::None;
	EMS_ItemSlotUIType SlotUIType = EMS_ItemSlotUIType::None;
	int32 SlotIndex = INDEX_NONE;
	struct FMS_SlotData SlotData;
};
