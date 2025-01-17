// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_PropSpaceComponent.h"

#include "MS_Define.h"
#include "Prop/MS_Prop.h"


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

AMS_Prop* UMS_PropSpaceComponent::GetOwnerProp() const
{
	return Cast<AMS_Prop>(GetOwner());
}

void UMS_PropSpaceComponent::GetWorldGridPositions(FIntVector2& aOutWorldStartGridPosition,
	FIntVector2& aOutGridNum) const
{
	// Prop Yaw
	float PropYaw = GetOwner()->GetActorRotation().Yaw;
	MS_LOG_Verbosity(VeryVerbose, TEXT("[%s] PropYaw : %f [PropName : %s]"), *MS_FUNC_STRING, PropYaw, *GetOwner()->GetName());

	bool bTransposeAxis = !(FMath::IsNearlyEqual(PropYaw, 0.f) || FMath::IsNearlyEqual(PropYaw, 180.f) || FMath::IsNearlyEqual(PropYaw, -180.f));

	
	// Start Grid Position
	FVector SpaceStartOffset;
	if (bTransposeAxis)
	{
		SpaceStartOffset = FVector(-GetUnscaledBoxExtent().Y, -GetUnscaledBoxExtent().X, 0.f);
	}
	else
	{
		SpaceStartOffset = FVector(-GetUnscaledBoxExtent().X, -GetUnscaledBoxExtent().Y, 0.f);
	}
			
	FVector WorldStartLocation = GetComponentLocation() + SpaceStartOffset;
	aOutWorldStartGridPosition = FIntVector2(FMath::RoundToInt32(WorldStartLocation.X) / MS_GridSizeInt.X, FMath::RoundToInt32(WorldStartLocation.Y) / MS_GridSizeInt.Y);
	
	
	// Grid Num
	FVector SpaceSize;
	if (bTransposeAxis)
	{
		SpaceSize = FVector(GetUnscaledBoxExtent().Y * 2.f, GetUnscaledBoxExtent().X * 2.f, 0.f);
	}
	else
	{
		SpaceSize = FVector(GetUnscaledBoxExtent().X * 2.f, GetUnscaledBoxExtent().Y * 2.f, 0.f);
	}

	aOutGridNum = FIntVector2(FMath::RoundToInt32(SpaceSize.X) / MS_GridSizeInt.X, FMath::RoundToInt32(SpaceSize.Y) / MS_GridSizeInt.Y);
}
