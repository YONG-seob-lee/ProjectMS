// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_Prop_Structure.h"


AMS_Prop_Structure::AMS_Prop_Structure()
{
	PrimaryActorTick.bCanEverTick = true;

	// Property
	PropType = EMS_PropType::Structure;
}

void AMS_Prop_Structure::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// Component
	GetComponents(UMeshComponent::StaticClass(), MeshComponents);
}

void AMS_Prop_Structure::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMS_Prop_Structure::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

