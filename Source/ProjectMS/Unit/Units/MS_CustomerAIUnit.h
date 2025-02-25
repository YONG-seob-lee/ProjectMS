// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_MarketAIUnit.h"
#include "Table/Caches/MS_CustomerCacheTable.h"
#include "MS_CustomerAIUnit.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_CustomerAIUnit : public UMS_MarketAIUnit
{
	GENERATED_BODY()

public:
	virtual void Initialize(MS_Handle aUnitHandle, EMS_UnitType aUnitType, int32 aTableId) override;
	virtual void Finalize() override;
	virtual void PostInitialize() override;
	virtual void Tick(float aDeltaTime) override;

	bool FindNearestSpline();
	bool ReachSplineEndPoint() const;
	void GoingToMarket() const;

protected:
	virtual int32 GetBlueprintPathId() const override;
	virtual UClass* GetBlueprintClass() const override;
	
private:
	FMS_CustomerData CustomerData = FMS_CustomerData();
	
	TWeakObjectPtr<class AMS_CustomerSplineActor> CustomerSplineActor = nullptr;
};
