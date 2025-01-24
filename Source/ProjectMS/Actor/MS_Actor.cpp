// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_Actor.h"


AMS_Actor::AMS_Actor(const FObjectInitializer& aObjectInitializer)
	: Super(aObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	// Component
	SceneRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRootComponent"));
	if (SceneRootComponent)
	{
		SetRootComponent(SceneRootComponent);
	}
}

void AMS_Actor::BeginPlay()
{
	Super::BeginPlay();
}

void AMS_Actor::Create(const FString& aLabelName)
{
	Initialize();
}

void AMS_Actor::Initialize()
{
}

void AMS_Actor::Finalize()
{
}

