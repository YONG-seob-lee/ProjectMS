// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_FurnitureUnit.h"

#include "MS_Actor.h"
#include "Table/RowBase/MS_StorageData.h"


void UMS_FurnitureUnit::Initialize(MS_Handle aUnitHandle, EMS_UnitType aUnitType, int32 aTableId)
{
	Super::Initialize(aUnitHandle, aUnitType, aTableId);

	FurnitureData = gTableMng.GetTableRowData<FMS_StorageData>(EMS_TableDataType::Storage, aTableId);
	MS_ENSURE(FurnitureData != nullptr);
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

int32 UMS_FurnitureUnit::GetBlueprintPathId() const
{
	return FurnitureData->PathFile;
}
