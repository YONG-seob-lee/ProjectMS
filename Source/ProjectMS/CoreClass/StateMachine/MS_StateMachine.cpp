// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_StateMachine.h"

#include "MS_StateBase.h"
#include "Utility/MS_Define.h"

void UMS_StateMachine::Create()
{
}

void UMS_StateMachine::Destroy()
{
	UnRegisterStates();
}

void UMS_StateMachine::Tick(float aDeltaTime)
{
	for(const auto& State : EntireState)
	{
		State.Value->Tick(aDeltaTime);
	}
}

void UMS_StateMachine::RegisterState(int8 aIndex, const FName& aName, const TSubclassOf<UMS_StateBase>& aSceneType, UObject* aOuter)
{
	if (EntireState.Contains(aIndex))
	{
		MS_ENSURE(false);
		return;
	}

	const TObjectPtr<UObject> CustomOuter = aOuter != nullptr ? aOuter : this;
	TObjectPtr<UMS_StateBase> State = MS_NewObject<UMS_StateBase>(CustomOuter, aSceneType);
	
	State->Initialize(aIndex, aName);
	EntireState.Emplace(aIndex, State);
}

void UMS_StateMachine::UnRegisterStates()
{
	for (auto& State : EntireState)
	{
		if (State.Value != nullptr)
		{
			State.Value->Finalize();
			MS_DeleteObject(State.Value);
		}
	}

	EntireState.Empty();
}

TObjectPtr<UMS_StateBase> UMS_StateMachine::GetCurrentState()
{
	const TObjectPtr<UMS_StateBase>* pCurrentStateBase = EntireState.Find(CurrentStateId);

	return pCurrentStateBase ? *pCurrentStateBase : nullptr;
}

void UMS_StateMachine::GetActiveStateId(TArray<int8>& aActiveState) const
{
	if(EntireState.IsEmpty())
	{
		return;
	}
	
	aActiveState.Empty();
	return EntireState.GenerateKeyArray(aActiveState);
}

void UMS_StateMachine::SetState(int32 aIndex, bool bInstant)
{
	if(bInstant)
	{
		SetState_Internal(aIndex);
	}
	else
	{
		ChangeStateId = aIndex;
	}
}

TObjectPtr<UMS_StateBase> UMS_StateMachine::GetState(int32 aIndex) const
{
	if(EntireState.Contains(aIndex))
	{
		return EntireState[aIndex];
	}

	return nullptr;
}

void UMS_StateMachine::SetState_Internal(uint8 aIndex)
{
	PreviousStateId = CurrentStateId;

	if(const TObjectPtr<UMS_StateBase> CurrentState = GetState(CurrentStateId))
	{
		CurrentState->OnExitState();
	}

	CurrentStateId = aIndex;

	if(const TObjectPtr<UMS_StateBase> NextState = GetState(aIndex))
	{
		NextState->OnBeginState();
	}
}
