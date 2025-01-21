// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_Furniture.h"


AMS_Furniture::AMS_Furniture(const FObjectInitializer& aObjectInitializer)
	: Super(aObjectInitializer)
{
	// Property
	PropType = EMS_PropType::Furniture;
}

void AMS_Furniture::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AMS_Furniture::BeginPlay()
{
	Super::BeginPlay();
}

