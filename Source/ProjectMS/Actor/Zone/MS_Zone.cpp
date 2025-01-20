// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_Zone.h"

#include "MS_Define.h"
#include "Component/Prop/MS_PropSpaceComponent.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Environment/MS_LevelPropDatas.h"
#include "Prop/MS_Prop.h"
#include "Widget/Market/MS_ZoneOpenWidget.h"


AMS_Zone::AMS_Zone()
{
	PrimaryActorTick.bCanEverTick = true;

	// Component
	ZoneBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("ZoneBoxComponent"));
	
	FloorAttachedComponent = CreateDefaultSubobject<USceneComponent>(TEXT("FloorAttachedComponent"));
	if (FloorAttachedComponent)
	{
		FloorAttachedComponent->SetupAttachment(ZoneBoxComponent);
	}

	Rot0WallAttachedComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Rot0WallAttachedComponent"));
	if (Rot0WallAttachedComponent)
	{
		Rot0WallAttachedComponent->SetupAttachment(ZoneBoxComponent);
	}

	Rot90WallAttachedComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Rot90WallAttachedComponent"));
	if (Rot90WallAttachedComponent)
	{
		Rot90WallAttachedComponent->SetupAttachment(ZoneBoxComponent);
	}

	Rot180WallAttachedComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Rot180WallAttachedComponent"));
	if (Rot180WallAttachedComponent)
	{
		Rot180WallAttachedComponent->SetupAttachment(ZoneBoxComponent);
	}

	Rot270WallAttachedComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Rot270WallAttachedComponent"));
	if (Rot270WallAttachedComponent)
	{
		Rot270WallAttachedComponent->SetupAttachment(ZoneBoxComponent);
	}

	ZoneOpendWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("ZoneOpendWidgetComponent"));
	if (ZoneOpendWidgetComponent)
	{
		ZoneOpendWidgetComponent->SetupAttachment(ZoneBoxComponent);
	}
}

void AMS_Zone::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	InitializeZoneData();
}

void AMS_Zone::BeginPlay()
{
	Super::BeginPlay();

	if (ZoneOpendWidgetComponent)
	{
		if (UMS_ZoneOpenWidget* ZoneOpenWidget = Cast<UMS_ZoneOpenWidget>(ZoneOpendWidgetComponent->GetWidget()))
		{
			ZoneOpenWidget->OnClickZoneOpenButtonDelegate.BindUObject(this, &AMS_Zone::OnClickZoneOpenWidget);
		}
	}
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
	
	ZoneGridNum = FIntVector2(FMath::RoundToInt32(ZoneSize.X / MS_GridSize.X),
		FMath::RoundToInt32(ZoneSize.Y / MS_GridSize.Y));
	
	ZoneWorldGridPosition = FIntVector2(FMath::RoundToInt32(ZoneLocation.X / MS_GridSize.X),
		FMath::RoundToInt32(ZoneLocation.Y / MS_GridSize.Y));

	CreateGrids();

	RegisterDefalutAttachedProps();
}

void AMS_Zone::CreateGrids()
{
	Grids.Empty();

	for (int i = 0; i < ZoneGridNum.Y; ++i)
	{
		for (int j = 0; j < ZoneGridNum.X; ++j)
		{
			FIntVector2 GridPosition = FIntVector2(ZoneWorldGridPosition.X, ZoneWorldGridPosition.Y) + FIntVector2(j, i);
			
			Grids.Emplace(GridPosition, FMS_GridData(this, GridPosition));
		}
	}
}

