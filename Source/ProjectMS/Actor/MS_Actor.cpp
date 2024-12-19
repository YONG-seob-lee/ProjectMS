// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_Actor.h"

#include "Components/SphereComponent.h"


// Sets default values
AMS_Actor::AMS_Actor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	if(StaticMeshComponent)
	{
		
	}
	
	TestSphere = CreateDefaultSubobject<USphereComponent>("VisibleTestComponent");
	if(TestSphere)
	{
		TestSphere->SetSphereRadius(300.f);
		TestSphere->SetGenerateOverlapEvents(false);
		TestSphere->SetEnableGravity(false);
		TestSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		TestSphere->SetCollisionProfileName(TEXT("NoCollision"));
		TestSphere->SetupAttachment(RootComponent);
		StaticMeshComponent->SetupAttachment(TestSphere);
	}
}

// Called when the game starts or when spawned
void AMS_Actor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMS_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMS_Actor::Create(const FString& aLabelName)
{
	SetActorLabel(aLabelName);

	Initialize();
}

void AMS_Actor::Initialize()
{
}

void AMS_Actor::Finalize()
{
	if(TestSphere)
	{
		TestSphere->Deactivate();
	}
}

