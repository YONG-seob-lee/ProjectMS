// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_UnitBase.h"

#include "BasicClass/StateMachine/MS_StateMachine.h"

void UMS_UnitBase::Initialize()
{
}

void UMS_UnitBase::Finalize()
{
	DestroyUnit();
}

void UMS_UnitBase::PostInitialize()
{
}

void UMS_UnitBase::Tick(float aDeltaTime)
{
}

bool UMS_UnitBase::CreateUnit(int32 aUnitTableId, const FVector& aPos, const FRotator& aRot)
{
	UnitHandle = aUnitTableId;
	// UnitData = gTableMng.GetTableRowData<FMS_ResourceUnit>(EITT_TableDataType::Resource_Unit, ResourceUnitTableId);
	// if(ResourceUnitData == nullptr)
	// {
	// 	return false;
	// }

	// const FString BPPath = gTableMng.GetPath(EITT_TableDataType::BasePath_BP_File, ResourceUnitData->Base_Path, true);
	// if(const TObjectPtr<AITT_CharacterBase> NewCharacter = gUnitMng.CreateCharacter(BPPath, Pos, Rot))
	// {
	// 	CharacterBase = NewCharacter;
	// 	CharacterBase->SetOwnerUnitBase(this);
	// 	
	// 	if(const TObjectPtr<UITT_AnimInstance> AnimInstance = Cast<UITT_AnimInstance>(GetAnimInstance()))
	// 	{
	// 		AnimInstance->SetMoveSpeedInfo(ResourceUnitData->WalkSpeed, ResourceUnitData->RunSpeed);
	// 		AnimInstance->InitializeAnimation();
	// 	}
	// }
	
	return true;
}

void UMS_UnitBase::DestroyUnit()
{
}

void UMS_UnitBase::ChangeActionState(EMS_UnitActionState aActionType) const
{
	if(ActionStateMachine == nullptr)
	{
		return;
	}
	
	ActionStateMachine->SetState(static_cast<uint8>(aActionType));
}
