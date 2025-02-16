// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_Furniture.h"

#include "Component/Actor/Item/MS_ItemSlotChildActorComponent.h"
#include "Manager_Client/MS_ModeManager.h"


AMS_Furniture::AMS_Furniture(const FObjectInitializer& aObjectInitializer)
	: Super(aObjectInitializer)
{
	// Property
	PropType = EMS_PropType::Furniture;

	ItemSlotAttachedComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SlotAttachedComponent"));
	if (ItemSlotAttachedComponent)
	{
		ItemSlotAttachedComponent->SetupAttachment(SceneRootComponent);
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

	TArray<UMS_ItemSlotChildActorComponent*> SlotComponents;
	GetComponents<UMS_ItemSlotChildActorComponent>(SlotComponents);

	for (UMS_ItemSlotChildActorComponent* SlotComponent : SlotComponents)
	{
		if (SlotComponent->GetSlotId() == INDEX_NONE)
		{
			MS_LOG_VERBOSITY(Error, TEXT("[%s] Please set slot components order"), *MS_FUNC_STRING);
			MS_ENSURE(false);
		}
		
		ItemSlotIdToSlotComponents.Emplace(SlotComponent->GetSlotId(), SlotComponent);
	}
}

void AMS_Furniture::OnSelectProp(EMS_ModeState aModeState)
{
	Super::OnSelectProp(aModeState);
	
	if (aModeState == EMS_ModeState::Normal || aModeState == EMS_ModeState::RunMarketNormal)
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

	if (aModeState == EMS_ModeState::Normal || aModeState == EMS_ModeState::RunMarketNormal)
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
	for (auto& It : ItemSlotIdToSlotComponents)
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
	for (auto& It : ItemSlotIdToSlotComponents)
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

