// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ActorUnitBase.h"

#include "MS_Actor.h"


void UMS_ActorUnitBase::Initialize(MS_Handle aUnitHandle, EMS_UnitType aUnitType, int32 aUnitTableId)
{
	Super::Initialize(aUnitHandle, aUnitType, aUnitTableId);
}

void UMS_ActorUnitBase::Finalize()
{
	Super::Finalize();
}

void UMS_ActorUnitBase::PostInitialize()
{
	Super::PostInitialize();
}

void UMS_ActorUnitBase::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
}

bool UMS_ActorUnitBase::CreateUnitActor(const FVector& aPosition, const FRotator& aRotator)
{
	if (Actor != nullptr)
	{
		MS_LOG_VERBOSITY(Error, TEXT("[%s] Actor already exist"), *MS_FUNC_STRING);
		MS_ENSURE(false);
	}
	
	if (Super::CreateUnitActor(aPosition, aRotator))
	{
		Actor = CreateActor(aPosition, aRotator);
		
		if(IsValid(Actor))
		{
			Actor->SetOwnerUnitBase(this);
			
			return true;
		}
	}
	
	MS_ENSURE(false);
	return false;
}

void UMS_ActorUnitBase::DestroyUnitActor()
{
	if(IsValid(Actor))
	{
		Actor->Destroy();
		Actor = nullptr;
	}
	
	Super::DestroyUnitActor();
}

bool UMS_ActorUnitBase::SetUnitActor(TObjectPtr<AMS_Actor> aUnitActor, bool bForced)
{
	if (Actor != nullptr)
	{
		if (!bForced)
		{
			MS_LOG_VERBOSITY(Error, TEXT("[%s] Actor already exist"), *MS_FUNC_STRING);
			MS_ENSURE(false);

			return false;
		}

		DestroyUnitActor();
	}
	
	if(IsValid(aUnitActor))
	{
		Actor = aUnitActor;
		Actor->SetOwnerUnitBase(this);
			
		return true;
	}

	MS_ENSURE(false);
	return false;
}

FVector UMS_ActorUnitBase::GetUnitPosition() const
{
	if(IsValid(Actor))
	{
		return Actor->GetActorLocation();
	}

	return FVector();
}

TObjectPtr<AMS_Actor> UMS_ActorUnitBase::CreateActor(const FVector& aVector, const FRotator& aRotator)
{
	if (UClass* BPClass = GetBlueprintClass())
	{
		TObjectPtr<AMS_Actor> NewActor = Cast<AMS_Actor>(MS_SpawnActor(BPClass, aVector, aRotator));
		if(IsValid(NewActor))
		{
			FVector Test = NewActor->GetActorLocation();
			
			NewActor->Create(BPClass->GetName());
			return NewActor;
		}
	}

	MS_LOG_VERBOSITY(Error, TEXT("[%s] Actor not created"), *MS_FUNC_STRING);
	MS_ENSURE(false);
	return nullptr;	
}
