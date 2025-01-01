// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_Building.h"

#include "ActorComponent/MS_InteractionComponent.h"
#include "Manager_Client/MS_SceneManager.h"

AMS_Building::AMS_Building()
{
	InteractionComponent = CreateDefaultSubobject<UMS_InteractionComponent>("InteractionComponent");
	if (InteractionComponent)
	{
		SetRootComponent(InteractionComponent);
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

	CREATE_SCENE_COMMAND(Command);
	Command->SetLevelType(EMS_LevelType::MarketLevel);
	Command->SetPreviousLevelType(EMS_LevelType::LobbyLevel);
	Command->SetFadeOutTransitionType(EMS_TransitionStyle::GradationOut);
	Command->SetFadeInTransitionType(EMS_TransitionStyle::GradationIn);
	Command->SetFadeAnimationType(EMS_FadeAnimationCurveType::Linear);
	Command->SetLoadingWidgetType(EMS_LoadingWidgetType::Default);

	gSceneMng.RequestChangeScene(Command);
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

			TArray<USceneComponent*> ChildComponent = BuildingMiddle->GetAttachChildren();
			for(int32 i = 0; i < ChildComponent.Num(); i++)
			{
				if(ChildComponent[i] == nullptr)
				{
					continue;
				}
				ChildComponent[i]->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
				MS_DeleteObject(ChildComponent[i]);
			}
			
			for(int32 i = 1 ;i < aFloor ; i++)
			{
				if(UStaticMeshComponent* ExtraMidMesh = MS_NewObject<UStaticMeshComponent>(this))
				{
					ExtraMidMesh->SetStaticMesh(BuildingMiddle->GetStaticMesh());
					ExtraMidMesh->AttachToComponent(BuildingMiddle, FAttachmentTransformRules::KeepRelativeTransform);
					ExtraMidMesh->SetRelativeLocation(FVector(0.f, 0.f, MiddleSizeZ * (i - 1)));
				}
			}
			
			BuildingMiddle->SetRelativeLocation(FVector(0.f, 0.f, MiddleStartLocationZ));

			BuildingRear->SetRelativeLocation(FVector(0.f, 0.f, MiddleStartLocationZ + MiddleSizeZ * (aFloor - 1)));
			
			break;
		}
	}
}