// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_UnitBase.h"

#include "UnitState/MS_UnitStateBase.h"
#include "CoreClass/Controller/MS_PlayerController.h"
#include "CoreClass/StateMachine/MS_StateMachine.h"

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

void UMS_UnitBase::CreateUnitStateMachine()
{
	UnitStateMachine = MS_NewObject<UMS_StateMachine>(this, UMS_StateMachine::StaticClass());
	MS_CHECK(UnitStateMachine);
	UnitStateMachine->AddToRoot();
	UnitStateMachine->Create();
}

void UMS_UnitBase::RegisterUnitState(EMS_UnitState aState, const FName& aName, TSubclassOf<UMS_StateBase> aClassType)
{
	MS_CHECK(UnitStateMachine);
	
	UnitStateMachine->RegisterState(static_cast<int8>(aState), aName, aClassType);
	TObjectPtr<UMS_UnitStateBase> State = Cast<UMS_UnitStateBase>(UnitStateMachine->GetState(static_cast<int8>(aState)));
	MS_CHECK(State);
	
	const TObjectPtr<AMS_PlayerController> Controller = Cast<AMS_PlayerController>(GetOuter());
	MS_CHECK(Controller);
	State->WeakBindController(Controller);
}

TObjectPtr<UMS_StateBase> UMS_UnitBase::GetCurrentUnitState() const
{
	MS_CHECK(UnitStateMachine);

	return UnitStateMachine->GetCurrentState();
}

void UMS_UnitBase::SetLodScaleValues(float aCullDistanceScale, float aOutLineCullDistanceScale, bool bVisibleOutLine) const
{
	if(Character)
	{
		Character->SetLodScaleValues(aCullDistanceScale, aOutLineCullDistanceScale, bVisibleOutLine);
	}
}

void UMS_UnitBase::ChangeState(EMS_UnitState aUnitState) const
{
	if(UnitStateMachine == nullptr)
	{
		return;
	}
	
	UnitStateMachine->SetState(static_cast<uint8>(aUnitState));
}
