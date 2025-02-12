// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_ActorUnitBase.h"
#include "ContentsUtilities/MS_ItemDefine.h"
#include "ContentsUtilities/MS_LevelDefine.h"
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

	// Property :: Getter
	EMS_ZoneType GetZoneType() const { return ZoneType; }
	
	void GetSlotDatas(TArray<FMS_SlotData>& aOutSlotDatas) const { aOutSlotDatas = SlotDatas; }
	
	// Property :: Setter
	void SetSlotDatas(const TArray<FMS_SlotData>& aSlotDatas);

private:
	void OnChangeRequestSlotDatas();
	void OnChangeCurrentSlotDatas();
	

private:
	struct FMS_StorageData* FurnitureData = nullptr;

	// Property
	UPROPERTY()
	EMS_ZoneType ZoneType;
	
	UPROPERTY()
	TArray<FMS_SlotData> SlotDatas;
};
