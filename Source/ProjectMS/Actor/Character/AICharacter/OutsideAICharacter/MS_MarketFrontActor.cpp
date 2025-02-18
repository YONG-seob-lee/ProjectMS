// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_MarketFrontActor.h"

#include "Components/SphereComponent.h"


// Sets default values
AMS_MarketFrontActor::AMS_MarketFrontActor(const FObjectInitializer& aObjectInitializer): Super(aObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	if(SphereComponent)
	{
		SphereComponent->SetupAttachment(SceneRootComponent);
		SphereComponent->InitSphereRadius(150.f);
	}
}

// Called when the game starts or when spawned
void AMS_MarketFrontActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMS_MarketFrontActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

