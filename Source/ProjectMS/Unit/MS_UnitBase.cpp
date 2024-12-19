// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_UnitBase.h"

#include "UnitState/MS_UnitStateBase.h"
#include "CoreClass/StateMachine/MS_StateMachine.h"
#include "Manager_Both/MS_UnitManager.h"

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

bool UMS_UnitBase::CreateUnit(int32 aUnitTableId, const FVector& aPosition, const FRotator& aRotator)
{
	UnitHandle = aUnitTableId;
	
	return true;
}

void UMS_UnitBase::DestroyUnit()
{
	if(UnitStateMachine)
	{
		UnitStateMachine->Destroy();
		UnitStateMachine = nullptr;
	}
}

void UMS_UnitBase::CreateUnitStateMachine()
{
	UnitStateMachine = MS_NewObject<UMS_StateMachine>(this, UMS_StateMachine::StaticClass());
	MS_CHECK(UnitStateMachine);
	UnitStateMachine->Create();
}

void UMS_UnitBase::RegisterUnitState(EMS_UnitState aState, const FName& aName, TSubclassOf<UMS_StateBase> aClassType)
{
	MS_CHECK(UnitStateMachine);
	
	UnitStateMachine->RegisterState(static_cast<int8>(aState), aName, aClassType);
}

TObjectPtr<UMS_StateBase> UMS_UnitBase::GetCurrentUnitState() const
{
	MS_CHECK(UnitStateMachine);

	return UnitStateMachine->GetCurrentState();
}

void UMS_UnitBase::ChangeState(EMS_UnitState aUnitState) const
{
	if(UnitStateMachine == nullptr)
	{
		return;
	}
	
	UnitStateMachine->SetState(static_cast<uint8>(aUnitState));
}
