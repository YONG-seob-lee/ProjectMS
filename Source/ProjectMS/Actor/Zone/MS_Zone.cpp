// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_Zone.h"

#include "MS_Define.h"
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
	
	ZoneLocation = ZoneBoxComponent->GetComponentLocation() - ZoneBoxComponent->GetScaledBoxExtent();
	ZoneGridNum = FIntVector(ZoneBoxComponent->GetScaledBoxExtent() * 2.f / MS_GridSize);
	ZoneWorldGridPosition = FIntVector(ZoneLocation / MS_GridSize);

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

void AMS_Zone::RegisterObjectToGrid(const FIntVector2& aZoneGridPosition, TWeakObjectPtr<AActor> aObject)
{
	if (Grids.Contains(aZoneGridPosition))
	{
		FMS_GridData& GridData = *Grids.Find(aZoneGridPosition);

		if (GridData.Object == nullptr)
		{
			GridData.Object = aObject;
		}
		else
		{
			MS_LOG_Verbosity(Error, TEXT("Object data alreay exists [Zone %d - X : %d, Y : %d]"),
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

