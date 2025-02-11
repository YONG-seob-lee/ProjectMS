// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_SlotActor.h"

#include "MS_Define.h"
#include "Component/Actor/Item/MS_ItemChildActorComponent.h"


AMS_SlotActor::AMS_SlotActor(const FObjectInitializer& aObjectInitializer)
	: Super(aObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	ItemAttachedComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ItemAttachedComponent"));
	if (ItemAttachedComponent)
	{
		ItemAttachedComponent->SetupAttachment(SceneRootComponent);
	}
}

void AMS_SlotActor::BeginPlay()
{
	Super::BeginPlay();
}

void AMS_SlotActor::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	TArray<UMS_ItemChildActorComponent*> ItemComponents;
	GetComponents<UMS_ItemChildActorComponent>(ItemComponents);

	for (UMS_ItemChildActorComponent* ItemComponent : ItemComponents)
	{
		if (ItemComponent->GetItemOrder() == INDEX_NONE)
		{
			MS_LOG_VERBOSITY(Error, TEXT("[%s] Please set item components order"), *MS_FUNC_STRING);
			MS_ENSURE(false);
		}
		
		ItemOrderToItemComponents.Emplace(ItemComponent->GetItemOrder(), ItemComponent);
	}
}

void AMS_SlotActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}
