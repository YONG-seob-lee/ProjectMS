// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_UnitManager.h"

#include "Unit/MS_UnitBase.h"
#include "Units/MS_BasePlayerUnit.h"
#include "Units/MS_FurnitureUnit.h"
#include "Units/MS_ItemUnit.h"


UMS_UnitManager::UMS_UnitManager()
{
	UnitManager = this;
	
	UnitTypeClasses.Emplace(EMS_UnitType::BasePlayer, UMS_BasePlayerUnit::StaticClass());
	UnitTypeClasses.Emplace(EMS_UnitType::Item, UMS_ItemUnit::StaticClass());
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

TObjectPtr<UMS_UnitBase> UMS_UnitManager::CreateUnit(int32 aUnitTableId, int32 aChildTableId, const FVector& aPosition, const FRotator& aRotator)
{
	// Unit Handle
	const MS_Handle NewUnitHandle = MakeUnitHandle(aUnitTableId, aChildTableId);
	
	if(NewUnitHandle == InvalidUnitHandle)
	{
		return nullptr;
	}

	// Resource Unit Data
	FMS_ResourceUnit* ResourceUnitData = GetResourceUnitData(aUnitTableId);
	if (ResourceUnitData == nullptr)
	{
		return nullptr;
	}

	// Unit Type
	EMS_UnitType UnitType = static_cast<EMS_UnitType>(ResourceUnitData->UnitType);
	if (UnitType == EMS_UnitType::Default)
	{
		return nullptr;
	}
	
	// Unit Type Class
	TSubclassOf<UMS_UnitBase> UnitTypeClass = nullptr;
	if (UnitTypeClasses.Contains(UnitType))
	{
		UnitTypeClass = *UnitTypeClasses.Find(UnitType);
	}
	
	if(UnitTypeClass == nullptr)
	{
		return nullptr; 
	}

	// Create Unit
	const TObjectPtr<UMS_UnitBase> Unit = MS_NewObject<UMS_UnitBase>(this, UnitTypeClass);
	Unit->Initialize(LastUnitHandle, aUnitTableId, aChildTableId);
	
	if(Unit->CreateUnitActor(aPosition, aRotator) == false)
	{
		DestroyUnit_Internal(Unit);
		return nullptr;
	}

	Unit->PostInitialize();

	// Add To Map
	Units.Add(LastUnitHandle, Unit);
	
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

void UMS_UnitManager::DestroyAllUnits()
{
	for(auto& Unit : Units)
	{
		DestroyUnit(Unit.Key);
	}

	Units.Empty();
}

MS_Handle UMS_UnitManager::MakeUnitHandle(int32 aUnitTableId, int32 aChildTableId)
{
	++LastUnitHandle;

	return LastUnitHandle;
}

FMS_ResourceUnit* UMS_UnitManager::GetResourceUnitData(int32 aUnitTableId) const
{
	FMS_ResourceUnit* ResourceUnitData = gTableMng.GetTableRowData<FMS_ResourceUnit>(EMS_TableDataType::ResourceUnit, aUnitTableId);
	if(ResourceUnitData == nullptr)
	{
		MS_LOG_Verbosity(Error, TEXT("[%s] ResourceUnitData is nullptr [UnitTableId : %d]"), *MS_FUNC_STRING, aUnitTableId);
		MS_Ensure(false);
	}
	
	return ResourceUnitData;
}

UMS_UnitManager* UMS_UnitManager::GetInstance()
{
	return UnitManager;
}
