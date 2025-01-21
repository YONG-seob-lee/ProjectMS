// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_UnitBase.h"
#include "MS_ActorUnitBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_ActorUnitBase : public UMS_UnitBase
{
	GENERATED_BODY()

protected:
	TObjectPtr<class AMS_Actor> CreateActor(int32 aUnitTableId, int32 aChildTableId, const FVector& aVector, const FRotator& aRotator);
};
