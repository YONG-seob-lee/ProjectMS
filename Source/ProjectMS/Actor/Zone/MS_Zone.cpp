// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_Zone.h"

#include "MS_Define.h"
#include "Component/Prop/MS_PropSpaceComponent.h"
#include "Components/BoxComponent.h"
#include "Environment/MS_LevelPropDatas.h"


AMS_Zone::AMS_Zone()
{
	PrimaryActorTick.bCanEverTick = true;

	// Component
	ZoneBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("ZoneBoxComponent"));
}

void AMS_Zone::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	InitializeZoneData();
}

void AMS_Zone::BeginPlay()
{
	Super::BeginPlay();
}

void AMS_Zone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AMS_Zone::InitializeZoneData()
{
	MS_CHECK(ZoneBoxComponent);
	
	ZoneLocation = ZoneBoxComponent->GetComponentLocation() - ZoneBoxComponent->GetUnscaledBoxExtent();
	
	ZoneSize = ZoneBoxComponent->GetUnscaledBoxExtent() * 2.f;
	
	ZoneGridNum = FIntVector(FMath::RoundToInt32(ZoneSize.X / MS_GridSize.X),
		FMath::RoundToInt32(ZoneSize.Y / MS_GridSize.Y), FMath::RoundToInt32(ZoneSize.Z / MS_GridSize.Z));
	
	ZoneWorldGridPosition = FIntVector(FMath::RoundToInt32(ZoneLocation.X / MS_GridSize.X),
		FMath::RoundToInt32(ZoneLocation.Y / MS_GridSize.Y), FMath::RoundToInt32(ZoneLocation.Z / MS_GridSize.Z));

	CreateGrids();
}

void AMS_Zone::CreateGrids()
{
	Grids.Empty();

	for (int i = 0; i < ZoneGridNum.Y; ++i)
	{
		for (int j = 0; j < ZoneGridNum.X; ++j)
		{
			FIntVector2 ZoneGridPosition = FIntVector2(j, i);
			FIntVector2 WorldGridPosition = FIntVector2(ZoneWorldGridPosition.X, ZoneWorldGridPosition.Y) + ZoneGridPosition;
			
			Grids.Emplace(ZoneGridPosition, FMS_GridData(this, ZoneGridPosition, WorldGridPosition));
		}
	}
}

bool AMS_Zone::IsWorldLocationContained(const FVector& aInWorldLocation, FVector& aOutZoneLocation) const
{
	if (aInWorldLocation.X >= ZoneLocation.X
	&& aInWorldLocation.Y >= ZoneLocation.Y
	&& aInWorldLocation.X < ZoneLocation.X + ZoneSize.X
	&& aInWorldLocation.Y < ZoneLocation.Y + ZoneSize.Y)
	{
		aOutZoneLocation = aInWorldLocation - ZoneLocation;

		return true;
	}

	return false;
}

bool AMS_Zone::IsWorldGridContained(const FIntVector2& aInWorldGridPosition, FIntVector2& aOutZoneGridPosition) const
{
	if (aInWorldGridPosition.X >= ZoneWorldGridPosition.X
		&& aInWorldGridPosition.Y >= ZoneWorldGridPosition.Y
		&& aInWorldGridPosition.X < ZoneWorldGridPosition.X + ZoneGridNum.X
		&& aInWorldGridPosition.Y < ZoneWorldGridPosition.Y + ZoneGridNum.Y)
	{
		aOutZoneGridPosition = FIntVector2(aInWorldGridPosition.X - ZoneWorldGridPosition.X,
			aInWorldGridPosition.Y - ZoneWorldGridPosition.Y);

		return true;
	}

	return false;
}

