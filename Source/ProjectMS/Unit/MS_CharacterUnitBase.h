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

public:
	virtual void Initialize(MS_Handle aUnitHandle, EMS_UnitType aUnitType, int32 aUnitTableId) override;
	virtual void Finalize() override;
	virtual void PostInitialize() override;
	virtual void Tick(float aDeltaTime) override;

	virtual bool CreateUnitActor(const FVector& aPosition, const FRotator& aRotator) override;
	virtual void DestroyUnitActor() override;

	virtual bool SetUnitCharacter(TObjectPtr<class AMS_CharacterBase> aUnitCharacter, bool bForced = false);

protected:
	TObjectPtr<class AMS_CharacterBase> CreateCharacter(const FVector& aPosition, const FRotator& aRotator);
	TObjectPtr<class AMS_CharacterBase> CreateCharacter(UClass* aClass, const FVector& aPosition, const FRotator& aRotator);

public:
	FORCEINLINE TObjectPtr<class AMS_CharacterBase> GetCharacter() const { return Character; }
	
private:
	UPROPERTY()
	TObjectPtr<class AMS_CharacterBase> Character = nullptr;
};
