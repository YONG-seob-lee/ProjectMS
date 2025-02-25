// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_SplineActor.h"
#include "MS_VehicleSplineActor.generated.h"

UCLASS()
class PROJECTMS_API AMS_VehicleSplineActor : public AMS_SplineActor
{
	GENERATED_BODY()

public:
	AMS_VehicleSplineActor(const FObjectInitializer& ObjectInitializer);
};
