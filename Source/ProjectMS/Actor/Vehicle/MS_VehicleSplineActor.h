// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_Actor.h"
#include "MS_VehicleSplineActor.generated.h"

UCLASS()
class PROJECTMS_API AMS_VehicleSplineActor : public AMS_Actor
{
	GENERATED_BODY()

public:
	AMS_VehicleSplineActor(const FObjectInitializer& ObjectInitializer);

	virtual void Tick(float DeltaTime) override;
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class USplineComponent> SplineComponent = nullptr;
};
