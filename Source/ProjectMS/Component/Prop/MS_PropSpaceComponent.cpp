// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_PropSpaceComponent.h"

#include "MS_Define.h"


UMS_PropSpaceComponent::UMS_PropSpaceComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
	BoxExtent = FVector(25.f, 25.f, 0.f);
	
	BodyInstance.SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
}


void UMS_PropSpaceComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UMS_PropSpaceComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                           FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UMS_PropSpaceComponent::GetGridPositions(FIntVector& aOutWorldStartGridPosition,
	FIntVector& aOutGridNum) const
{
	float PropYaw = GetOwner()->GetActorRotation().Yaw;
	MS_LOG_Verbosity(Warning, TEXT("PropYaw : %f [PropName : %s]"), PropYaw, *GetOwner()->GetName());
	
	// Start Position
	FVector SpaceStartOffset;
	if (FMath::IsNearlyEqual(PropYaw, 0.f) || FMath::IsNearlyEqual(PropYaw, 180.f) || FMath::IsNearlyEqual(PropYaw, -180.f))
	{
		SpaceStartOffset = FVector(-GetUnscaledBoxExtent().X, -GetUnscaledBoxExtent().Y, 0.f);
	}
	else
	{
		SpaceStartOffset = FVector(-GetUnscaledBoxExtent().Y, -GetUnscaledBoxExtent().X, 0.f);
	}
			
	FVector WorldStartLocation = GetComponentLocation() + SpaceStartOffset;
	aOutWorldStartGridPosition = FIntVector(FMath::RoundToInt32(WorldStartLocation.X / MS_GridSize.X), FMath::RoundToInt32(WorldStartLocation.Y / MS_GridSize.Y), 0);

	// Num
	FVector SpaceSize;
	if (FMath::IsNearlyEqual(PropYaw, 0.f) || FMath::IsNearlyEqual(PropYaw, 180.f) || FMath::IsNearlyEqual(PropYaw, -180.f))
	{
		SpaceSize = FVector(GetUnscaledBoxExtent().X * 2.f, GetUnscaledBoxExtent().Y * 2.f, 0.f);
	}
	else
	{
		SpaceSize = FVector(GetUnscaledBoxExtent().Y * 2.f, GetUnscaledBoxExtent().X * 2.f, 0.f);
	}

	aOutGridNum = FIntVector(FMath::RoundToInt32(SpaceSize.X / MS_GridSize.X), FMath::RoundToInt32(SpaceSize.Y / MS_GridSize.Y), 0);
}
