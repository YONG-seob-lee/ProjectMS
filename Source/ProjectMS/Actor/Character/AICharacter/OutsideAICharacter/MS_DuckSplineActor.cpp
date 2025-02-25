// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_DuckSplineActor.h"

#include "Components/SplineComponent.h"

AMS_DuckSplineActor::AMS_DuckSplineActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	SplineComponent = CreateDefaultSubobject<USplineComponent>("SplineComponent");
	if(SplineComponent)
	{
		SplineComponent->SetupAttachment(SceneRootComponent);
	}
}

// Called every frame
void AMS_DuckSplineActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FVector AMS_DuckSplineActor::FindTangentClosestToWorldLocation(const FVector& aWorldLocation) const
{
	if(!SplineComponent)
	{
		return FVector::ZeroVector;
	}
	
	return SplineComponent->FindTangentClosestToWorldLocation(aWorldLocation, ESplineCoordinateSpace::World);
}

FVector AMS_DuckSplineActor::FindLocationClosestToWorldLocation(const FVector& aWorldLocation) const
{
	if(!SplineComponent)
	{
		return FVector::ZeroVector;
	}
	
	return SplineComponent->FindLocationClosestToWorldLocation(aWorldLocation, ESplineCoordinateSpace::World);
}

void AMS_DuckSplineActor::BeginPlay()
{
	Super::BeginPlay();
	
	const int32 SplinePoints = SplineComponent->GetNumberOfSplinePoints();
	StartPoint = SplineComponent->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::Type::World);
	EndPoint = SplineComponent->GetLocationAtSplinePoint(SplinePoints-1, ESplineCoordinateSpace::Type::World);
}