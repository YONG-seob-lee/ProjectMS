// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_UnitBase.h"
#include "MS_BasePlayer.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_BasePlayer : public UMS_UnitBase
{
	GENERATED_BODY()
	
public:
	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void PostInitialize() override;
	virtual void Tick(float aDeltaTime) override;
	
	virtual bool CreateUnit(int32 aUnitTableId, const FVector& aPos, const FRotator& aRot) override;
	virtual void DestroyUnit() override;
	
protected:
	virtual void ChangeState(EMS_UnitState aActionType) const override;
	
	bool bSelfPlayer = false;

private:
};
