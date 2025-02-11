// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_Zone.h"

#include "MS_Define.h"
#include "Component/Actor/Prop/MS_PropSpaceComponent.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Controller/MS_PlayerController.h"
#include "PlayerState/MS_PlayerState.h"
#include "ContentsUtilities/MS_LevelDefine.h"
#include "Manager_Both/MS_UnitManager.h"
#include "Prop/MS_Prop.h"
#include "Prop/Floor/MS_Floor.h"
#include "Prop/Gate/MS_Gate.h"
#include "Prop/Wall/MS_Wall.h"
#include "Units/MS_GateUnit.h"
#include "Widget/Market/MS_ZoneOpenWidget.h"


AMS_Zone::AMS_Zone(const FObjectInitializer& aObjectInitializer)
	: Super(aObjectInitializer), ZoneIndex(INDEX_NONE), ZoneType(EMS_ZoneType::None)
{
	// Component
	ZoneBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("ZoneBoxComponent"));
	if (ZoneBoxComponent)
	{
		ZoneBoxComponent->SetupAttachment(SceneRootComponent);
	}
	
	FloorAttachedComponent = CreateDefaultSubobject<USceneComponent>(TEXT("FloorAttachedComponent"));
	if (FloorAttachedComponent)
	{
		FloorAttachedComponent->SetupAttachment(ZoneBoxComponent);
	}
	
	WallAttachedComponent = CreateDefaultSubobject<USceneComponent>(TEXT("WallAttachedComponent"));
	if (WallAttachedComponent)
	{
		WallAttachedComponent->SetupAttachment(ZoneBoxComponent);
	}

	ZoneOpenWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("ZoneOpendWidgetComponent"));
	if (ZoneOpenWidgetComponent)
	{
		ZoneOpenWidgetComponent->SetupAttachment(ZoneBoxComponent);

		ZoneOpenWidgetComponent->SetVisibility(true);
	}

	// Cache
	Walls.Empty();
}

void AMS_Zone::PreInitializeComponents()
{
	Super::PreInitializeComponents();
}

void AMS_Zone::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	InitializeZoneData();
	
	RegisterDefalutAttachedProps();
}

void AMS_Zone::BeginPlay()
{
	Super::BeginPlay();

	if (ZoneOpenWidgetComponent)
	{
		if (UMS_ZoneOpenWidget* ZoneOpenWidget = Cast<UMS_ZoneOpenWidget>(ZoneOpenWidgetComponent->GetWidget()))
		{
			ZoneOpenWidget->OnClickZoneOpenButtonDelegate.BindUObject(this, &AMS_Zone::OnClickZoneOpenWidget);
		}
	}
	
	if (FloorAttachedComponent)
	{
		if (!bOpened)
		{
			FloorAttachedComponent->SetVisibility(false, true);
		}
	}
	
	if (ZoneType == EMS_ZoneType::Pallet)
	{
		SetZoneOpened(true);	// LevelScriptActor에서 확인해서 OnZoneOpened 호출
	}
}

void AMS_Zone::InitializeZoneData()
{
	MS_CHECK(ZoneBoxComponent);
	
	ZoneLocation = ZoneBoxComponent->GetComponentLocation() - ZoneBoxComponent->GetUnscaledBoxExtent();
	
	ZoneSize = ZoneBoxComponent->GetUnscaledBoxExtent() * 2.f;
	
	ZoneGridNum = FIntVector2(FMath::RoundToInt32(ZoneSize.X / MS_GridSize.X),
		FMath::RoundToInt32(ZoneSize.Y / MS_GridSize.Y));
	
	ZoneWorldGridPosition = FMS_GridData::ConvertLocationToGridPosition(ZoneLocation);

	CreateGrids();
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
		if (AMS_Floor* Floor = Cast<AMS_Floor>(AttachedActor))
		{
			// Prop Center Grid
			FVector WorldLocation = Floor->GetActorLocation();
			FIntVector2 GridPosition = FMS_GridData::ConvertLocationToGridPosition(WorldLocation);
			
			Floor->SetZoneData(this);

			RegisterFloorToGrid(GridPosition, Floor);
		}

		else if (AMS_Wall* Wall = Cast<AMS_Wall>(AttachedActor))
		{
			Walls.Emplace(Wall);
		}

		else if (AMS_Gate* Gate = Cast<AMS_Gate>(AttachedActor))
		{
			Gate->SetZoneData(this);

			// Create Unit
			TObjectPtr<UMS_GateUnit> Unit = Cast<UMS_GateUnit>(gUnitMng.CreateUnit(EMS_UnitType::Gate, Gate->GetTableIndex(), false));
			if (IsValid(Unit))
			{
				// Set Unit Actor
				if (!Unit->SetUnitActor(Gate))
				{
					MS_LOG_VERBOSITY(Error, TEXT("[%s] Set Unit Actor Fail"), *MS_FUNC_STRING);
					MS_ENSURE(false);
				}
			}
			else
			{
				MS_LOG_VERBOSITY(Error, TEXT("[%s] Create Unit Fail"), *MS_FUNC_STRING);
				MS_ENSURE(false);
			}

			// Prop Space
			const TArray<UMS_PropSpaceComponent*>& PropSpaceComponents = Gate->GetPropSpaceComponents();

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
						
						if (IsGridContained(GridPosition))
						{
							RegisterObjectToGrid(GridPosition, PropSpaceComponent);
						}
						else
						{
							MS_LOG_VERBOSITY(Error, TEXT("[%s] All gate prop spaces must be within the attacked zone [Gate Id : %d]"), *MS_FUNC_STRING, Gate->GetGateIndex());
							MS_ENSURE(false);
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

void AMS_Zone::RegisterFloorToGrid(const FIntVector2& aGridPosition, TWeakObjectPtr<AMS_Floor> aFloor)
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
			MS_LOG_VERBOSITY(Error, TEXT("Floor data alreay exists [%s - X : %d, Y : %d]"),
				*GetActorLabel(), aGridPosition.X, aGridPosition.Y);

			MS_ENSURE(false);
		}
	}
	else
	{
		MS_LOG_VERBOSITY(Error, TEXT("Floor's GridPosition is not vaild [%s - X : %d, Y : %d]"),
			*GetActorLabel(), aGridPosition.X, aGridPosition.Y);

		MS_ENSURE(false);
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
			MS_LOG_VERBOSITY(Error, TEXT("Object data alreay exists [%s - X : %d, Y : %d]"),
				*GetActorLabel(), aGridPosition.X, aGridPosition.Y);

			MS_ENSURE(false);
		}

		if (GridData.PropSpaceComponent == nullptr)
		{
			GridData.PropSpaceComponent = aPropSpaceComponent;
		}
		else
		{
			MS_LOG_VERBOSITY(Error, TEXT("PropSpaceComponent data alreay exists [Zone %d - X : %d, Y : %d]"),
				ZoneIndex, aGridPosition.X, aGridPosition.Y);

			MS_ENSURE(false);
		}
	}
	else
	{
		MS_LOG_VERBOSITY(Error, TEXT("Object's GridPosition is not vaild [%s - X : %d, Y : %d]"),
			*GetActorLabel(), aGridPosition.X, aGridPosition.Y);

		MS_ENSURE(false);
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
		MS_LOG_VERBOSITY(Error, TEXT("Object's GridPosition is not vaild [%s - X : %d, Y : %d]"),
			*GetActorLabel(), aGridPosition.X, aGridPosition.Y);

		MS_ENSURE(false);
	}
}

