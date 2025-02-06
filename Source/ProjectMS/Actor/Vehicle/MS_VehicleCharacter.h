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

	virtual void Tick(float DeltaTime) override;
	
protected:
	virtual void BeginPlay() override;

private:
	TObjectPtr<class AMS_VehicleSplineActor> FindNearestSpline() const;

	TWeakObjectPtr<AMS_VehicleSplineActor> NearestSpline = nullptr;

	UPROPERTY(EditAnywhere)
	float VehicleVelocity = 5.f;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent = nullptr;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UCharacterMovementComponent> MovementComponent = nullptr;
	
};
