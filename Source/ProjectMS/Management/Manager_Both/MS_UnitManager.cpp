﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_UnitManager.h"

#include "Unit/MS_UnitBase.h"
#include "Units/MS_AIUnit.h"
#include "Units/MS_BasePlayerUnit.h"
#include "Units/MS_CounterUnit.h"
#include "Units/MS_CustomerAIUnit.h"
#include "Units/MS_StorageUnit.h"
#include "Units/MS_GateUnit.h"
#include "Units/MS_SplineUnit.h"
#include "Units/MS_StaffAIUnit.h"
#include "Units/MS_VehicleUnit.h"


UMS_UnitManager::UMS_UnitManager()
{
	UnitManager = this;

	CacheUnitTypeToUnits.Empty();
	
	UnitTypeClasses.Emplace(EMS_UnitType::BasePlayer, UMS_BasePlayerUnit::StaticClass());
	UnitTypeClasses.Emplace(EMS_UnitType::Storage, UMS_StorageUnit::StaticClass());
	UnitTypeClasses.Emplace(EMS_UnitType::Counter, UMS_CounterUnit::StaticClass());
}

void UMS_UnitManager::Finalize()
{
	DestroyAllUnits();
	
	Super::Finalize();
}

TWeakObjectPtr<UMS_UnitBase> UMS_UnitManager::GetUnit(MS_Handle aHandle)
{
	if (Units.Contains(aHandle))
	{
		return *Units.Find(aHandle);
	}

	return nullptr;
}

void UMS_UnitManager::GetUnits(EMS_UnitType aUnitType, TArray<TWeakObjectPtr<UMS_UnitBase>>& aOutUnits)
{
	aOutUnits.Empty();

	for(const auto& Unit : Units)
	{
		if(Unit.Value->GetUnitType() == aUnitType)
		{
			aOutUnits.Emplace(Unit.Value);
		}
	}
}

TWeakObjectPtr<UMS_UnitBase> UMS_UnitManager::CreateUnit(EMS_UnitType aUnitType, int32 aTableId, bool bCreateActor, const FVector& aPosition, const FRotator& aRotator)
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
	CacheUnitTypeToUnits.Add(aUnitType, Unit);
	
	return Unit;
}

void UMS_UnitManager::DestroyUnit(MS_Handle aHandle)
{
	TWeakObjectPtr<UMS_UnitBase> Unit = GetUnit(aHandle);
	if (Unit != nullptr)
	{
		EMS_UnitType UnitType = Unit->GetUnitType();
		
		DestroyUnit_Internal(Unit);

		if (CacheUnitTypeToUnits.Contains(UnitType))
		{
			CacheUnitTypeToUnits.RemoveSingle(UnitType, Unit);
		}
	}
	
	if (Units.Contains(aHandle))
	{
		Units.Remove(aHandle);
	}
}

void UMS_UnitManager::DestroyUnit(TWeakObjectPtr<UMS_UnitBase> aUnit)
{
	if (aUnit != nullptr)
	{
		int32 UnitHandle = aUnit->GetUnitHandle();
		EMS_UnitType UnitType = aUnit->GetUnitType();
		
		DestroyUnit_Internal(aUnit);

		if (CacheUnitTypeToUnits.Contains(UnitType))
		{
			CacheUnitTypeToUnits.RemoveSingle(UnitType, aUnit);
		}
	
		if (Units.Contains(UnitHandle))
		{
			Units.Remove(UnitHandle);
		}
	}
}

void UMS_UnitManager::DestroyUnits(TArray<TWeakObjectPtr<UMS_UnitBase>>& aUnits)
{
	for(const auto& Unit : aUnits)
	{
		DestroyUnit(Unit);
	}
}

void UMS_UnitManager::DestroyAllUnits(EMS_UnitType aUnitType)
{
	TArray<TWeakObjectPtr<UMS_UnitBase>> TargetUnits;
	GetUnits(aUnitType, TargetUnits);
	
	for(const auto& TargetUnit : TargetUnits)
	{
		DestroyUnit(TargetUnit);
	}
}

void UMS_UnitManager::DestroyAllUnits()
{
	for(auto& Unit : Units)
	{
		DestroyUnit_Internal(Unit.Value);
	}

	CacheUnitTypeToUnits.Empty();
	Units.Empty();

	LastUnitHandle = InvalidUnitHandle;
}

void UMS_UnitManager::DestroyUnit_Internal(TWeakObjectPtr<UMS_UnitBase> aUnitBase)
{
	if (aUnitBase != nullptr)
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
	case EMS_UnitType::Storage:
		{
			return UMS_StorageUnit::StaticClass();
		}
	case EMS_UnitType::Counter:
		{
			return UMS_CounterUnit::StaticClass();
		}
	case EMS_UnitType::Vehicle:
		{
			return UMS_VehicleUnit::StaticClass();
		}
	case EMS_UnitType::CarSpline:
	case EMS_UnitType::DuckSpline:
	case EMS_UnitType::CustomerSpline:
		{
			return UMS_SplineUnit::StaticClass();
		}
	case EMS_UnitType::Gate:
		{
			return UMS_GateUnit::StaticClass();
		}
	case EMS_UnitType::OutsideAI:
		{
			return UMS_AIUnit::StaticClass();
		}
	case EMS_UnitType::StaffAI:
		{
			return UMS_StaffAIUnit::StaticClass();
		}
	case EMS_UnitType::CustomerAI:
		{
			return UMS_CustomerAIUnit::StaticClass();
		}
	default:
		{
			return nullptr;
		}
	}
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
