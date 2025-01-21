// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_FurnitureUnit.h"

#include "MS_Actor.h"


void UMS_FurnitureUnit::Initialize(MS_Handle aUnitHandle)
{
	Super::Initialize(aUnitHandle);
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

bool UMS_FurnitureUnit::CreateUnit(int32 aUnitTableId, int32 aChildTableId, const FVector& aPosition, const FRotator& aRotator)
{
	if (Super::CreateUnit(aUnitTableId, aChildTableId, aPosition, aRotator))
	{
		if(const TObjectPtr<AMS_Actor> NewActor = CreateActor(aUnitTableId, aChildTableId, aPosition, aRotator))
		{
			NewActor->SetOwnerUnitBase(this);
			
			return true;
		}
	}

	MS_Ensure(false);
	return false;
}

void UMS_FurnitureUnit::DestroyUnit()
{
	Super::DestroyUnit();
}
