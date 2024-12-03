// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_TownLevelScriptActor.h"


// Sets default values
AMS_TownLevelScriptActor::AMS_TownLevelScriptActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMS_TownLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMS_TownLevelScriptActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