void AMS_Zone::OnClickZoneOpenWidget(UMS_ZoneOpenWidget* aZoneOpenWidget)
{
	bool bBound = RequestOpenZoneDelegate.ExecuteIfBound(ZoneIndex);
}

void AMS_Zone::OnZoneOpened()
{
	FloorAttachedComponent->SetVisibility(true, true);
	ZoneOpenWidgetComponent->SetVisibility(false);
}

void AMS_Zone::OnAnyZoneOpened(TWeakObjectPtr<class AMS_ConstructibleLevelScriptActorBase> aOwnerLevelScriptActor)
{
	if (ZoneType == EMS_ZoneType::Passage)
	{
		if (CanOpenZone())
		{
			bool bBound = RequestOpenZoneDelegate.ExecuteIfBound(ZoneIndex);
		}
	}
	
	SetWallVisibilities(aOwnerLevelScriptActor);
}

void AMS_Zone::SetWallVisibilities(TWeakObjectPtr<AMS_ConstructibleLevelScriptActorBase> aOwnerLevelScriptActor)
{
	for (auto It = Walls.CreateConstIterator(); It; ++It)
	{
		It->Get()->SetVisibilityByGridOpened(aOwnerLevelScriptActor);
	}
}

bool AMS_Zone::CanOpenZone()
{
	if (bOpened)
	{
		return false;
	}
	
	UWorld* World = GetWorld();
	if (!IsValid(World))
	{
		return false;
	}

	AMS_PlayerController* PlayerController = World->GetFirstPlayerController<AMS_PlayerController>();
	if (!IsValid(PlayerController))
	{
		return false;
	}
	
	AMS_PlayerState* PlayerState = PlayerController->GetPlayerState<AMS_PlayerState>();
	if (!IsValid(PlayerState))
	{
		return false;
	}

	const TArray<int32>& OpenedZoneIds = PlayerState->GetOpenedZoneIds();

	if (ZoneType == EMS_ZoneType::Passage)
	{
		for (int32 TestId : TestConditionZoneIds)
		{
			if (!OpenedZoneIds.Contains(TestId))
			{
				return false;
			}
		}

		return true;
	}
	else
	{
		for (int32 TestId : TestConditionZoneIds)
		{
			if (OpenedZoneIds.Contains(TestId))
			{
				return true;
			}
		}

		return false;
	}
}

const FMS_GridData* AMS_Zone::GetGrid(const FIntVector2& aGridPosition) const
{
	if (!Grids.Contains(aGridPosition))
	{
		MS_ENSURE(false);
		return nullptr;
	}
	
	return Grids.Find(aGridPosition);
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
					MS_LOG_VERBOSITY(VeryVerbose, TEXT("ZoneGrid %d-%d,%d : %s, SpaceType : %d, PurposeType : %d"),
						ZoneIndex, j, i, *pGrid->Object->GetName(),
						static_cast<uint8>(pGrid->PropSpaceComponent->GetPropSpaceType()),
						static_cast<uint8>(pGrid->PropSpaceComponent->GetPropPurposeSpaceType()));
				}
			}
		}
	}
#endif
}

