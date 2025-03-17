// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_UnitBase.h"

#include "Controller/MS_PlayerController.h"
#include "Manager_Both/MS_TableManager.h"
#include "PlayerState/MS_PlayerState.h"
#include "UnitState/MS_UnitStateBase.h"
#include "CoreClass/StateMachine/MS_StateMachine.h"
#include "Manager_Both/MS_UnitManager.h"


void UMS_UnitBase::Initialize(MS_Handle aUnitHandle, EMS_UnitType aUnitType, int32 aTableId)
{
	// Unit Handle
	UnitHandle = aUnitHandle;
	UnitType = aUnitType;
	if (UnitHandle == InvalidUnitHandle)
	{
		MS_ERROR(TEXT("[%s] Unit Handle is invalid"), *MS_FUNC_STRING);
		MS_ENSURE(false);

		return;
	}

	// Table
	TableId = aTableId;
}

void UMS_UnitBase::Finalize()
{
	DestroyUnitActor();
	
	if(UnitStateMachine)
	{
		UnitStateMachine->Destroy();
		UnitStateMachine = nullptr;
	}

	UnitHandle = InvalidUnitHandle;
}

void UMS_UnitBase::PostInitialize()
{
}

void UMS_UnitBase::Tick(float aDeltaTime)
{
}

void UMS_UnitBase::DestroyUnit()
{
	gUnitMng.DestroyUnit(UnitHandle);
}

bool UMS_UnitBase::CreateUnitActor(const FVector& aPosition, const FRotator& aRotator)
{
	if (TableId == INDEX_NONE)
	{
		MS_ERROR(TEXT("[%s] UnitTableId is invalid"), *MS_FUNC_STRING);
		MS_ENSURE(false);

		return false;
	}
	return true;
}

void UMS_UnitBase::DestroyUnitActor()
{
}

int32 UMS_UnitBase::GetBlueprintPathId() const
{
	MS_ERROR(TEXT("[%s] Please Override this Function."), *MS_FUNC_STRING);
	MS_ENSURE(false);
	
	return INDEX_NONE;
}

UClass* UMS_UnitBase::GetBlueprintClass() const
{
	int32 BPPathId = GetBlueprintPathId();
	if (BPPathId == INDEX_NONE)
	{
		return nullptr;
	}

	return UMS_TableManager::GetClassByTablePathId(BPPathId);
}

TObjectPtr<AActor> UMS_UnitBase::MS_SpawnActor(UClass* aClass, const FVector& Pos, const FRotator& Rot,
                                               bool bNeedRootComponent, ESpawnActorCollisionHandlingMethod Method) const
{
	if (!IsValid(aClass))
	{
		MS_ERROR(TEXT("[%s] Class is not valid."), *MS_FUNC_STRING);
		MS_ENSURE(false);
		
		return nullptr;
	}
	
	const TObjectPtr<UWorld> World = GetWorld();
	if(!IsValid(World))
	{
		return nullptr;	
	}
			
	FActorSpawnParameters Parameters;
	Parameters.OverrideLevel = World->GetCurrentLevel();
	Parameters.SpawnCollisionHandlingOverride = Method;
	const TObjectPtr<AActor> ResultActor = World->SpawnActor(aClass, &Pos, &Rot, Parameters);

	if(ResultActor)
	{
		//ResultActor->SetActorLabel(GetBPNameFromFullPath(BlueprintPath));

		if(bNeedRootComponent && ResultActor->GetRootComponent() == nullptr)
		{
			const TObjectPtr<USceneComponent> RootComponent = MS_NewObject<USceneComponent>(ResultActor, USceneComponent::GetDefaultSceneRootVariableName(), RF_Transactional);
			RootComponent->Mobility = EComponentMobility::Movable;

			ResultActor->SetRootComponent(RootComponent);
			ResultActor->AddInstanceComponent(RootComponent);

			RootComponent->RegisterComponent();
		}
	}

	return ResultActor != nullptr ? ResultActor : nullptr;
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

AMS_PlayerState* UMS_UnitBase::GetPlayerState() const
{
	UWorld* World = GetWorld();
	if (!IsValid(World))
	{
		return nullptr;
	}

	AMS_PlayerController* PlayerController = World->GetFirstPlayerController<AMS_PlayerController>();
	if (!IsValid(PlayerController))
	{
		return nullptr;
	}
	
	return PlayerController->GetPlayerState<AMS_PlayerState>();
}