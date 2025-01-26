// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_Wall.h"

#include "MS_ConstructibleLevelScriptActorBase.h"
#include "Manager_Client/MS_SceneManager.h"
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

void AMS_Wall::GetGridPositionOnBothSides(FIntVector2& OutGridPosition1, FIntVector2& OutGridPosition2) const
{
	const FRotator& ActorRotation = GetActorRotation();
	EMS_Rotation RotationEnum = UMS_MathUtility::ConvertRotation(ActorRotation.Yaw);
	
	if (RotationEnum == EMS_Rotation::Rot0 || RotationEnum == EMS_Rotation::Rot180)
	{
		OutGridPosition1 = GridPosition + FIntVector2(0, -1);
		OutGridPosition2 = GridPosition;
	}
	else
	{
		OutGridPosition1 = GridPosition + FIntVector2(-1, 0);
		OutGridPosition2 = GridPosition;
	}
}

void AMS_Wall::SetVisibilityByGridOpened(class AMS_ConstructibleLevelScriptActorBase* OwnerLevelScriptActor)
{
	// ToDo : Level에서 Wall을 관리하는 방식으로 변경해서 의존성 관리할 것
	// (에디터에서 미리 세팅하는 게 아니라 레벨에서 생성하도록 변경 후)

	bool NewVisibility = false;
	
	FIntVector2 GridPosition1, GridPosition2;
	GetGridPositionOnBothSides(GridPosition1, GridPosition2);

	if (IsValid(OwnerLevelScriptActor))
	{
		bool GridOpend1 = OwnerLevelScriptActor->IsGridOpened(GridPosition1);
		bool GridOpend2 = OwnerLevelScriptActor->IsGridOpened(GridPosition2);

		if ((GridOpend1 && !GridOpend2) || (!GridOpend1 && GridOpend2))
		{
			NewVisibility = true;
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
