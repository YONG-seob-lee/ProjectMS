// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_UnitManager.h"

#include "Unit/MS_UnitBase.h"

UMS_UnitManager::UMS_UnitManager()
{
	UnitManager = this;
}

TObjectPtr<UMS_UnitBase> UMS_UnitManager::CreateUnit(int32 aUnitTableId, const TSubclassOf<UMS_UnitBase>& aUnitType, const FVector& aPosition, const FRotator& aRotator)
{
	const TObjectPtr<UMS_UnitBase> Unit = MS_NewObject<UMS_UnitBase>(this, aUnitType);
	Unit->AddToRoot();
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

UMS_UnitManager* UMS_UnitManager::GetInstance()
{
	return UnitManager;
}
