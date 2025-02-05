// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_VehicleSplineActor.h"

#include "Components/SplineComponent.h"


// Sets default values
AMS_VehicleSplineActor::AMS_VehicleSplineActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
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

