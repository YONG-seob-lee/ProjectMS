// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_CharacterUnitBase.h"

#include "Character/MS_CharacterBase.h"


TObjectPtr<AMS_CharacterBase> UMS_CharacterUnitBase::CreateCharacter(int32 aUnitTableId, int32 aChildTableId,
                                                                     const FVector& aPosition, const FRotator& aRotator)
{
	if (UClass* BPClass = GetBlueprintClass(aUnitTableId, aChildTableId))
	{
		const TObjectPtr<AMS_CharacterBase> NewCharacter = Cast<AMS_CharacterBase>(SpawnBlueprintActor(BPClass, aPosition, aRotator));
		if(IsValid(NewCharacter))
		{
			NewCharacter->Create(BPClass->GetName());
			return NewCharacter;
		}
	}

	return nullptr;
}
