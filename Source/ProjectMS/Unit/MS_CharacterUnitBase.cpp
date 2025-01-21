// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_CharacterUnitBase.h"

#include "Character/MS_CharacterBase.h"


TObjectPtr<AMS_CharacterBase> UMS_CharacterUnitBase::CreateCharacter(int32 aUnitTableId, int32 aChildTableId,
                                                                     const FVector& aPosition, const FRotator& aRotator)
{
	if (UClass* BPClass = GetBlueprintClass(aUnitTableId, aChildTableId))
	{
		return CreateCharacter(BPClass, aPosition, aRotator);
	}

	return nullptr;
}

TObjectPtr<AMS_CharacterBase> UMS_CharacterUnitBase::CreateCharacter(UClass* aClass, const FVector& aPosition,
	const FRotator& aRotator)
{
	if (Character != nullptr)
	{
		MS_LOG_Verbosity(Error, TEXT("[%s] Character already exist"), *MS_FUNC_STRING);
		MS_Ensure(false);
	}
	
	Character = Cast<AMS_CharacterBase>(MS_SpawnActor(aClass, aPosition, aRotator));
	if(IsValid(Character))
	{
		Character->Create(aClass->GetName());
		return Character;
	}
	
	MS_LOG_Verbosity(Error, TEXT("[%s] Character not created"), *MS_FUNC_STRING);
	MS_Ensure(false);
	return nullptr;
}
