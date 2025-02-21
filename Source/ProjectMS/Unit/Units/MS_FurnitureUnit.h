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
	
	FORCEINLINE virtual int32 GetBlueprintPathId() const override;

	// Property :: Getter
	FORCEINLINE EMS_ZoneType GetZoneType() const;

	FORCEINLINE int32 GetSlotCount() const;
	FORCEINLINE void GetSlotDatas(TArray<FMS_SlotData>& aOutSlotDatas) const { aOutSlotDatas = SlotDatas; }

	FIntVector2 GetGridPosition() const;

	TArray<class UMS_PropSpaceComponent*> GetPropPurposeSpaceComponents(EMS_PurposeType aPropPurposeSpace) const;

	
	// Property :: Setter
	void SetSlotDatas(const TArray<FMS_SlotData>& aSlotDatas, bool bSavePlayerData = false);

	bool AddCurrentItemCount(int32 aSlotId, int32 aItemId, int32 aCount, bool bSavePlayerData = false);
	bool SubtractCurrentItemCount(int32 aSlotId, int32 aItemId, int32 aCount, bool bSavePlayerData = false);

	UFUNCTION()
	virtual void SetRequestItem(int32 aSlotId, int32 aItemId, bool bSavePlayerData = true);

	UFUNCTION()
	virtual void TakeItemsImmediately(int32 aSlotId, int32 aItemId, bool bSavePlayerData = true);
	
private:
	void OnChangeRequestSlotDatas();
	void OnChangeCurrentSlotDatas();
	
private:
	struct FMS_StorageData* FurnitureData = nullptr;

	// Property
	UPROPERTY()
	TArray<FMS_SlotData> SlotDatas;
};