void AMS_Zone::RegisterFloorToGrid(const FIntVector2& aZoneGridPosition, TWeakObjectPtr<AActor> aFloor)
{
	if (Grids.Contains(aZoneGridPosition))
	{
		FMS_GridData& GridData = *Grids.Find(aZoneGridPosition);

		if (GridData.Floor == nullptr)
		{
			GridData.Floor = aFloor;
		}
		else
		{
			MS_LOG_Verbosity(Error, TEXT("Floor data alreay exists [Zone %d - X : %d, Y : %d]"),
				ZoneIndex, aZoneGridPosition.X, aZoneGridPosition.Y);

			MS_Ensure(false);
		}
	}
	else
	{
		MS_LOG_Verbosity(Error, TEXT("Floor's ZoneGridPosition is not vaild [Zone %d - X : %d, Y : %d]"),
			ZoneIndex, aZoneGridPosition.X, aZoneGridPosition.Y);

		MS_Ensure(false);
	}
}

void AMS_Zone::RegisterObjectToGrid(const FIntVector2& aZoneGridPosition, TWeakObjectPtr<UMS_PropSpaceComponent> aPropSpaceComponent)
{
	if (Grids.Contains(aZoneGridPosition))
	{
		FMS_GridData& GridData = *Grids.Find(aZoneGridPosition);

		if (GridData.Object == nullptr)
		{
			GridData.Object = aPropSpaceComponent->GetOwner();
		}
		else
		{
			MS_LOG_Verbosity(Error, TEXT("Object data alreay exists [Zone %d - X : %d, Y : %d]"),
				ZoneIndex, aZoneGridPosition.X, aZoneGridPosition.Y);

			MS_Ensure(false);
		}

		if (GridData.PropSpaceComponent == nullptr)
		{
			GridData.PropSpaceComponent = aPropSpaceComponent;
		}
		else
		{
			MS_LOG_Verbosity(Error, TEXT("PropSpaceComponent data alreay exists [Zone %d - X : %d, Y : %d]"),
				ZoneIndex, aZoneGridPosition.X, aZoneGridPosition.Y);

			MS_Ensure(false);
		}
	}
	else
	{
		MS_LOG_Verbosity(Error, TEXT("Object's ZoneGridPosition is not vaild [Zone %d - X : %d, Y : %d]"),
			ZoneIndex, aZoneGridPosition.X, aZoneGridPosition.Y);

		MS_Ensure(false);
	}
}

void AMS_Zone::UnregisterObjectToGrid(const FIntVector2& aZoneGridPosition)
{
	if (Grids.Contains(aZoneGridPosition))
	{
		FMS_GridData& GridData = *Grids.Find(aZoneGridPosition);

		GridData.Object = nullptr;
		GridData.PropSpaceComponent = nullptr;
	}
	else
	{
		MS_LOG_Verbosity(Error, TEXT("Object's ZoneGridPosition is not vaild [Zone %d - X : %d, Y : %d]"),
			ZoneIndex, aZoneGridPosition.X, aZoneGridPosition.Y);

		MS_Ensure(false);
	}
}

const FMS_GridData& AMS_Zone::GetGrid(const FIntVector2& aZoneGridPosition) const
{
	static FMS_GridData Dummy;
	if (!Grids.Contains(aZoneGridPosition))
	{
		MS_Ensure(false);
		return Dummy;
	}
	
	return *Grids.Find(aZoneGridPosition);
}

void AMS_Zone::ShowDebugZoneData()
{
#if WITH_EDITOR
	for (int i = 0; i < ZoneGridNum.Y; ++i)
	{
		for (int j = 0; j < ZoneGridNum.X; ++j)
		{
			if (FMS_GridData* pGrid = Grids.Find(FIntVector2(j, i)))
			{
				if (pGrid->Object != nullptr && pGrid->PropSpaceComponent != nullptr)
				{
					MS_LOG_Verbosity(VeryVerbose, TEXT("ZoneGrid %d-%d,%d : %s, SpaceType : %d, PurposeType : %d"),
						ZoneIndex, j, i, *pGrid->Object->GetName(),
						static_cast<uint8>(pGrid->PropSpaceComponent->GetPropSpaceType()),
						static_cast<uint8>(pGrid->PropSpaceComponent->GetPropPurposeSpaceType()));
				}
			}
		}
	}
#endif
}

