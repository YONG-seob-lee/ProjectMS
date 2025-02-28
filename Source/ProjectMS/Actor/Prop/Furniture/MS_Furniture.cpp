// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_Furniture.h"


AMS_Furniture::AMS_Furniture(const FObjectInitializer& aObjectInitializer)
	: Super(aObjectInitializer), FurnitureType(EMS_FurnitureType::None)
{
	// Property
	PropType = EMS_PropType::Furniture;
}

void AMS_Furniture::BeginPlay()
{
	Super::BeginPlay();
}

void AMS_Furniture::PreInitializeComponents()
{
	Super::PreInitializeComponents();
}

void AMS_Furniture::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AMS_Furniture::OnSelectProp(EMS_ModeState aModeState)
{
	Super::OnSelectProp(aModeState);
	
	if (aModeState == EMS_ModeState::Normal || aModeState == EMS_ModeState::RunMarket)
	{
		// For PostProcess
		GetComponents(UMeshComponent::StaticClass(), MeshComponents);

		for (UMeshComponent* MeshComponent : MeshComponents)
		{
			MeshComponent->SetRenderCustomDepth(true);
		}
	}
}

void AMS_Furniture::OnUnselectProp(EMS_ModeState aModeState)
{
	Super::OnUnselectProp(aModeState);

	if (aModeState == EMS_ModeState::Normal || aModeState == EMS_ModeState::RunMarket)
	{
		// For PostProcess
		GetComponents(UMeshComponent::StaticClass(), MeshComponents);

		for (UMeshComponent* MeshComponent : MeshComponents)
		{
			MeshComponent->SetRenderCustomDepth(false);
		}
	}
}

