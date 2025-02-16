// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_BlackboardComponent.h"


UMS_BlackboardComponent::UMS_BlackboardComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UMS_BlackboardComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UMS_BlackboardComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

