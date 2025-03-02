// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_MeshTransformComponent.h"


UMS_MeshTransformComponent::UMS_MeshTransformComponent()
	: Order(INDEX_NONE)
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UMS_MeshTransformComponent::BeginPlay()
{
	Super::BeginPlay();
}

