// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_MovingBoxComponent.h"


UMS_MovingBoxComponent::UMS_MovingBoxComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	BoxExtent = FVector(50.f, 50.f, 70.f);
}

void UMS_MovingBoxComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UMS_MovingBoxComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

