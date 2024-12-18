// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_UnitManager.h"

#include "MS_BasePlayer.h"
#include "Unit/MS_UnitBase.h"

UMS_UnitManager::UMS_UnitManager()
{
	UnitManager = this;
	
	UnitType.Emplace(EMS_UnitType::BasePlayer, UMS_BasePlayer::StaticClass());
}

void UMS_UnitManager::Finalize()
{
	DestroyAllUnits();
	
	Super::Finalize();
}

TObjectPtr<UMS_UnitBase> UMS_UnitManager::CreateUnit(int32 aUnitTableId, const TSubclassOf<UMS_UnitBase>& aUnitType, const FVector& aPosition, const FRotator& aRotator)
{
	const TObjectPtr<UMS_UnitBase> Unit = MS_NewObject<UMS_UnitBase>(this, aUnitType);
	Unit->Initialize();
	
	if(Unit->CreateUnit(aUnitTableId, aPosition, aRotator) == false)
	{
		return nullptr;
	}

	Unit->PostInitialize();
	Unit->SetLodScaleValues(LodScale, LodScale, bOutLineModeOn);

	// const MS_Handle NewUnitHandle = MakeUnitHandle(Unit);
	//
	// if(NewUnitHandle == InvalidUnitHandle)
	// {
	// 	return nullptr;
	// }

	// 일단 테이블 아이디로 사용
	Units.Add(aUnitTableId, Unit);
	
	return Unit;
}

TObjectPtr<UMS_UnitBase> UMS_UnitManager::CreateUnit(int32 aUnitTableId, int32 aUnitType, const FVector& aPosition, const FRotator& aRotator)
{
	const TSubclassOf<UMS_UnitBase>* UnitClassType = UnitType.Find(static_cast<EMS_UnitType>(aUnitType));
	if(UnitClassType == nullptr)
	{
		return nullptr; 
	}
	
	const TObjectPtr<UMS_UnitBase> Unit = MS_NewObject<UMS_UnitBase>(this, *UnitClassType);
	Unit->Initialize();
	
	if(Unit->CreateUnit(aUnitTableId, aPosition, aRotator) == false)
	{
		return nullptr;
	}

	Unit->PostInitialize();
	Unit->SetLodScaleValues(LodScale, LodScale, bOutLineModeOn);

	// const MS_Handle NewUnitHandle = MakeUnitHandle(Unit);
	//
	// if(NewUnitHandle == InvalidUnitHandle)
	// {
	// 	return nullptr;
	// }

	// 일단 테이블 아이디로 사용
	Units.Add(aUnitTableId, Unit);
	
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

		Unit.Value->RemoveFromRoot();
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
