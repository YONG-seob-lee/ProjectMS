// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_BasePlayerUnit.h"

#include "CoreClass/Controller/MS_PlayerController.h"
#include "Manager_Both/MS_UnitManager.h"

void UMS_BasePlayerUnit::Initialize()
{
	Super::Initialize();
}

void UMS_BasePlayerUnit::Finalize()
{
	Super::Finalize();
}

void UMS_BasePlayerUnit::PostInitialize()
{
	Super::PostInitialize();
}

void UMS_BasePlayerUnit::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
}

bool UMS_BasePlayerUnit::CreateUnit(int32 aUnitTableId, const FVector& aPosition, const FRotator& aRotator)
{
	Super::CreateUnit(aUnitTableId, aPosition, aRotator);
	
	UnitData = gTableMng.GetTableRowData<FMS_ResourceUnit>(EMS_TableDataType::ResourceUnit, aUnitTableId);
	if(UnitData == nullptr)
	{
		return false;
	}
	
	const FString BPPath = gTableMng.GetPath(EMS_TableDataType::BasePathBPFile, UnitData->Base_Path, true);

	if(const TObjectPtr<AMS_CharacterBase> NewCharacter = gUnitMng.CreateCharacter(BPPath, aPosition, aRotator))
	{
		Character = NewCharacter;
		Character->SetOwnerUnitBase(this);
		
		// if(const TObjectPtr<UMS_AnimInstance> AnimInstance = Cast<UMS_AnimInstance>(GetAnimInstance()))
		// {
		// 	AnimInstance->InitializeAnimation();
		// }
		return true;
	}

	return false;
}

void UMS_BasePlayerUnit::DestroyUnit()
{
	Super::DestroyUnit();
}

void UMS_BasePlayerUnit::SetLodScaleValues(float aCullDistanceScale, float aOutLineCullDistanceScale, bool bVisibleOutLine) const
{
	if(Character)
	{
		Character->SetLodScaleValues(aCullDistanceScale, aOutLineCullDistanceScale, bVisibleOutLine);
	}
}

void UMS_BasePlayerUnit::ChangeState(EMS_UnitState aActionType) const
{
	if(APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		PlayerController->FlushPressedKeys();
	}
	
	Super::ChangeState(aActionType);
}
