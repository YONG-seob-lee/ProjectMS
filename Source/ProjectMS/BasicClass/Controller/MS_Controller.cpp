// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_Controller.h"


// Sets default values
AMS_Controller::AMS_Controller()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMS_Controller::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMS_Controller::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
}

