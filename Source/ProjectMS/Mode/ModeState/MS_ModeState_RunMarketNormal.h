// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_ModeState_RunMarket.h"
#include "MS_ModeState_RunMarketNormal.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_ModeState_RunMarketNormal : public UMS_ModeState_RunMarket
{
	GENERATED_BODY()

public:
	UMS_ModeState_RunMarketNormal();
	
	virtual void Initialize(uint8 aIndex, const FName& aName) override;
	virtual void Finalize() override;

	virtual void Tick(float aDeltaTime) override;
	
protected:
	virtual void Begin() override;
	virtual void Exit() override;
	
	virtual void RunSchedule() override;
	
	virtual void UpdateMinute(int32 aCurrentMinute) override;

	virtual void UpdateScheduleEvent(int32 aScheduleEvent) override;
};