void AMS_Zone::RegisterDefalutAttachedProps()
{
	TArray<AActor*> AttachedActors;
	GetAttachedActors(AttachedActors);

	for (AActor* AttachedActor : AttachedActors)
	{
		if (AMS_Prop* Prop = Cast<AMS_Prop>(AttachedActor))
		{
			// Prop Center Grid
			FVector WorldCenterLocation = Prop->GetActorLocation();
		
			FIntVector2 PropCenterGridPosition = FIntVector2(FMath::RoundToInt32(WorldCenterLocation.X) / MS_GridSizeInt.X
				, FMath::RoundToInt32(WorldCenterLocation.Y) / MS_GridSizeInt.Y);
			
			Prop->SetZoneData(this, PropCenterGridPosition);
		
			// Prop Space
			const TArray<UMS_PropSpaceComponent*>& PropSpaceComponents = Prop->GetPropSpaceComponents();
		
			for (UMS_PropSpaceComponent* PropSpaceComponent : PropSpaceComponents)
			{
				FIntVector2 StartGridPosition = FIntVector2::ZeroValue;
				FIntVector2 GridNum = FIntVector2::ZeroValue;
			
				PropSpaceComponent->GetGridPositions(StartGridPosition, GridNum);
			
				// Set With Grid
				for (int i = 0; i < GridNum.Y; ++i)
				{
					for (int j = 0; j < GridNum.X; ++j)
					{
						FIntVector2 GridPosition = FIntVector2(StartGridPosition.X + j, StartGridPosition.Y + i);

						EMS_PropType PropType = Prop->GetPropType();
						
						switch (PropType)
						{
						case EMS_PropType::Floor:
							{
								RegisterFloorToGrid(GridPosition, Prop);
					
								break;
							}
						default :
							{
								break;
							}
						}
					}
				}
			}
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

bool AMS_Zone::IsGridContained(const FIntVector2& aInGridPosition) const
{
	return Grids.Contains(aInGridPosition);
}

void AMS_Zone::RegisterFloorToGrid(const FIntVector2& aGridPosition, TWeakObjectPtr<AActor> aFloor)
{
	if (Grids.Contains(aGridPosition))
	{
		FMS_GridData& GridData = *Grids.Find(aGridPosition);

		if (GridData.Floor == nullptr)
		{
			GridData.Floor = aFloor;
		}
		else
		{
			MS_LOG_Verbosity(Error, TEXT("Floor data alreay exists [Zone %d - X : %d, Y : %d]"),
				ZoneIndex, aGridPosition.X, aGridPosition.Y);

			MS_Ensure(false);
		}
	}
	else
	{
		MS_LOG_Verbosity(Error, TEXT("Floor's GridPosition is not vaild [Zone %d - X : %d, Y : %d]"),
			ZoneIndex, aGridPosition.X, aGridPosition.Y);

		MS_Ensure(false);
	}
}

void AMS_Zone::RegisterObjectToGrid(const FIntVector2& aGridPosition, TWeakObjectPtr<UMS_PropSpaceComponent> aPropSpaceComponent)
{
	if (Grids.Contains(aGridPosition))
	{
		FMS_GridData& GridData = *Grids.Find(aGridPosition);

		if (GridData.Object == nullptr)
		{
			GridData.Object = aPropSpaceComponent->GetOwner();
		}
		else
		{
			MS_LOG_Verbosity(Error, TEXT("Object data alreay exists [Zone %d - X : %d, Y : %d]"),
				ZoneIndex, aGridPosition.X, aGridPosition.Y);

			MS_Ensure(false);
		}

		if (GridData.PropSpaceComponent == nullptr)
		{
			GridData.PropSpaceComponent = aPropSpaceComponent;
		}
		else
		{
			MS_LOG_Verbosity(Error, TEXT("PropSpaceComponent data alreay exists [Zone %d - X : %d, Y : %d]"),
				ZoneIndex, aGridPosition.X, aGridPosition.Y);

			MS_Ensure(false);
		}
	}
	else
	{
		MS_LOG_Verbosity(Error, TEXT("Object's GridPosition is not vaild [Zone %d - X : %d, Y : %d]"),
			ZoneIndex, aGridPosition.X, aGridPosition.Y);

		MS_Ensure(false);
	}
}

void AMS_Zone::UnregisterObjectToGrid(const FIntVector2& aGridPosition)
{
	if (Grids.Contains(aGridPosition))
	{
		FMS_GridData& GridData = *Grids.Find(aGridPosition);

		GridData.Object = nullptr;
		GridData.PropSpaceComponent = nullptr;
	}
	else
	{
		MS_LOG_Verbosity(Error, TEXT("Object's GridPosition is not vaild [Zone %d - X : %d, Y : %d]"),
			ZoneIndex, aGridPosition.X, aGridPosition.Y);

		MS_Ensure(false);
	}
}

void AMS_Zone::OnClickZoneOpenWidget(UMS_ZoneOpenWidget* aZoneOpenWidget)
{
	SetZoneOpened(true);
}

void AMS_Zone::SetZoneOpened(bool aOpened)
{
	bOpened = aOpened;

	FloorAttachedComponent->SetVisibility(aOpened, true);
	Rot0WallAttachedComponent->SetVisibility(aOpened, true);
	Rot90WallAttachedComponent->SetVisibility(aOpened, true);
	Rot180WallAttachedComponent->SetVisibility(aOpened, true);
	Rot270WallAttachedComponent->SetVisibility(aOpened, true);

	ZoneOpendWidgetComponent->SetVisibility(!aOpened);
}

const FMS_GridData& AMS_Zone::GetGrid(const FIntVector2& aGridPosition) const
{
	static FMS_GridData Dummy;
	if (!Grids.Contains(aGridPosition))
	{
		MS_Ensure(false);
		return Dummy;
	}
	
	return *Grids.Find(aGridPosition);
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

