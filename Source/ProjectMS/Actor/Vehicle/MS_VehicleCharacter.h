// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/MS_CharacterBase.h"
#include "MS_VehicleCharacter.generated.h"

UCLASS()
class PROJECTMS_API AMS_VehicleCharacter : public AMS_CharacterBase
{
	GENERATED_BODY()

public:
	AMS_VehicleCharacter();

	virtual void PostInitializeComponents() override;
	virtual void Tick(float DeltaTime) override;

	void TurnOnLight();
	void TurnOffLight();
	
protected:
	virtual void BeginPlay() override;

private:
	TObjectPtr<class AMS_VehicleSplineActor> FindNearestSpline() const;

	TWeakObjectPtr<AMS_VehicleSplineActor> NearestSpline = nullptr;

	UPROPERTY(EditAnywhere)
	float VehicleVelocity = 5.f;

	UPROPERTY(EditAnywhere)
	float FrontLightDistance = 140.f;

	UPROPERTY()
	TArray<class USpotLightComponent*> SpotLightComponents = {};
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> VehicleMeshComponent = nullptr;
};
