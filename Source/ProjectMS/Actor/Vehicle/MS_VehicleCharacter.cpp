// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_VehicleCharacter.h"

#include "MS_ActorUnitBase.h"
#include "MS_VehicleSplineActor.h"
#include "Kismet/KismetMathLibrary.h"
#include "Manager_Both/MS_UnitManager.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
AMS_VehicleCharacter::AMS_VehicleCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	if(StaticMeshComponent)
	{
		StaticMeshComponent->SetupAttachment(GetRootComponent());
	}
	MovementComponent = CreateDefaultSubobject<UCharacterMovementComponent>("MovementComponent");
	if(MovementComponent)
	{
		MovementComponent->bRunPhysicsWithNoController = true;
		MovementComponent->SetIsReplicated(true);
		MovementComponent->RotationRate = FRotator(0.f, 360.f, 0.f);
		MovementComponent->bUseControllerDesiredRotation = true;
		MovementComponent->bOrientRotationToMovement = true;
	}
}

// Called every frame
void AMS_VehicleCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(MovementComponent)
	{
		const FVector CurrentVehicleLocation = GetActorLocation();
		const FVector TangentLocation = NearestSpline->FindTangentClosestToWorldLocation(CurrentVehicleLocation);
		const FRotator MoveNextRotation = TangentLocation.Rotation();
		const FVector ClosetLocation = NearestSpline->FindLocationClosestToWorldLocation(CurrentVehicleLocation);
		SetActorLocation(ClosetLocation + TangentLocation.GetSafeNormal() * VehicleVelocity);
		SetActorRotation(MoveNextRotation);
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
	TArray<TObjectPtr<UMS_UnitBase>> VehicleSplineUnits; 
	gUnitMng.GetUnits(EMS_UnitType::CarSpline, VehicleSplineUnits);

	float DistanceMin = 0.f;
	TObjectPtr<UMS_ActorUnitBase> NearestSplineUnit = nullptr;
	
	for(const auto& SplineUnit : VehicleSplineUnits)
	{
		if(const TObjectPtr<UMS_ActorUnitBase> SplineActorUnit = Cast<UMS_ActorUnitBase>(SplineUnit))
		{
			const float Distance = FVector::Distance(GetActorLocation(), SplineActorUnit->GetUnitPosition());
			if(DistanceMin == 0.f || DistanceMin > Distance)
			{
				DistanceMin = Distance;
				NearestSplineUnit = SplineActorUnit;
			}
		}
	}

	if(!NearestSplineUnit)
	{
		return nullptr;
	}

	TObjectPtr<AMS_VehicleSplineActor> VehicleSplineActor = Cast<AMS_VehicleSplineActor>(NearestSplineUnit->GetActor());
	return VehicleSplineActor;
}