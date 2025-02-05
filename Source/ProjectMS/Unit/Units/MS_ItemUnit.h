// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_ActorUnitBase.h"
#include "Table/RowBase/MS_ItemData.h"
#include "MS_ItemUnit.generated.h"

class AMS_Actor;
/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_ItemUnit : public UMS_ActorUnitBase
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(MS_Handle aUnitHandle, EMS_UnitType aUnitType, int32 aUnitTableId) override;
	virtual void Finalize() override;
	virtual void PostInitialize() override;
	virtual void Tick(float aDeltaTime) override;

	virtual bool CreateUnitActor(const FVector& aPosition, const FRotator& aRotator) override;
	virtual void DestroyUnitActor() override;
	
protected:
	virtual void ChangeState(EMS_UnitState aUnitState) const override;

private:
	FMS_ItemData* ItemData = nullptr;
};
