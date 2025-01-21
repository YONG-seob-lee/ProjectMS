// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ActorUnitBase.h"

#include "MS_Actor.h"

TObjectPtr<AMS_Actor> UMS_ActorUnitBase::CreateActor(int32 aUnitTableId, int32 aChildTableId, const FVector& aVector,
                                                     const FRotator& aRotator)
{
	if (Actor != nullptr)
	{
		MS_LOG_Verbosity(Error, TEXT("[%s] Actor already exist"), *MS_FUNC_STRING);
		MS_Ensure(false);
	}
	
	if (UClass* BPClass = GetBlueprintClass(aUnitTableId, aChildTableId))
	{
		Actor = Cast<AMS_Actor>(MS_SpawnActor(BPClass, aVector, aRotator));
		if(IsValid(Actor))
		{
			Actor->Create(BPClass->GetName());
			return Actor;
		}
	}

	MS_LOG_Verbosity(Error, TEXT("[%s] Actor not created"), *MS_FUNC_STRING);
	MS_Ensure(false);
	return nullptr;	
}
