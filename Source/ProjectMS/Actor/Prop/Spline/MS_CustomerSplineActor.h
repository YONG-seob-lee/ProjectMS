// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_SplineActor.h"
#include "MS_CustomerSplineActor.generated.h"

UCLASS()
class PROJECTMS_API AMS_CustomerSplineActor : public AMS_SplineActor
{
	GENERATED_BODY()

public:
	AMS_CustomerSplineActor(const FObjectInitializer& ObjectInitializer);
};
