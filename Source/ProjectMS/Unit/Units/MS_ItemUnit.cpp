// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ItemUnit.h"

#include "Manager_Both/MS_UnitManager.h"

void UMS_ItemUnit::Initialize(MS_Handle aUnitHandle, int32 aUnitTableId, int32 aChildTableId)
{
	Super::Initialize(aUnitHandle, aUnitTableId, aChildTableId);
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
	if (Super::CreateUnitActor(aPosition, aRotator))
	{
		ItemData = gTableMng.GetTableRowData<FMS_ItemData>(EMS_TableDataType::ItemData, ChildTableId);
		if(ItemData == nullptr)
		{
			return false;
		}
	}
	
	MS_Ensure(false);
	return false;
}

void UMS_ItemUnit::DestroyUnitActor()
{
	Super::DestroyUnitActor();
}

void UMS_ItemUnit::ChangeState(EMS_UnitState aUnitState) const
{
	Super::ChangeState(aUnitState);
}
