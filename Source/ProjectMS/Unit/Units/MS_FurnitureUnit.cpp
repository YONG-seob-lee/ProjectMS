// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_FurnitureUnit.h"

#include "MS_Actor.h"


void UMS_FurnitureUnit::Initialize(MS_Handle aUnitHandle, int32 aUnitTableId, int32 aChildTableId)
{
	Super::Initialize(aUnitHandle, aUnitTableId, aChildTableId);
}

void UMS_FurnitureUnit::Finalize()
{
	Super::Finalize();
}

void UMS_FurnitureUnit::PostInitialize()
{
	Super::PostInitialize();
}

void UMS_FurnitureUnit::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
}

bool UMS_FurnitureUnit::CreateUnitActor(const FVector& aPosition, const FRotator& aRotator)
{
	return Super::CreateUnitActor(aPosition, aRotator);
}

void UMS_FurnitureUnit::DestroyUnitActor()
{
	Super::DestroyUnitActor();
}
