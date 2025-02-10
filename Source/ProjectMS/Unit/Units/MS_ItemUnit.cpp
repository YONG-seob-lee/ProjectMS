// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ItemUnit.h"

#include "Manager_Both/MS_UnitManager.h"
#include "Table/RowBase/MS_ItemData.h"


void UMS_ItemUnit::Initialize(MS_Handle aUnitHandle, EMS_UnitType aUnitType, int32 aTableId)
{
	Super::Initialize(aUnitHandle, aUnitType, aTableId);

	ItemData = gTableMng.GetTableRowData<FMS_ItemData>(EMS_TableDataType::ItemData, aTableId);
	MS_ENSURE(ItemData != nullptr);
}

void UMS_ItemUnit::Finalize()
{
	Super::Finalize();
}

void UMS_ItemUnit::PostInitialize()
{
	Super::PostInitialize();
}

void UMS_ItemUnit::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
}

bool UMS_ItemUnit::CreateUnitActor(const FVector& aPosition, const FRotator& aRotator)
{
	return Super::CreateUnitActor(aPosition, aRotator);
}

void UMS_ItemUnit::DestroyUnitActor()
{
	Super::DestroyUnitActor();
}

void UMS_ItemUnit::ChangeState(EMS_UnitState aUnitState) const
{
	Super::ChangeState(aUnitState);
}

int32 UMS_ItemUnit::GetBlueprintPathId() const
{
	return ItemData->PathFile;
}
