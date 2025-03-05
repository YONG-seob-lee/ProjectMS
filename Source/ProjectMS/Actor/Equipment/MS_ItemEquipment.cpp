// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ItemEquipment.h"


AMS_ItemEquipment::AMS_ItemEquipment(const FObjectInitializer& aObjectInitializer) : Super(aObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
}

void AMS_ItemEquipment::SetMesh(const TObjectPtr<UStaticMesh>* StaticMesh) const
{
	if(MeshComponent && StaticMesh)
	{
		MeshComponent->SetStaticMesh(*StaticMesh);
	}
}

void AMS_ItemEquipment::BeginPlay()
{
	Super::BeginPlay();
}

