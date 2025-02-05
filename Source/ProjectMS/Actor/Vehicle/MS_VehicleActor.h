// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_Actor.h"
#include "MS_VehicleActor.generated.h"

UCLASS()
class PROJECTMS_API AMS_VehicleActor : public AMS_Actor
{
	GENERATED_BODY()

public:
	AMS_VehicleActor(const FObjectInitializer& ObjectInitializer);

	virtual void Tick(float DeltaTime) override;
	
protected:
	virtual void BeginPlay() override;

private:
	TObjectPtr<class AMS_VehicleSplineActor> FindNearestSpline() const;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent = nullptr;
};
