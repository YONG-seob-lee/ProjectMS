// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ModeManager.h"

#include "MS_Define.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "StateMachine/MS_StateMachine.h"
#include "Mode/ModeState/MS_ModeStateBase.h"


UMS_ModeManager::UMS_ModeManager()
{
	ModeManager = this;
}

UMS_ModeManager* UMS_ModeManager::GetInstance()
{
	return ModeManager;
}

void UMS_ModeManager::BuiltInInitialize()
{
}

void UMS_ModeManager::Initialize()
{
	CreateModeStateMachine();
}

void UMS_ModeManager::PostInitialize()
{
}

void UMS_ModeManager::PreFinalize()
{
}

void UMS_ModeManager::Finalize()
{
	DestroyModeStateMachine();
}

void UMS_ModeManager::BuiltInFinalize()
{
}

void UMS_ModeManager::Tick(float aDeltaTime)
{
}

void UMS_ModeManager::ChangeControllerMode(EMS_ControllerModeType aControllerModeType)
{
	ControllerModeType = aControllerModeType;
	
	switch(aControllerModeType)
	{
	case(EMS_ControllerModeType::Normal):
		{
			break;
		}
	case(EMS_ControllerModeType::Rotate):
		{
			ShowRotateWidget();
			break;
		}
	}

	OnChangeModeDelegate.Broadcast(ModeStateMachine == nullptr ? EMS_ModeState::None : GetCurrentModeStateId()
		, ControllerModeType);
}

void UMS_ModeManager::ShowRotateWidget()
{
	gWidgetMng.ShowRotateWidget();
}

void UMS_ModeManager::HideRotateWidget()
{
	gWidgetMng.HideRotateWidget();
}

void UMS_ModeManager::CreateModeStateMachine()
{
	ModeStateMachine = MS_NewObject<UMS_StateMachine>(this, UMS_StateMachine::StaticClass());
	MS_CHECK(ModeStateMachine);
	ModeStateMachine->AddToRoot();
	ModeStateMachine->Create();
}

void UMS_ModeManager::DestroyModeStateMachine()
{
	if (ModeStateMachine)
	{
		ModeStateMachine->Destroy();
		ModeStateMachine->RemoveFromRoot();
		ModeStateMachine = nullptr;
	}
}

void UMS_ModeManager::RegisterModeState(EMS_ModeState aModeState, const FName& aName, TSubclassOf<UMS_ModeStateBase> aClassType)
{
	MS_CHECK(ModeStateMachine);
	
	ModeStateMachine->RegisterState(static_cast<int8>(aModeState), aName, aClassType);
}

void UMS_ModeManager::UnregisterModeStates()
{
	if (ModeStateMachine)
	{
		ModeStateMachine->UnRegisterStates();
	}
}

TObjectPtr<UMS_ModeStateBase> UMS_ModeManager::GetCurrentModeState() const
{
	MS_CHECK(ModeStateMachine);
	
	return Cast<UMS_ModeStateBase>(ModeStateMachine->GetCurrentState());
}

EMS_ModeState UMS_ModeManager::GetCurrentModeStateId() const
{
	if (GetCurrentModeState() != nullptr)
	{
		return static_cast<EMS_ModeState>(GetCurrentModeState()->GetStateIndex());
	}

	return EMS_ModeState::None;
}

void UMS_ModeManager::ChangeState(EMS_ModeState aModeState)
{
	if(ModeStateMachine == nullptr)
	{
		return;
	}
	
	ModeStateMachine->SetState(static_cast<uint8>(aModeState));

	ChangeControllerMode(EMS_ControllerModeType::Normal);
}
