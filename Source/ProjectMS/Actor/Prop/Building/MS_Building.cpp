// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_Building.h"

#include "Component/Actor/MS_InteractionComponent.h"
#include "Manager_Client/MS_SceneManager.h"

AMS_Building::AMS_Building()
{
	InteractionComponent = CreateDefaultSubobject<UMS_InteractionComponent>("InteractionComponent");
	if (InteractionComponent)
	{
		InteractionComponent->SetupAttachment(GetRootComponent());
	}
	
	BuildingFront = CreateDefaultSubobject<UStaticMeshComponent>("BuildingFront");
	if(BuildingFront)
	{
		BuildingFront->AttachToComponent(InteractionComponent, FAttachmentTransformRules::KeepRelativeTransform);
	}

	BuildingMiddle = CreateDefaultSubobject<UStaticMeshComponent>("BuildingMid");
	if(BuildingMiddle)
	{
		BuildingMiddle->AttachToComponent(BuildingFront, FAttachmentTransformRules::KeepRelativeTransform);
		MiddleArray.Emplace(CreateDefaultSubobject<UStaticMeshComponent>("Middle_1"));
		MiddleArray.Emplace(CreateDefaultSubobject<UStaticMeshComponent>("Middle_2"));
		MiddleArray.Emplace(CreateDefaultSubobject<UStaticMeshComponent>("Middle_3"));
		MiddleArray.Emplace(CreateDefaultSubobject<UStaticMeshComponent>("Middle_4"));
		MiddleArray.Emplace(CreateDefaultSubobject<UStaticMeshComponent>("Middle_5"));
		MiddleArray.Emplace(CreateDefaultSubobject<UStaticMeshComponent>("Middle_6"));
		MiddleArray.Emplace(CreateDefaultSubobject<UStaticMeshComponent>("Middle_7"));
		MiddleArray.Emplace(CreateDefaultSubobject<UStaticMeshComponent>("Middle_8"));
		MiddleArray.Emplace(CreateDefaultSubobject<UStaticMeshComponent>("Middle_9"));
	}
	for(const auto& Middle : MiddleArray)
	{
		Middle->SetVisibility(false, true);
	}
	
	BuildingRear = CreateDefaultSubobject<UStaticMeshComponent>("BuildingRear");
	if(BuildingRear)
	{
		BuildingRear->AttachToComponent(BuildingFront, FAttachmentTransformRules::KeepRelativeTransform);
	}
	
	SetFloor(Floor);
}

void AMS_Building::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	UpdateFloorSize();
	SetFloor(Floor);
}

void AMS_Building::PostInitProperties()
{
	Super::PostInitProperties();

	UpdateFloorSize();
	SetFloor(Floor);
}

bool AMS_Building::HasInteractionComponent()
{
	return InteractionComponent != nullptr;
}

void AMS_Building::OnPressDownEvent()
{
	InteractionComponent->OnPressedEvent();
}

void AMS_Building::OnPressUpEvent()
{
	InteractionComponent->OnReleasedEvent();
}

void AMS_Building::LaunchEvent()
{
	Super::LaunchEvent();
}

void AMS_Building::UpdateFloorSize()
{
	if(BuildingFront->GetStaticMesh())
	{
		MiddleStartLocationZ = BuildingFront->GetStaticMesh()->GetBounds().Origin.Z * 2.f;
	}

	if(BuildingMiddle->GetStaticMesh())
	{
		MiddleSizeZ = BuildingMiddle->GetStaticMesh()->GetBounds().Origin.Z * 2.f;
	}
}

void AMS_Building::SetFloor(int32 aFloor)
{
	switch(aFloor)
	{
	case 0:
		{
			BuildingFront->SetVisibility(false, true);
			BuildingMiddle->SetVisibility(false, true);
			BuildingRear->SetVisibility(false, true);
			break;
		}
	case 1:
		{
			BuildingFront->SetVisibility(true, true);
			BuildingMiddle->SetVisibility(false, true);
			BuildingRear->SetVisibility(true, true);
			BuildingRear->SetRelativeLocation(FVector(0.f, 0.f, MiddleStartLocationZ));
			break;
		}
	default:
		{
			BuildingFront->SetVisibility(true, true);
			BuildingRear->SetVisibility(true, true);
			BuildingMiddle->SetVisibility(true, true);

			for(const auto& Middle : MiddleArray)
			{
				Middle->SetVisibility(false, true);
			}

			for(int32 i = 0 ; i < aFloor - 2 ; i++)
			{
				if(MiddleArray.IsValidIndex(i))
				{
					MiddleArray[i]->SetStaticMesh(BuildingMiddle->GetStaticMesh());
					MiddleArray[i]->SetVisibility(true,  true);
					MiddleArray[i]->AttachToComponent(BuildingMiddle, FAttachmentTransformRules::KeepRelativeTransform);
					MiddleArray[i]->SetRelativeLocation(FVector(0.f, 0.f, MiddleSizeZ * (i + 1)));
				}
			}
			
			BuildingMiddle->SetRelativeLocation(FVector(0.f, 0.f, MiddleStartLocationZ));

			if(aFloor <= MiddleArray.Num() + 2)
			{
				BuildingRear->SetRelativeLocation(FVector(0.f, 0.f, MiddleStartLocationZ + MiddleSizeZ * (aFloor - 1)));
			}
			
			break;
		}
	}
}