// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_UnitManager.h"

#include "Character/MS_CharacterBase.h"
#include "Unit/MS_UnitBase.h"
#include "Units/MS_BasePlayerUnit.h"
#include "Units/MS_FurnitureUnit.h"
#include "Units/MS_ItemUnit.h"

UMS_UnitManager::UMS_UnitManager()
{
	UnitManager = this;
	
	UnitType.Emplace(EMS_UnitType::BasePlayer, UMS_BasePlayerUnit::StaticClass());
	UnitType.Emplace(EMS_UnitType::Item, UMS_ItemUnit::StaticClass());
	UnitType.Emplace(EMS_UnitType::Furniture, UMS_FurnitureUnit::StaticClass());
}

void UMS_UnitManager::Finalize()
{
	DestroyAllUnits();
	
	Super::Finalize();
}

TObjectPtr<UMS_UnitBase> UMS_UnitManager::CreateUnit(int32 aUnitTableId, int32 aChildTableId,  const TSubclassOf<UMS_UnitBase>& aUnitType, const FVector& aPosition, const FRotator& aRotator)
{
	// Unit Handle
	++LastUnitHandle;

	// Unit
	const TObjectPtr<UMS_UnitBase> Unit = MS_NewObject<UMS_UnitBase>(this, aUnitType);
	Unit->Initialize(LastUnitHandle);
	
	if(Unit->CreateUnit(aUnitTableId, aChildTableId, aPosition, aRotator) == false)
	{
		return nullptr;
	}

	Unit->PostInitialize();

	// const MS_Handle NewUnitHandle = MakeUnitHandle(Unit);
	//
	// if(NewUnitHandle == InvalidUnitHandle)
	// {
	// 	return nullptr;
	// }

	// Add
	Units.Add(LastUnitHandle, Unit);
	
	return Unit;
}

TObjectPtr<UMS_UnitBase> UMS_UnitManager::CreateUnit(int32 aUnitTableId, int32 aChildTableId,  EMS_UnitType aUnitType, const FVector& aPosition, const FRotator& aRotator)
{
	// Unit Handle
	++LastUnitHandle;

	// Unit
	const TSubclassOf<UMS_UnitBase>* UnitClassType = UnitType.Find(aUnitType);
	if(UnitClassType == nullptr)
	{
		return nullptr; 
	}
	
	const TObjectPtr<UMS_UnitBase> Unit = MS_NewObject<UMS_UnitBase>(this, *UnitClassType);
	Unit->Initialize(LastUnitHandle);
	
	if(Unit->CreateUnit(aUnitTableId, aChildTableId, aPosition, aRotator) == false)
	{
		return nullptr;
	}

	Unit->PostInitialize();

	// const MS_Handle NewUnitHandle = MakeUnitHandle(Unit);
	//
	// if(NewUnitHandle == InvalidUnitHandle)
	// {
	// 	return nullptr;
	// }

	// Add
	Units.Add(LastUnitHandle, Unit);
	
	return Unit;
}

void UMS_UnitManager::DestroyAllUnits()
{
	for(auto& Unit : Units)
	{
		if(Unit.Value == nullptr)
		{
			continue;
		}

		Unit.Value->Finalize();
		Unit.Value->MarkAsGarbage();
		Unit.Value = nullptr;
	}

	Units.Empty();
}

UMS_UnitManager* UMS_UnitManager::GetInstance()
{
	return UnitManager;
}
