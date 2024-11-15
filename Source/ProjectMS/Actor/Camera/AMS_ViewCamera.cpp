// Fill out your copyright notice in the Description page of Project Settings.


#include "AMS_ViewCamera.h"


// Sets default values
AAMS_ViewCamera::AAMS_ViewCamera()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAMS_ViewCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAMS_ViewCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

