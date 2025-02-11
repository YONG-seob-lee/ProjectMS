// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ContentsUtilities/MS_LevelDefine.h"
#include "Manager_Client/MS_ItemManager.h"

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
	FORCEINLINE void SetSlotType(int32 aSlotType) { SlotType = aSlotType; }
	FORCEINLINE void SetSlotIndex(int32 aSlotIndex) { SlotIndex = aSlotIndex; }
	FORCEINLINE void SetItemId(int32 aItemId) { ItemId = aItemId; }
	FORCEINLINE void SetMolecular(int32 aMolecular) { Molecular = aMolecular; }
	FORCEINLINE void SetDenominator(int32 aDenominator) { Denominator = aDenominator; }
	FORCEINLINE void SetShelfCount(int32 aShelfCount) { ShelfCount = aShelfCount; }

	FORCEINLINE int32 GetSlotType() const { return SlotType; }
	FORCEINLINE int32 GetSlotIndex() const { return SlotIndex; }
	FORCEINLINE int32 GetItemId() const { return ItemId; }
	FORCEINLINE int32 GetMolecular() const { return Molecular; }
	FORCEINLINE int32 GetDenominator() const { return Denominator; }
	FORCEINLINE int32 GetShelfCount() const { return ShelfCount; }

	FMS_OnClickStorageSlot OnClickDisplaySlotDelegate;
	FMS_OnClickStorageSlot OnClickShelfSlotDelegate;

private:
	int32 SlotType = static_cast<int32>(EMS_ZoneType::None);
	int32 SlotIndex = INDEX_NONE;
	int32 ItemId = INDEX_NONE;
	int32 Molecular = 0;
	int32 Denominator = 0;
	int32 ShelfCount = 0;
};
