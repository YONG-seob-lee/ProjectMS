
#include "MS_SplineActor.h"

#include "Components/SplineComponent.h"


AMS_SplineActor::AMS_SplineActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	SplineComponent = CreateDefaultSubobject<USplineComponent>("SplineComponent");
	if(SplineComponent)
	{
		SplineComponent->SetupAttachment(SceneRootComponent);
	}
}

void AMS_SplineActor::BeginPlay()
{
	Super::BeginPlay();
	
	const int32 SplinePoints = SplineComponent->GetNumberOfSplinePoints();
	StartPoint = SplineComponent->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::Type::World);
	EndPoint = SplineComponent->GetLocationAtSplinePoint(SplinePoints-1, ESplineCoordinateSpace::Type::World);
}

void AMS_SplineActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FVector AMS_SplineActor::FindTangentClosestToWorldLocation(const FVector& aWorldLocation) const
{
	if(!SplineComponent)
	{
		return FVector::ZeroVector;
	}
	
	return SplineComponent->FindTangentClosestToWorldLocation(aWorldLocation, ESplineCoordinateSpace::World);
}

FVector AMS_SplineActor::FindLocationClosestToWorldLocation(const FVector& aWorldLocation) const
{
	if(!SplineComponent)
	{
		return FVector::ZeroVector;
	}
	
	return SplineComponent->FindLocationClosestToWorldLocation(aWorldLocation, ESplineCoordinateSpace::World);
}

