// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_VehicleSplineActor.h"

#include "Components/SplineComponent.h"


// Sets default values
AMS_VehicleSplineActor::AMS_VehicleSplineActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SplineComponent = CreateDefaultSubobject<USplineComponent>("SplineComponent");
	if(SplineComponent)
	{
		SplineComponent->SetupAttachment(SceneRootComponent);
	}
}

// Called when the game starts or when spawned
void AMS_VehicleSplineActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMS_VehicleSplineActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FVector AMS_VehicleSplineActor::FindTangentClosestToWorldLocation(const FVector& aWorldLocation) const
{
	if(!SplineComponent)
	{
		return FVector::ZeroVector;
	}
	
	return SplineComponent->FindTangentClosestToWorldLocation(aWorldLocation, ESplineCoordinateSpace::World);
}

FVector AMS_VehicleSplineActor::FindLocationClosestToWorldLocation(const FVector& aWorldLocation) const
{
	if(!SplineComponent)
	{
		return FVector::ZeroVector;
	}
	
	return SplineComponent->FindLocationClosestToWorldLocation(aWorldLocation, ESplineCoordinateSpace::World);
}

