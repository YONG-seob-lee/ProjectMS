// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_BasePlayerUnit.h"

#include "Character/MS_CharacterBase.h"
#include "CoreClass/Controller/MS_PlayerController.h"


void UMS_BasePlayerUnit::Initialize(MS_Handle aUnitHandle, EMS_UnitType aUnitType, int32 aTableId)
{
	Super::Initialize(aUnitHandle, aUnitType, aTableId);
}

void UMS_BasePlayerUnit::Finalize()
{
	Super::Finalize();
}

void UMS_BasePlayerUnit::PostInitialize()
{
	Super::PostInitialize();
}

void UMS_BasePlayerUnit::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
}

void UMS_BasePlayerUnit::SetLodScaleValues(float aCullDistanceScale, float aOutLineCullDistanceScale, bool bVisibleOutLine) const
{
	if(GetCharacter())
	{
		GetCharacter()->SetLodScaleValues(aCullDistanceScale, aOutLineCullDistanceScale, bVisibleOutLine);
	}
}

void UMS_BasePlayerUnit::ChangeState(EMS_UnitState aActionType) const
{
	if(APlayerController* PlayerController = Cast<APlayerController>(GetCharacter()->GetController()))
	{
		PlayerController->FlushPressedKeys();
	}
	
	Super::ChangeState(aActionType);
}

int32 UMS_BasePlayerUnit::GetBlueprintPathId() const
{
	return INDEX_NONE;
}

UClass* UMS_BasePlayerUnit::GetBlueprintClass() const
{
	return AMS_CharacterBase::StaticClass();
}
