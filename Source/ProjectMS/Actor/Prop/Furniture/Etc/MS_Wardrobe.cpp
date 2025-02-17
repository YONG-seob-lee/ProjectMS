// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_Wardrobe.h"


AMS_Wardrobe::AMS_Wardrobe(const FObjectInitializer& aObjectInitializer)
	: Super(aObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMS_Wardrobe::BeginPlay()
{
	Super::BeginPlay();
}

void AMS_Wardrobe::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

