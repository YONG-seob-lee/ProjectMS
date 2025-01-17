// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_Furniture.h"


AMS_Furniture::AMS_Furniture()
{
	PrimaryActorTick.bCanEverTick = true;

	// Property
	PropType = EMS_PropType::Furniture;
}

void AMS_Furniture::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// Component
	GetComponents(UMeshComponent::StaticClass(), MeshComponents);
}

void AMS_Furniture::BeginPlay()
{
	Super::BeginPlay();
}

void AMS_Furniture::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

