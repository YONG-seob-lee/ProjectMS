// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_AICharacter.h"
#include "MathUtility/MS_MathUtility.h"
#include "MS_MarketAICharacter.generated.h"

UCLASS()
class PROJECTMS_API AMS_MarketAICharacter : public AMS_AICharacter
{
	GENERATED_BODY()

public:
	AMS_MarketAICharacter();

	virtual void PreInitializeComponents() override;
	virtual void PostInitializeComponents() override;
	
	virtual void BeginPlay() override;
	virtual void Tick(float aDeltaTime) override;


	EMS_Direction GetWalkingDirection() const { return WalkingDirection; }
	void SetWalkingDirection(EMS_Direction aWalkingDirection, FVector2D aPathLocation, bool aStopInPathLocation);
	
	
protected:
	// Component
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class UMS_MovingBoxComponent*> MovingBoxComponents;

	// Property
	UPROPERTY(EditAnywhere)
	float DuckVelocity = 50.f;
	
	// Walking Progress
	UPROPERTY()
	FVector CacheLocation;
	
	UPROPERTY()
	EMS_Direction WalkingDirection = EMS_Direction::None;
	
	UPROPERTY()
	FVector2D PathLocation;

	UPROPERTY()
	bool bStopInPathLocation;
};
