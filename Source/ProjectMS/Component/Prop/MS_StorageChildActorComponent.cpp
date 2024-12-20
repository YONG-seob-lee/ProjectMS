// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_StorageChildActorComponent.h"


UMS_StorageChildActorComponent::UMS_StorageChildActorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UMS_StorageChildActorComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UMS_StorageChildActorComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                   FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

