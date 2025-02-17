// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_StaffBlackboardComponent.h"


UMS_StaffBlackboardComponent::UMS_StaffBlackboardComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UMS_StaffBlackboardComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UMS_StaffBlackboardComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                 FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

