// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_ActorUnitBase.h"
#include "MS_SplineUnit.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_SplineUnit : public UMS_ActorUnitBase
{
	GENERATED_BODY()
public:
	virtual void Initialize(MS_Handle aUnitHandle, EMS_UnitType aUnitType, int32 aTableId) override;
	virtual void Finalize() override;
};
