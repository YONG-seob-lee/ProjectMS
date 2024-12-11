// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_Prop_Wall.h"


AMS_Prop_Wall::AMS_Prop_Wall()
{
	PrimaryActorTick.bCanEverTick = true;

	// Property
	PropType = EMS_PropType::Wall;
}

void AMS_Prop_Wall::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMS_Prop_Wall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}