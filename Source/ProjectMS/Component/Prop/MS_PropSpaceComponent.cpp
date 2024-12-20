// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_PropSpaceComponent.h"


UMS_PropSpaceComponent::UMS_PropSpaceComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
	BoxExtent = FVector(25.f, 25.f, 0.f);
	
	BodyInstance.SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
}


void UMS_PropSpaceComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UMS_PropSpaceComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                           FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
