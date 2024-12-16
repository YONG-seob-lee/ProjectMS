// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_GridBoxComponent.h"


UMS_GridBoxComponent::UMS_GridBoxComponent()
	: GridLocationOffset(FVector::ZeroVector), PropSpaceType(EMS_PropSpaceType::None)
{
	PrimaryComponentTick.bCanEverTick = true;

	BoxExtent = FVector(25.f, 25.f, 25.f);
	
	BodyInstance.SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
}

void UMS_GridBoxComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UMS_GridBoxComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UMS_GridBoxComponent::OnRegisteredWithLevelPropDatas(FIntVector aGridPosition)
{
	GridPosition = aGridPosition;
}

