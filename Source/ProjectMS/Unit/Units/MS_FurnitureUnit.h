// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_ActorUnitBase.h"
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

	virtual bool CreateUnitActor(const FVector& aPosition, const FRotator& aRotator) override;
	virtual void DestroyUnitActor() override;


public:
	virtual int32 GetBlueprintPathId() const override;
	

private:
	struct FMS_StorageData* FurnitureData = nullptr;
};
