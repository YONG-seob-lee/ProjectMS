// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_UnitManager.h"

#include "Unit/MS_UnitBase.h"
#include "Units/MS_AIUnit.h"
#include "Units/MS_BasePlayerUnit.h"
#include "Units/MS_FurnitureUnit.h"
#include "Units/MS_GateUnit.h"
#include "Units/MS_SplineUnit.h"
#include "Units/MS_VehicleUnit.h"


UMS_UnitManager::UMS_UnitManager()
{
	UnitManager = this;
	
	UnitTypeClasses.Emplace(EMS_UnitType::BasePlayer, UMS_BasePlayerUnit::StaticClass());
	UnitTypeClasses.Emplace(EMS_UnitType::Furniture, UMS_FurnitureUnit::StaticClass());
}

void UMS_UnitManager::Finalize()
{
	DestroyAllUnits();
	
	Super::Finalize();
}

TObjectPtr<UMS_UnitBase> UMS_UnitManager::GetUnit(MS_Handle aHandle)
{
	if (Units.Contains(aHandle))
	{
		return *Units.Find(aHandle);
	}

	return nullptr;
}

void UMS_UnitManager::GetUnit(EMS_UnitType aUnitType, TArray<TObjectPtr<UMS_UnitBase>>& aUnits)
{
	aUnits.Empty();

	for(const auto& Unit : Units)
	{
		if(Unit.Value->GetUnitType() == aUnitType)
		{
			aUnits.Emplace(Unit.Value);
		}
	}
}

TObjectPtr<UMS_UnitBase> UMS_UnitManager::CreateUnit(EMS_UnitType aUnitType, int32 aTableId, bool bCreateActor, const FVector& aPosition, const FRotator& aRotator)
{
	// Unit Handle
	const MS_Handle NewUnitHandle = MakeUnitHandle();
	
	if(NewUnitHandle == InvalidUnitHandle)
	{
		return nullptr;
	}
	
	// Create Unit
	const TObjectPtr<UMS_UnitBase> Unit = MS_NewObject<UMS_UnitBase>(this, GetUnitTypeClass(aUnitType));
	Unit->Initialize(NewUnitHandle, aUnitType, aTableId);

	// Create Actor
	if (bCreateActor)
	{
		if (Unit->CreateUnitActor(aPosition, aRotator) == false)
		{
			DestroyUnit_Internal(Unit);
			return nullptr;
		}
	}
	
	Unit->PostInitialize();

	// Add To Map
	Units.Add(NewUnitHandle, Unit);
	
	return Unit;
}

void UMS_UnitManager::DestroyUnit(MS_Handle aHandle)
{
	if (TObjectPtr<UMS_UnitBase> UnitBase = GetUnit(aHandle))
	{
		DestroyUnit_Internal(UnitBase);
	}

	if (Units.Contains(aHandle))
	{
		Units.Remove(aHandle);
	}
}

void UMS_UnitManager::DestroyUnit_Internal(TObjectPtr<UMS_UnitBase> aUnitBase)
{
	if (IsValid(aUnitBase))
	{
		aUnitBase->Finalize();
		aUnitBase->MarkAsGarbage();
		aUnitBase = nullptr;
	}
}

TSubclassOf<UMS_UnitBase> UMS_UnitManager::GetUnitTypeClass(EMS_UnitType aUnitType)
{
	switch(aUnitType)
	{
	case EMS_UnitType::BasePlayer:
		{
			return UMS_BasePlayerUnit::StaticClass();
		}
	case EMS_UnitType::Furniture:
		{
			return UMS_FurnitureUnit::StaticClass();
		}
	case EMS_UnitType::Vehicle:
		{
			return UMS_VehicleUnit::StaticClass();
		}
	case EMS_UnitType::CarSpline:
	case EMS_UnitType::DuckSpline:
		{
			return UMS_SplineUnit::StaticClass();
		}
	case EMS_UnitType::Gate:
		{
			return UMS_GateUnit::StaticClass();
		}
	case EMS_UnitType::AI:
		{
			return UMS_AIUnit::StaticClass();
		}
	default:
		{
			return nullptr;
		}
	}
}

void UMS_UnitManager::DestroyAllUnits()
{
	for(auto& Unit : Units)
	{
		DestroyUnit_Internal(Unit.Value);
	}

	Units.Empty();
}

MS_Handle UMS_UnitManager::MakeUnitHandle()
{
	++LastUnitHandle;

	return LastUnitHandle;
}

UMS_UnitManager* UMS_UnitManager::GetInstance()
{
	return UnitManager;
}
