// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "MS_StorageSlotElementData.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_StorageSlotElementData : public UObject
{
	GENERATED_BODY()
public:
	FORCEINLINE void SetItemId(int32 aItemId) { ItemId = aItemId; }
	FORCEINLINE void SetMolecular(int32 aMolecular) { Molecular = aMolecular; }
	FORCEINLINE void SetDenominator(int32 aDenominator) { Denominator = aDenominator; }
	
	FORCEINLINE int32 GetItemId() const { return ItemId; }
	FORCEINLINE int32 GetMolecular() const { return Molecular; }
	FORCEINLINE int32 GetDenominator() const { return Denominator; }

private:
	int32 ItemId = 0;
	int32 Molecular = 0;
	int32 Denominator = 0;
};
