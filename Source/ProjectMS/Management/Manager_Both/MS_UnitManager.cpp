// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_UnitManager.h"

#include "MS_BasePlayerUnit.h"
#include "MS_FurnitureUnit.h"
#include "MS_ItemUnit.h"
#include "Character/MS_CharacterBase.h"
#include "Unit/MS_UnitBase.h"

UMS_UnitManager::UMS_UnitManager()
{
	UnitManager = this;
	
	UnitType.Emplace(EMS_UnitType::BasePlayer, UMS_BasePlayerUnit::StaticClass());
	UnitType.Emplace(EMS_UnitType::Item, UMS_ItemUnit::StaticClass());
	UnitType.Emplace(EMS_UnitType::Furniture, UMS_FurnitureUnit::StaticClass());
}

void UMS_UnitManager::Finalize()
{
	DestroyAllUnits();
	
	Super::Finalize();
}

TObjectPtr<UMS_UnitBase> UMS_UnitManager::CreateUnit(int32 aUnitTableId, const TSubclassOf<UMS_UnitBase>& aUnitType, const FVector& aPosition, const FRotator& aRotator)
{
	const TObjectPtr<UMS_UnitBase> Unit = MS_NewObject<UMS_UnitBase>(this, aUnitType);
	Unit->Initialize();
	
	if(Unit->CreateUnit(aUnitTableId, aPosition, aRotator) == false)
	{
		return nullptr;
	}

	Unit->PostInitialize();

	// const MS_Handle NewUnitHandle = MakeUnitHandle(Unit);
	//
	// if(NewUnitHandle == InvalidUnitHandle)
	// {
	// 	return nullptr;
	// }

	// 일단 테이블 아이디로 사용
	Units.Add(aUnitTableId, Unit);
	
	return Unit;
}

TObjectPtr<UMS_UnitBase> UMS_UnitManager::CreateUnit(int32 aUnitTableId, int32 aUnitType, const FVector& aPosition, const FRotator& aRotator)
{
	const TSubclassOf<UMS_UnitBase>* UnitClassType = UnitType.Find(static_cast<EMS_UnitType>(aUnitType));
	if(UnitClassType == nullptr)
	{
		return nullptr; 
	}
	
	const TObjectPtr<UMS_UnitBase> Unit = MS_NewObject<UMS_UnitBase>(this, *UnitClassType);
	Unit->Initialize();
	
	if(Unit->CreateUnit(aUnitTableId, aPosition, aRotator) == false)
	{
		return nullptr;
	}

	Unit->PostInitialize();

	// const MS_Handle NewUnitHandle = MakeUnitHandle(Unit);
	//
	// if(NewUnitHandle == InvalidUnitHandle)
	// {
	// 	return nullptr;
	// }

	// 일단 테이블 아이디로 사용
	Units.Add(aUnitTableId, Unit);
	
	return Unit;
}

TObjectPtr<AMS_CharacterBase> UMS_UnitManager::CreateCharacter(const FString& aBlueprintPath, const FVector& aPosition, const FRotator& aRotator)
{
	const TObjectPtr<AMS_CharacterBase> NewCharacter = Cast<AMS_CharacterBase>(SpawnBlueprintActor(aBlueprintPath, aPosition, aRotator));
	if(IsValid(NewCharacter))
	{
		NewCharacter->Create(GetBPNameFromFullPath(aBlueprintPath));
		return NewCharacter;
	}

	return nullptr;	
}

TObjectPtr<AMS_Actor> UMS_UnitManager::CreateActor(const FString& aBlueprintPath, const FVector& aVector, const FRotator& aRotator)
{
	const TObjectPtr<AMS_Actor> NewActor = Cast<AMS_Actor>(SpawnBlueprintActor(aBlueprintPath, aVector, aRotator));
	if(IsValid(NewActor))
	{
		NewActor->Create(GetBPNameFromFullPath(aBlueprintPath));
		return NewActor;
	}

	return nullptr;	
}

TObjectPtr<AActor> UMS_UnitManager::SpawnBlueprintActor(const FString& BlueprintPath, const FVector& Pos, const FRotator& Rot, bool bNeedRootComponent, ESpawnActorCollisionHandlingMethod Method) const
{
	UClass* BlueprintClass = StaticLoadClass(UObject::StaticClass(), nullptr, *BlueprintPath);
	if(IsValid(BlueprintClass) == false)
	{
		MS_CHECK(false);
		MS_LOG(TEXT("Blueprint Path or Name is not Correct. Please Check Blueprint Path"));
		return nullptr;
	}
	
	const TObjectPtr<UWorld> World = GetWorld();
	if(IsValid(World) == false)
	{
		return nullptr;	
	}
			
	FActorSpawnParameters Parameters;
	Parameters.OverrideLevel = World->GetCurrentLevel();
	Parameters.SpawnCollisionHandlingOverride = Method;
	const TObjectPtr<AActor> ResultActor = World->SpawnActor(BlueprintClass, &Pos, &Rot, Parameters);

	if(ResultActor)
	{
		ResultActor->SetActorLabel(GetBPNameFromFullPath(BlueprintPath));

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

void UMS_UnitManager::DestroyAllUnits()
{
	for(auto& Unit : Units)
	{
		if(Unit.Value == nullptr)
		{
			continue;
		}

		Unit.Value->Finalize();
		Unit.Value->MarkAsGarbage();
		Unit.Value = nullptr;
	}

	Units.Empty();
}

UMS_UnitManager* UMS_UnitManager::GetInstance()
{
	return UnitManager;
}
