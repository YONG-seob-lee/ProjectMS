// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_SlotActor.h"


AMS_SlotActor::AMS_SlotActor(const FObjectInitializer& aObjectInitializer)
	: Super(aObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
}

void AMS_SlotActor::BeginPlay()
{
	Super::BeginPlay();
}
