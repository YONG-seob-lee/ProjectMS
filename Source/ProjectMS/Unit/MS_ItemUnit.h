// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_UnitBase.h"
#include "Table/RowBase/MS_ItemData.h"
#include "MS_ItemUnit.generated.h"

class AMS_Actor;
/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_ItemUnit : public UMS_UnitBase
{
	GENERATED_BODY()
	
public:
	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void PostInitialize() override;
	virtual void Tick(float aDeltaTime) override;

	virtual bool CreateUnit(int32 aUnitTableId, const FVector& aPosition, const FRotator& aRotator) override;
	virtual void DestroyUnit() override;

	FORCEINLINE TObjectPtr<AMS_Actor> GetActor() { return Actor; }
protected:
	virtual void ChangeState(EMS_UnitState aUnitState) const override;
private:
	UPROPERTY()
	TObjectPtr<AMS_Actor> Actor = nullptr;

	FMS_ItemData* ItemData = nullptr;
};
