// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_ModeStateBase.h"
#include "MS_ModeState_RunMarketBase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class PROJECTMS_API UMS_ModeState_RunMarketBase : public UMS_ModeStateBase
{
	GENERATED_BODY()
public:
	UMS_ModeState_RunMarketBase();

	virtual void Initialize(uint8 aIndex, const FName& aName) override;
	virtual void Finalize() override;

	virtual void Tick(float aDeltaTime) override;
	
protected:
	virtual void Begin() override;
	virtual void Exit() override;
	
	virtual void OnInputPointerDoubleClickEvent(FVector2D aPosition, const FHitResult& aInteractableHitResult) override;
	
private:
	void EndSchedule();

public:
	virtual void UpdateMinute(int32 aCurrentMinute);
	virtual void UpdateScheduleEvent(int32 aScheduleEvent);

	FORCEINLINE void GetScheduleEvent(TMap<int32, int32>& _ScheduleEvent) const { _ScheduleEvent = ScheduleEvent; }
	
	// aTargetPoints가 다른 존에 있을 경우 첫번째 타겟의 게이트를 찾아감
	virtual void SearchPathToTarget(TArray<FIntVector2>& aOutPath, const FIntVector2& aStartPosition, const TArray<FIntVector2>& aTargetPositions) const override;

	
	TObjectPtr<class UMS_StaffSupervisor> GetStaffSupervisor() const { return StaffSupervisor; }

	
private:
	FTimerHandle DelayTimerHandle;

protected:
	UPROPERTY()
	TObjectPtr<class UMS_IssueTicketContainer> IssueTicketContainer;
	
	UPROPERTY()
	TObjectPtr<class UMS_StaffSupervisor> StaffSupervisor;

	UPROPERTY()
	TObjectPtr<class UMS_CustomerSupervisor> CustomerSupervisor;

	UPROPERTY()
	TObjectPtr<class UMS_GridBFS_2x2> GridBFS_2x2;
	
	TMap<int32, int32> ScheduleEvent;
};
