// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_Equipment.h"


AMS_Equipment::AMS_Equipment(const FObjectInitializer& aObjectInitializer) : Super(aObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	if(MeshComponent)
	{
		MeshComponent->SetupAttachment(SceneRootComponent);
	}
}

void AMS_Equipment::BeginPlay()
{
	Super::BeginPlay();
}

void AMS_Equipment::Equip()
{
	bIsEquipped = true;
	
	SetActorHiddenInGame(true);
	SetActorEnableCollision(true);
}

void AMS_Equipment::Unequip()
{
	bIsEquipped = false;
	
	SetActorHiddenInGame(false);
	SetActorEnableCollision(false);
}
