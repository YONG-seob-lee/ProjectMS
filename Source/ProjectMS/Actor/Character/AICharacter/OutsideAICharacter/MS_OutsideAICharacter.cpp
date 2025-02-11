// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_OutsideAICharacter.h"

#include "AI/AIController/OutsideAIController/MS_OutsideAIController.h"


// Sets default values
AMS_OutsideAICharacter::AMS_OutsideAICharacter()
{
	AIControllerClass = AMS_OutsideAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AMS_OutsideAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

// Called when the game starts or when spawned
void AMS_OutsideAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMS_OutsideAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}