// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_OutsideBlackboardComponent.h"

UMS_OutsideBlackboardComponent::UMS_OutsideBlackboardComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UMS_OutsideBlackboardComponent::BeginPlay()
{
	Super::BeginPlay();

	PrimaryComponentTick.bCanEverTick = true;
	RegisterComponent();
	PrimaryComponentTick.RegisterTickFunction(GetComponentLevel());
}