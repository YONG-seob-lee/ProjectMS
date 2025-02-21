// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_Equipment.h"


AMS_Equipment::AMS_Equipment(const FObjectInitializer& aObjectInitializer) : Super(aObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	if(MeshComponent)
	{
		MeshComponent->SetupAttachment(GetRootComponent());
	}
}

void AMS_Equipment::BeginPlay()
{
	Super::BeginPlay();
}