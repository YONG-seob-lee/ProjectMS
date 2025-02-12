// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_Furniture.h"

#include "Component/Actor/Item/MS_SlotChildActorComponent.h"
#include "Manager_Client/MS_ModeManager.h"


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
}

void AMS_Furniture::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	TArray<UMS_SlotChildActorComponent*> SlotComponents;
	GetComponents<UMS_SlotChildActorComponent>(SlotComponents);

	for (UMS_SlotChildActorComponent* SlotComponent : SlotComponents)
	{
		if (SlotComponent->GetSlotId() == INDEX_NONE)
		{
			MS_LOG_VERBOSITY(Error, TEXT("[%s] Please set slot components order"), *MS_FUNC_STRING);
			MS_ENSURE(false);
		}
		
		SlotIdToSlotComponents.Emplace(SlotComponent->GetSlotId(), SlotComponent);
	}
}

void AMS_Furniture::OnSelectProp(EMS_ModeState aModeState)
{
	Super::OnSelectProp(aModeState);
	
	if (aModeState == EMS_ModeState::Normal)
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

	if (aModeState == EMS_ModeState::Normal)
	{
		// For PostProcess
		GetComponents(UMeshComponent::StaticClass(), MeshComponents);

		for (UMeshComponent* MeshComponent : MeshComponents)
		{
			MeshComponent->SetRenderCustomDepth(false);
		}
	}
}

void AMS_Furniture::OnChangeRequestSlotDatas(const TArray<FMS_SlotData>& aSlotDatas)
{
	for (auto& It : SlotIdToSlotComponents)
	{
		if (aSlotDatas.IsValidIndex(It.Key))
		{
			It.Value->OnChangeRequestSlotData(aSlotDatas[It.Key]);
		}
		else
		{
			It.Value->OnChangeRequestSlotData(FMS_SlotData());
		}
	}
}

void AMS_Furniture::OnChangeCurrentSlotDatas(const TArray<FMS_SlotData>& aSlotDatas)
{
	for (auto& It : SlotIdToSlotComponents)
	{
		if (aSlotDatas.IsValidIndex(It.Key))
		{
			It.Value->OnChangeCurrentSlotData(aSlotDatas[It.Key]);
		}
		else
		{
			It.Value->OnChangeCurrentSlotData(FMS_SlotData());
		}
	}
}

