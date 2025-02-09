// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_GateUnit.h"

void UMS_GateUnit::Initialize(MS_Handle aUnitHandle, EMS_UnitType aUnitType, int32 aUnitTableId)
{
	Super::Initialize(aUnitHandle, aUnitType, aUnitTableId);
}

void UMS_GateUnit::Finalize()
{
	Super::Finalize();
}

void UMS_GateUnit::PostInitialize()
{
	Super::PostInitialize();
}

void UMS_GateUnit::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
}

bool UMS_GateUnit::CreateUnitActor(const FVector& aPosition, const FRotator& aRotator)
{
	return Super::CreateUnitActor(aPosition, aRotator);
}

void UMS_GateUnit::DestroyUnitActor()
{
	Super::DestroyUnitActor();
}
