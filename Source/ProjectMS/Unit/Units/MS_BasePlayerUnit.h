// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_CharacterUnitBase.h"
#include "MS_BasePlayerUnit.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_BasePlayerUnit : public UMS_CharacterUnitBase
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(MS_Handle aUnitHandle, EMS_UnitType aUnitType, int32 aTableId) override;
	virtual void Finalize() override;
	virtual void PostInitialize() override;
	virtual void Tick(float aDeltaTime) override;
	
	void SetLodScaleValues(float aCullDistanceScale, float aOutLineCullDistanceScale, bool bVisibleOutLine) const;
	
	FORCEINLINE FName GetUnitName() const { return UnitName; }

protected:
	virtual void ChangeState(EMS_UnitState aActionType) const override;

	virtual int32 GetBlueprintPathId() const override;
	virtual UClass* GetBlueprintClass() const override;
	
private:
	FName UnitName = FName();

	float LodScale = 1.f;
	bool bOutLineModeOn = true;
	bool bSelfPlayer = false;
};