// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_UnitBase.h"
#include "MS_CharacterUnitBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_CharacterUnitBase : public UMS_UnitBase
{
	GENERATED_BODY()

protected:
	TObjectPtr<class AMS_CharacterBase> CreateCharacter(int32 aUnitTableId, int32 aChildTableId, const FVector& aPosition, const FRotator& aRotator);
	TObjectPtr<class AMS_CharacterBase> CreateCharacter(UClass* aClass, const FVector& aPosition, const FRotator& aRotator);

public:
	FORCEINLINE TObjectPtr<class AMS_CharacterBase> GetCharacter() const { return Character; }
	
private:
	UPROPERTY()
	TObjectPtr<class AMS_CharacterBase> Character = nullptr;
};
