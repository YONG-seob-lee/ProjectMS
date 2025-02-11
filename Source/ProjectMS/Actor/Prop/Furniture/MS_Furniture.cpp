// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_Furniture.h"

#include "Component/Actor/Item/MS_SlotChildActorComponent.h"


AMS_Furniture::AMS_Furniture(const FObjectInitializer& aObjectInitializer)
	: Super(aObjectInitializer)
{
	// Property
	PropType = EMS_PropType::Furniture;

	SlotAttachedComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SlotAttachedComponent"));
	if (SlotAttachedComponent)
	{
		SlotAttachedComponent->SetupAttachment(SceneRootComponent);
	}
}

void AMS_Furniture::BeginPlay()
{
	Super::BeginPlay();
}

void AMS_Furniture::PreInitializeComponents()
{
	Super::PreInitializeComponents();
	
	TArray<UMS_SlotChildActorComponent*> SlotComponents;
	GetComponents<UMS_SlotChildActorComponent>(SlotComponents);

	for (UMS_SlotChildActorComponent* SlotComponent : SlotComponents)
	{
		if (SlotComponent->GetSlotOrder() == INDEX_NONE)
		{
			MS_LOG_VERBOSITY(Error, TEXT("[%s] Please set slot components order"), *MS_FUNC_STRING);
			MS_ENSURE(false);
		}
		
		SlotOrderToSlotComponents.Emplace(SlotComponent->GetSlotOrder(), SlotComponent);
	}
}

void AMS_Furniture::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

