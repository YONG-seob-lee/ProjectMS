// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_PlayerController.h"


// Sets default values
AMS_PlayerController::AMS_PlayerController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerCameraManagerClass = AMS_PlayerController::StaticClass();
}

// Called when the game starts or when spawned
void AMS_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMS_PlayerController::PostLoad()
{
	Super::PostLoad();

	Management = NewObject<UMS_Management>(this);
}

TWeakObjectPtr<UMS_TableManager> AMS_PlayerController::GetTableManager() const
{
	if(!Management)
	{
		return nullptr;
	}

	return Management->GetTableManager();
}

// Called every frame
void AMS_PlayerController::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
}

