// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_UnitBase.h"

#include "UnitState/MS_UnitStateBase.h"
#include "CoreClass/StateMachine/MS_StateMachine.h"
#include "Manager_Both/MS_UnitManager.h"
#include "Table/Caches/MS_ResourceUnitCacheTable.h"


void UMS_UnitBase::Initialize(MS_Handle aUnitHandle, int32 aUnitTableId, int32 aChildTableId)
{
	// Unit Handle
	UnitHandle = aUnitHandle;
	
	if (UnitHandle == InvalidUnitHandle)
	{
		MS_LOG_VERBOSITY(Error, TEXT("[%s] Unit Handle is invalid"), *MS_FUNC_STRING);
		MS_ENSURE(false);

		return;
	}

	// Table
	UnitTableId = aUnitTableId;
	if (UnitTableId == INDEX_NONE)
	{
		MS_LOG_VERBOSITY(Error, TEXT("[%s] UnitTableId is invalid"), *MS_FUNC_STRING);
		MS_ENSURE(false);

		return;
	}

	ChildTableId = aChildTableId;

	// Table Data Cache
	ResourceUnitData = gTableMng.GetTableRowData<FMS_ResourceUnit>(EMS_TableDataType::ResourceUnit, aUnitTableId);
	if(ResourceUnitData == nullptr)
	{
		MS_LOG_VERBOSITY(Error, TEXT("[%s] ResourceUnitData is nullptr [UnitTableId : %d]"), *MS_FUNC_STRING, aUnitTableId);
		MS_ENSURE(false);
	}
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
	if (UnitTableId == INDEX_NONE)
	{
		MS_LOG_VERBOSITY(Error, TEXT("[%s] UnitTableId is invalid"), *MS_FUNC_STRING);
		MS_ENSURE(false);

		return false;
	}

	if (ChildTableId == INDEX_NONE)
	{
		MS_LOG_VERBOSITY(Error, TEXT("[%s] ChildTableId is invalid"), *MS_FUNC_STRING);
		MS_ENSURE(false);

		return false;
	}
	
	if(ResourceUnitData == nullptr)
	{
		MS_LOG_VERBOSITY(Error, TEXT("[%s] ResourceUnitData is nullptr"), *MS_FUNC_STRING);
		MS_ENSURE(false);
		
		return false;
	}
	
	return true;
}

void UMS_UnitBase::DestroyUnitActor()
{
}

UClass* UMS_UnitBase::GetBlueprintClass() const
{
	if (UnitTableId == INDEX_NONE)
	{
		MS_LOG_VERBOSITY(Error, TEXT("[%s] UnitTableId is None"), *MS_FUNC_STRING);
		MS_ENSURE(false);

		return nullptr;
	}

	if (ChildTableId == INDEX_NONE)
	{
		MS_LOG_VERBOSITY(Error, TEXT("[%s] ChildTableId is None"), *MS_FUNC_STRING);
		MS_ENSURE(false);

		return nullptr;
	}
	
	TObjectPtr<UMS_CacheTable> CacheTable = gTableMng.GetCacheTable(EMS_TableDataType::ResourceUnit);
	if (UMS_ResourceUnitCacheTable* ResourceUnitCacheTable = Cast<UMS_ResourceUnitCacheTable>(CacheTable))
	{
		return ResourceUnitCacheTable->GetBlueprintClass(UnitTableId, ChildTableId);
	}

	return nullptr;
}

TObjectPtr<AActor> UMS_UnitBase::MS_SpawnActor(UClass* aClass, const FVector& Pos, const FRotator& Rot,
	bool bNeedRootComponent, ESpawnActorCollisionHandlingMethod Method) const
{
	if (!IsValid(aClass))
	{
		MS_LOG_VERBOSITY(Error, TEXT("[%s] Class is not valid."), *MS_FUNC_STRING);
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
