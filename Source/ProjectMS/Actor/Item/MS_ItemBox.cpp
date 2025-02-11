// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ItemBox.h"


AMS_ItemBox::AMS_ItemBox(const FObjectInitializer& aObjectInitializer)
	: Super(aObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
}

void AMS_ItemBox::BeginPlay()
{
	Super::BeginPlay();
}
