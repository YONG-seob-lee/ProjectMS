// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_UnitBase.h"
#include "Table/RowBase/MS_ResourceUnit.h"
#include "MS_BasePlayerUnit.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_BasePlayerUnit : public UMS_UnitBase
{
	GENERATED_BODY()
	
public:
	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void PostInitialize() override;
	virtual void Tick(float aDeltaTime) override;
	
	virtual bool CreateUnit(int32 aUnitTableId, const FVector& aPosition, const FRotator& aRotator) override;
	virtual void DestroyUnit() override;
	
	FORCEINLINE TObjectPtr<class AMS_CharacterBase> GetCharacterBase() const { return Character; }

	void SetLodScaleValues(float aCullDistanceScale, float aOutLineCullDistanceScale, bool bVisibleOutLine) const;
protected:
	virtual void ChangeState(EMS_UnitState aActionType) const override;
	
private:
	UPROPERTY()
	TObjectPtr<AMS_CharacterBase> Character = nullptr;
	
	FMS_ResourceUnit* UnitData = nullptr;

	float LodScale = 1.f;
	bool bOutLineModeOn = true;
	bool bSelfPlayer = false;

private:
};
