// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_SpawnPoint.h"
#include "ContentsUtilities/MS_AIDefine.h"
#include "MS_StaffDuckSpawnPoint.generated.h"

UCLASS()
class PROJECTMS_API AMS_StaffDuckSpawnPoint : public AMS_SpawnPoint
{
	GENERATED_BODY()

public:
	AMS_StaffDuckSpawnPoint(const FObjectInitializer& ObjectInitializer);

	void UpdateSpawnData(FMS_PlayerStaffData* aPlayerStaffData, int32 aSpawnMinute);
	
	virtual FVector GetSpawnLocation() override;
	virtual FRotator GetSpawnRotation() override;

	bool IsSpawnThisMinute(int32 aCurrentMinute, TArray<FMS_PlayerStaffData*>& aStaffData);
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	// Key : UnitId, Value : SpawnMinute
	TMap<FMS_PlayerStaffData*, int32> SpawnDatas = {};
};
