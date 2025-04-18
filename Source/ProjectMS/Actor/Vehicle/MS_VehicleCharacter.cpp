﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_VehicleCharacter.h"

#include "MS_ActorUnitBase.h"
#include "Kismet/KismetMathLibrary.h"
#include "Manager_Both/MS_UnitManager.h"
#include "DrawDebugHelpers.h"
#include "Components/CapsuleComponent.h"
#include "Components/SpotLightComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Prop/Spline/MS_VehicleSplineActor.h"


// Sets default values
AMS_VehicleCharacter::AMS_VehicleCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	VehicleMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("VehicleMeshComponent");
	if(VehicleMeshComponent)
	{
		VehicleMeshComponent->SetupAttachment(GetCapsuleComponent());
	}
	
	UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
	if(MovementComponent)
	{
		MovementComponent->bRunPhysicsWithNoController = true;
		MovementComponent->RotationRate = FRotator(0.f, 360.f, 0.f);
		MovementComponent->bUseControllerDesiredRotation = true;
		MovementComponent->bOrientRotationToMovement = true;
	}
}

void AMS_VehicleCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	GetComponents(USpotLightComponent::StaticClass(), SpotLightComponents);

	for(const auto& SpotLight : SpotLightComponents)
	{
		FTransform SpotLightTransform = SpotLight->GetRelativeTransform();
		SpotLightTransform.SetLocation(FVector(FrontLightDistance, SpotLightTransform.GetLocation().Y, SpotLightTransform.GetLocation().Z));
	}
}

// Called every frame
void AMS_VehicleCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
	if(MovementComponent)
	{
		if (NearestSpline != nullptr)
		{
			const FVector CurrentVehicleLocation = GetActorLocation();
			const FVector TangentLocation = NearestSpline->FindTangentClosestToWorldLocation(CurrentVehicleLocation);
			const FRotator MoveNextRotation = TangentLocation.Rotation();
			const FVector ClosetLocation = NearestSpline->FindLocationClosestToWorldLocation(CurrentVehicleLocation);
			SetActorLocation(ClosetLocation + TangentLocation.GetSafeNormal() * VehicleVelocity);
			SetActorRotation(MoveNextRotation);
		}
	}
}

void AMS_VehicleCharacter::TurnOnLight()
{
	for(const auto& SpotLightComponent : SpotLightComponents)
	{
		SpotLightComponent->SetHiddenInGame(false);
	}
}

void AMS_VehicleCharacter::TurnOffLight()
{
	for(const auto& SpotLightComponent : SpotLightComponents)
	{
		SpotLightComponent->SetHiddenInGame(true);
	}
}


// Called when the game starts or when spawned
void AMS_VehicleCharacter::BeginPlay()
{
	Super::BeginPlay();

	NearestSpline = FindNearestSpline();
}

TObjectPtr<AMS_VehicleSplineActor> AMS_VehicleCharacter::FindNearestSpline() const
{
	TArray<TWeakObjectPtr<UMS_UnitBase>> VehicleSplineUnits; 
	gUnitMng.GetUnits(EMS_UnitType::CarSpline, VehicleSplineUnits);

	const int32 TargetSpline = FMath::RandRange(0, VehicleSplineUnits.Num() - 1);
	if(VehicleSplineUnits.IsValidIndex(TargetSpline) == false)
	{
		return nullptr;
	}

	const TObjectPtr<UMS_ActorUnitBase> VehicleUnit = Cast<UMS_ActorUnitBase>(VehicleSplineUnits[TargetSpline]);
	TObjectPtr<AMS_VehicleSplineActor> VehicleSplineActor = Cast<AMS_VehicleSplineActor>(VehicleUnit->GetActor());
	return VehicleSplineActor;
}