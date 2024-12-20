// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_Prop_Furniture.h"


AMS_Prop_Furniture::AMS_Prop_Furniture()
{
	PrimaryActorTick.bCanEverTick = true;

	// Property
	PropType = EMS_PropType::Furniture;
}

void AMS_Prop_Furniture::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// Component
	GetComponents(UMeshComponent::StaticClass(), MeshComponents);
}

void AMS_Prop_Furniture::BeginPlay()
{
	Super::BeginPlay();
}

void AMS_Prop_Furniture::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

