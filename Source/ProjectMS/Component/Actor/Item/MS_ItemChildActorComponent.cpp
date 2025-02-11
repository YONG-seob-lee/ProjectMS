// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ItemChildActorComponent.h"

#include "Item/MS_Item.h"


UMS_ItemChildActorComponent::UMS_ItemChildActorComponent()
	: ItemOrder(INDEX_NONE)
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UMS_ItemChildActorComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UMS_ItemChildActorComponent::SetItemVisibility(bool bVisibility)
{
	AMS_Item* Item = Cast<AMS_Item>(GetChildActor());
	
	if (IsValid(Item))
	{
		Item->SetItemVisibility(bVisibility);
	}
}

