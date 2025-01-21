// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ItemUnit.h"

#include "Manager_Both/MS_UnitManager.h"

void UMS_ItemUnit::Initialize(MS_Handle aUnitHandle)
{
	Super::Initialize(aUnitHandle);
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

bool UMS_ItemUnit::CreateUnit(int32 aUnitTableId, int32 aChildTableId, const FVector& aPosition, const FRotator& aRotator)
{
	Super::CreateUnit(aUnitTableId, aChildTableId, aPosition, aRotator);

	// ToDo
	ItemData = gTableMng.GetTableRowData<FMS_ItemData>(EMS_TableDataType::ItemData, aUnitTableId);
	if(ItemData == nullptr)
	{
		return false;
	}
	
	if(const TObjectPtr<AMS_Actor> NewActor = CreateActor(aUnitTableId, aChildTableId, aPosition, aRotator))
	{
		Actor = NewActor;
		Actor->SetOwnerUnitBase(this);
		
		// if(const TObjectPtr<UMS_AnimInstance> AnimInstance = Cast<UMS_AnimInstance>(GetAnimInstance()))
		// {
		// 	AnimInstance->InitializeAnimation();
		// }
		return true;
	}

	return false;
}

void UMS_ItemUnit::DestroyUnit()
{
	Super::DestroyUnit();
}

void UMS_ItemUnit::ChangeState(EMS_UnitState aUnitState) const
{
	Super::ChangeState(aUnitState);
}
