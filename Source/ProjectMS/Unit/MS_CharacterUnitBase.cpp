// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_CharacterUnitBase.h"

#include "Character/MS_CharacterBase.h"


void UMS_CharacterUnitBase::Initialize(MS_Handle aUnitHandle, EMS_UnitType aUnitType, int32 aUnitTableId)
{
	Super::Initialize(aUnitHandle, aUnitType, aUnitTableId);
}

void UMS_CharacterUnitBase::Finalize()
{
	Super::Finalize();
}

void UMS_CharacterUnitBase::PostInitialize()
{
	Super::PostInitialize();
}

void UMS_CharacterUnitBase::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
}

bool UMS_CharacterUnitBase::CreateUnitActor(const FVector& aPosition, const FRotator& aRotator)
{
	if (Character != nullptr)
	{
		MS_LOG_VERBOSITY(Error, TEXT("[%s] Character already exist"), *MS_FUNC_STRING);
		MS_ENSURE(false);
	}
	
	if (Super::CreateUnitActor(aPosition, aRotator))
	{
		Character = CreateCharacter(aPosition, aRotator);
		
		if(IsValid(Character))
		{
			Character->SetOwnerUnitBase(this);
			
			return true;
		}
	}
	
	MS_ENSURE(false);
	return false;
}

void UMS_CharacterUnitBase::DestroyUnitActor()
{
	if(IsValid(Character))
	{
		Character->Destroy();
		GetWorld()->DestroyActor(Character);
		Character = nullptr;
	}
	
	Super::DestroyUnitActor();
}

bool UMS_CharacterUnitBase::SetUnitCharacter(TObjectPtr<AMS_CharacterBase> aUnitCharacter, bool bForced)
{
	if (Character != nullptr)
	{
		if (!bForced)
		{
			MS_LOG_VERBOSITY(Error, TEXT("[%s] Character already exist"), *MS_FUNC_STRING);
			MS_ENSURE(false);

			return false;
		}

		DestroyUnitActor();
	}
	
	if(IsValid(aUnitCharacter))
	{
		Character = aUnitCharacter;
		Character->SetOwnerUnitBase(this);
			
		return true;
	}

	MS_ENSURE(false);
	return false;
}

TObjectPtr<AMS_CharacterBase> UMS_CharacterUnitBase::CreateCharacter(const FVector& aPosition, const FRotator& aRotator)
{
	if (UClass* BPClass = GetBlueprintClass())
	{
		return CreateCharacter(BPClass, aPosition, aRotator);
	}

	return nullptr;
}

TObjectPtr<AMS_CharacterBase> UMS_CharacterUnitBase::CreateCharacter(UClass* aClass, const FVector& aPosition,
	const FRotator& aRotator)
{
	TObjectPtr<AMS_CharacterBase> NewCharacter = Cast<AMS_CharacterBase>(MS_SpawnActor(aClass, aPosition, aRotator));
	if(IsValid(NewCharacter))
	{
		NewCharacter->Create(aClass->GetName());
		return NewCharacter;
	}
	
	MS_LOG_VERBOSITY(Error, TEXT("[%s] Character not created"), *MS_FUNC_STRING);
	MS_ENSURE(false);
	return nullptr;
}
