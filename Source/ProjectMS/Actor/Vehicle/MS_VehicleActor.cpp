// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_VehicleActor.h"

#include "MS_ActorUnitBase.h"
#include "MS_VehicleSplineActor.h"
#include "Manager_Both/MS_UnitManager.h"


// Sets default values
AMS_VehicleActor::AMS_VehicleActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
}

// Called every frame
void AMS_VehicleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


// Called when the game starts or when spawned
void AMS_VehicleActor::BeginPlay()
{
	Super::BeginPlay();

	
}

TObjectPtr<AMS_VehicleSplineActor> AMS_VehicleActor::FindNearestSpline() const
{
	TArray<TObjectPtr<UMS_UnitBase>> VehicleSplineUnits; 
	gUnitMng.GetUnit(EMS_UnitType::Spline, VehicleSplineUnits);

	float DistanceMin = 0.f;
	TObjectPtr<UMS_ActorUnitBase> NearestSpline = nullptr;
	
	for(const auto& SplineUnit : VehicleSplineUnits)
	{
		if(const TObjectPtr<UMS_ActorUnitBase> SplineActor = Cast<UMS_ActorUnitBase>(SplineUnit))
		{
			const float Distance = FVector::Distance(GetActorLocation(), SplineActor->GetUnitPosition());
			if(DistanceMin == 0.f || DistanceMin > Distance)
			{
				DistanceMin = Distance;
				NearestSpline = SplineActor;
			}
		}
	}

	TObjectPtr<AMS_VehicleSplineActor> VehicleSplineActor = Cast<AMS_VehicleSplineActor>(NearestSpline->GetActor());
	return VehicleSplineActor;
}