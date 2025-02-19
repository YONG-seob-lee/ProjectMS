// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ContentsUtilities/MS_AIDefine.h"
#include "Mode/ModeObject/Supervisor/MS_AISupervisor.h"
#include "MS_StaffSupervisor.generated.h"

class UMS_StaffAIUnit;
/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_StaffSupervisor : public UMS_AISupervisor
{
	GENERATED_BODY()

public:
	UMS_StaffSupervisor();
	
	virtual void Initialize() override;
	virtual void Finalize() override;

	virtual void Tick(float aDeltaTime) override;

	virtual void Begin() override;
	virtual void Exit() override;

	void SetIssueTicketContainer(TWeakObjectPtr<class UMS_IssueTicketContainer> aIssueTicketContainer);

	
	virtual void UpdateMinute(int32 aCurrentMinute) override;
	virtual void UpdateScheduleEvent(int32 aScheduleEvent) override;
	
	void RequestSpawnCharacters(int32 aCurrentMinute);
	bool SpawnCharacter(int32 StaffId, const FVector& SpawnLocation, const FRotator& SpawnRotator);

	
private:
	void InitStaffSpawnPoint();
	
	TWeakObjectPtr<class UMS_IssueTicketContainer> IssueTicketContainer;

	TArray<FMS_StaffData> StaffDatas;
	TMap<int32, int32> NeedToSpawnStaffDataIndexToSpawnMinute;

	TArray<TWeakObjectPtr<UMS_StaffAIUnit>> StaffAIUnits;
	TArray<TWeakObjectPtr<class AMS_StaffDuckSpawnPoint>>  StaffSpawnPoints;
	
	bool bSpawnCharacter;
};
