// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_GateUnit.h"

#include "Prop/Gate/MS_Gate.h"

void UMS_GateUnit::Initialize(MS_Handle aUnitHandle, EMS_UnitType aUnitType, int32 aTableId)
{
	Super::Initialize(aUnitHandle, aUnitType, aTableId);
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

AMS_Gate* UMS_GateUnit::GetGateActor() const
{
	return Cast<AMS_Gate>(GetActor());
}

EMS_ZoneType UMS_GateUnit::GetGateZoneType() const
{
	return GetGateActor()->GetGateZoneType();
}

EMS_ZoneType UMS_GateUnit::GetLinkedZoneType() const
{
	return GetGateActor()->GetLinkedZoneType();
}

TWeakObjectPtr<AMS_Gate> UMS_GateUnit::GetLinkedGateActor() const
{
	return GetGateActor()->GetLinkedGate();
}

FIntVector2 UMS_GateUnit::GetGridPosition() const
{
	return GetGateActor()->GetGridPosition();
}

FIntVector2 UMS_GateUnit::GetLinkedGridPosition() const
{
	return GetLinkedGateActor()->GetGridPosition();
}
