// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ActorUnitBase.h"

#include "MS_Actor.h"

TObjectPtr<AMS_Actor> UMS_ActorUnitBase::CreateActor(int32 aUnitTableId, int32 aChildTableId, const FVector& aVector,
                                                     const FRotator& aRotator)
{
	if (UClass* BPClass = GetBlueprintClass(aUnitTableId, aChildTableId))
	{
		const TObjectPtr<AMS_Actor> NewActor = Cast<AMS_Actor>(SpawnBlueprintActor(BPClass, aVector, aRotator));
		if(IsValid(NewActor))
		{
			NewActor->Create(BPClass->GetName());
			return NewActor;
		}
	}

	return nullptr;	
}
