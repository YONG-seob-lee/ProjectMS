// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_Pawn.h"


// Sets default values
AMS_Pawn::AMS_Pawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMS_Pawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMS_Pawn::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
}

// Called to bind functionality to input
void AMS_Pawn::SetupPlayerInputComponent(UInputComponent* aPlayerInputComponent)
{
	Super::SetupPlayerInputComponent(aPlayerInputComponent);
}

