// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_ActorUnitBase.h"
#include "ContentsUtilities/MS_LevelDefine.h"
#include "MS_GateUnit.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_GateUnit : public UMS_ActorUnitBase
{
	GENERATED_BODY()

public:
	virtual void Initialize(MS_Handle aUnitHandle, EMS_UnitType aUnitType, int32 aTableId) override;
	virtual void Finalize() override;
	virtual void PostInitialize() override;
	virtual void Tick(float aDeltaTime) override;

	virtual bool CreateUnitActor(const FVector& aPosition, const FRotator& aRotator) override;
	virtual void DestroyUnitActor() override;

	// Getter
	FORCEINLINE class AMS_Gate* GetGateActor() const;
	
	FORCEINLINE EMS_ZoneType GetGateZoneType() const;
	FORCEINLINE EMS_ZoneType GetLinkedZoneType() const;
	
	FORCEINLINE int32 GetGateIndex() const;
	FORCEINLINE int32 GetLinkedGateIndex() const;

	FORCEINLINE FIntVector2 GetGridPosition() const;
};
