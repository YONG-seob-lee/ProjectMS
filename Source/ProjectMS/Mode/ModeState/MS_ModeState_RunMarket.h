// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_ModeStateBase.h"
#include "MS_ModeState_RunMarket.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class PROJECTMS_API UMS_ModeState_RunMarket : public UMS_ModeStateBase
{
	GENERATED_BODY()
public:
	UMS_ModeState_RunMarket();

	virtual void Initialize(uint8 aIndex, const FName& aName) override;
	virtual void Finalize() override;

	virtual void Tick(float aDeltaTime) override;
	
protected:
	virtual void Begin() override;
	virtual void Exit() override;

	virtual void RunSchedule();

public:
	virtual void UpdateMinute(int32 aCurrentMinute);

	virtual void UpdateScheduleEvent(int32 aScheduleEvent);

	
private:
	FTimerHandle DelayTimerHandle;

protected:
	UPROPERTY()
	TObjectPtr<class UStaffSupervisor> StaffSupervisor;

	UPROPERTY()
	TObjectPtr<class UCustomerSupervisor> CustomerSupervisor;
	
	TMap<int32, int32> ScheduleEvent;
};
