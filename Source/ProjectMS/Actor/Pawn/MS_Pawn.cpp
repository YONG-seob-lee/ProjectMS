// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_Pawn.h"


AMS_Pawn::AMS_Pawn()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMS_Pawn::BeginPlay()
{
	Super::BeginPlay();
}

void AMS_Pawn::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
}

void AMS_Pawn::SetupPlayerInputComponent(UInputComponent* aPlayerInputComponent)
{
	Super::SetupPlayerInputComponent(aPlayerInputComponent);
}

