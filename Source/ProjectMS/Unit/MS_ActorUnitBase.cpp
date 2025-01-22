// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ActorUnitBase.h"

#include "MS_Actor.h"


void UMS_ActorUnitBase::Initialize(MS_Handle aUnitHandle, int32 aUnitTableId, int32 aChildTableId)
{
	Super::Initialize(aUnitHandle, aUnitTableId, aChildTableId);
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
		MS_LOG_Verbosity(Error, TEXT("[%s] Actor already exist"), *MS_FUNC_STRING);
		MS_Ensure(false);
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
	
	MS_Ensure(false);
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

TObjectPtr<AMS_Actor> UMS_ActorUnitBase::CreateActor(const FVector& aVector, const FRotator& aRotator)
{
	if (UClass* BPClass = GetBlueprintClass())
	{
		TObjectPtr<AMS_Actor> NewActor = Cast<AMS_Actor>(MS_SpawnActor(BPClass, aVector, aRotator));
		if(IsValid(NewActor))
		{
			NewActor->Create(BPClass->GetName());
			return NewActor;
		}
	}

	MS_LOG_Verbosity(Error, TEXT("[%s] Actor not created"), *MS_FUNC_STRING);
	MS_Ensure(false);
	return nullptr;	
}
