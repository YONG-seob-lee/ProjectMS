// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_Item.h"


AMS_Item::AMS_Item(const FObjectInitializer& aObjectInitializer)
	: Super(aObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
}

void AMS_Item::BeginPlay()
{
	Super::BeginPlay();
}

