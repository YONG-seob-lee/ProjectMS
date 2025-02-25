// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ContentsUtilities/MS_AIDefine.h"
#include "Mode/ModeObject/Supervisor/MS_AISupervisor.h"
#include "MS_StaffSupervisor.generated.h"

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
	
# if WITH_EDITOR
	void RequestSpawnCharacterInMarket(int32 aStaffId);
#endif
	
	bool SpawnCharacter(int32 aStaffId, const FVector& SpawnLocation, const FRotator& SpawnRotator);
	bool SpawnCharacter(FMS_PlayerStaffData* aPlayerStaffData, const FVector& SpawnLocation, const FRotator& SpawnRotator);
	void RemoveAllCharacter();

	void RegisterPreSpawnedCharacter(int32 aStaffId, TWeakObjectPtr<class AMS_CharacterBase> aCharacter);
	
private:
	void InitStaffSpawnPoint();
	void CashingDuckSplineActors() const;
	
	TWeakObjectPtr<class UMS_IssueTicketContainer> IssueTicketContainer;

	TArray<FMS_PlayerStaffData> PlayerStaffDatas;
	TMap<int32, int32> NeedToSpawnStaffDataIndexToSpawnMinute;

	TArray<TWeakObjectPtr<class UMS_StaffAIUnit>> StaffAIUnits;
	TArray<TWeakObjectPtr<class AMS_StaffDuckSpawnPoint>>  StaffSpawnPoints;
	
	bool bSpawnCharacter;
};
