// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ActorBase.h"


AMS_ActorBase::AMS_ActorBase(const FObjectInitializer& aObjectInitializer)
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

void AMS_ActorBase::BeginPlay()
{
	Super::BeginPlay();
}

void AMS_ActorBase::Create()
{
	Initialize();
}

void AMS_ActorBase::Initialize()
{
}

void AMS_ActorBase::Finalize()
{
}