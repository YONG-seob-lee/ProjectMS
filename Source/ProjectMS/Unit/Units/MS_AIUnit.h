// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_CharacterUnitBase.h"
#include "MS_AIUnit.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_AIUnit : public UMS_CharacterUnitBase
{
	GENERATED_BODY()
public:
	virtual void Initialize(MS_Handle aUnitHandle, EMS_UnitType aUnitType, int32 aUnitTableId) override;
	virtual void Finalize() override;
	virtual void PostInitialize() override;

protected:
	virtual UClass* GetBlueprintClass() const override;
	
private:
	UPROPERTY()
	TObjectPtr<class AMS_AIController> AIController = nullptr;

	UPROPERTY()
	TObjectPtr<class UBlackboardComponent> BlackboardComponent = nullptr;
};
