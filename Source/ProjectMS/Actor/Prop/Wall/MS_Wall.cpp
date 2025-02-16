// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_Wall.h"

#include "MS_ConstructibleLevelScriptActorBase.h"
#include "MathUtility/MS_MathUtility.h"


AMS_Wall::AMS_Wall(const FObjectInitializer& aObjectInitializer)
	: Super(aObjectInitializer)
{
	// Property
	PropType = EMS_PropType::Wall;
}

void AMS_Wall::BeginPlay()
{
	Super::BeginPlay();
}

void AMS_Wall::GetGridPositionOnBothSides(FIntVector2& aOutGridPosition1, FIntVector2& aOutGridPosition2) const
{
	const FRotator& ActorRotation = GetActorRotation();
	EMS_Rotation RotationEnum = UMS_MathUtility::ConvertRotation(ActorRotation.Yaw);
	
	if (RotationEnum == EMS_Rotation::Rot0 || RotationEnum == EMS_Rotation::Rot180)
	{
		aOutGridPosition1 = GetGridPosition() + FIntVector2(0, -1);
		aOutGridPosition2 = GetGridPosition();
	}
	else
	{
		aOutGridPosition1 = GetGridPosition() + FIntVector2(-1, 0);
		aOutGridPosition2 = GetGridPosition();
	}
}

void AMS_Wall::SetVisibilityByGridOpened(TWeakObjectPtr<AMS_ConstructibleLevelScriptActorBase> aOwnerLevelScriptActor)
{
	bool NewVisibility = false;
	
	FIntVector2 GridPosition1, GridPosition2;
	GetGridPositionOnBothSides(GridPosition1, GridPosition2);

	if (aOwnerLevelScriptActor != nullptr)
	{
		bool GridOpend1 = aOwnerLevelScriptActor->IsGridOpened(GridPosition1);
		bool GridOpend2 = aOwnerLevelScriptActor->IsGridOpened(GridPosition2);

		if (GridOpend1 && !GridOpend2)
		{
			NewVisibility = true;

			TWeakObjectPtr<AActor> WallObject = aOwnerLevelScriptActor->GetGridObject(GridPosition1);
			if (AMS_Prop* WallProp = Cast<AMS_Prop>(WallObject))
			{
				if (WallProp->GetPropType() == EMS_PropType::Gate)
				{
					NewVisibility = false;
					WallProp->SetActorHiddenInGame(false);
				}
			}
		}

		else if (!GridOpend1 && GridOpend2)
		{
			NewVisibility = true;

			TWeakObjectPtr<AActor> WallObject = aOwnerLevelScriptActor->GetGridObject(GridPosition2);
			if (AMS_Prop* WallProp = Cast<AMS_Prop>(WallObject))
			{
				if (WallProp->GetPropType() == EMS_PropType::Gate)
				{
					NewVisibility = false;
					WallProp->SetActorHiddenInGame(false);
				}
			}
		}
	}

	for (UMeshComponent* MeshComponent : GetMeshComponents())
	{
		if (IsValid(MeshComponent))
		{
			MeshComponent->SetVisibility(NewVisibility);
		}
	}
}
