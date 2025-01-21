// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_Wall.h"


AMS_Wall::AMS_Wall(const FObjectInitializer& aObjectInitializer)
	: Super(aObjectInitializer)
{
	// Property
	PropType = EMS_PropType::Wall;
}

void AMS_Wall::BeginPlay()
{
	Super::BeginPlay();
}
