// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_Item.h"


AMS_Item::AMS_Item(const FObjectInitializer& aObjectInitializer)
: Super(aObjectInitializer.SetDefaultSubobjectClass<UStaticMeshComponent>(TEXT("MeshComponent")))
{
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UMeshComponent>(TEXT("MeshComponent"));
	if (MeshComponent)
	{
		MeshComponent->SetupAttachment(SceneRootComponent);
		MeshComponent->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	}
}

void AMS_Item::BeginPlay()
{
	Super::BeginPlay();
}

void AMS_Item::SetItemVisibility(bool bVisibility)
{
	MeshComponent->SetVisibility(bVisibility);
}

