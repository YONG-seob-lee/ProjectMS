// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_PawnBase.h"


AMS_PawnBase::AMS_PawnBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMS_PawnBase::BeginPlay()
{
	Super::BeginPlay();
}

void AMS_PawnBase::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
}

void AMS_PawnBase::SetupPlayerInputComponent(UInputComponent* aPlayerInputComponent)
{
	Super::SetupPlayerInputComponent(aPlayerInputComponent);
}

