// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ItemChildActorComponent.h"


UMS_ItemChildActorComponent::UMS_ItemChildActorComponent()
	: ItemOrder(INDEX_NONE)
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UMS_ItemChildActorComponent::BeginPlay()
{
	Super::BeginPlay();
}

