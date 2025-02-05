// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ConstructibleLevelScriptActorBase.h"

#include "MS_Define.h"
#include "Kismet/GameplayStatics.h"

#include "Prop/MS_Prop.h"
#include "Component/Prop/MS_PropSpaceComponent.h"
#include "Manager_Both/MS_UnitManager.h"
#include "Manager_Client/MS_SceneManager.h"
#include "Prop/Floor/MS_Floor.h"
#include "Prop/Wall/MS_Wall.h"
#include "Units/MS_FurnitureUnit.h"
#include "Zone/MS_Zone.h"


AMS_ConstructibleLevelScriptActorBase::AMS_ConstructibleLevelScriptActorBase()
	: HasBegun(false)
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMS_ConstructibleLevelScriptActorBase::BeginPlay()
{
	Super::BeginPlay();

	if (!HasBegun)
	{
		HasBegun = true;
		
		ParsingDefaultPropDatas();

		SetWallVisibilities();
	}
}

void AMS_ConstructibleLevelScriptActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMS_ConstructibleLevelScriptActorBase::ParsingDefaultPropDatas()
{
	// Zone
	for (auto& Zone : Zones)
	{
		Zone.Value->SetZoneIndex(Zone.Key);

		if (Zone.Key == 1)
		{
			Zone.Value->SetZoneOpened(true);
		}
		else
		{
			Zone.Value->SetZoneOpened(false);
		}

		Zone.Value->OnZoneOpendDelegate.AddDynamic(this, &AMS_ConstructibleLevelScriptActorBase::SetWallVisibilities);
	}
	
	// Prop
	TArray<AActor*> PropActors;

	// ToDo : 스트리밍 레벨 뿐 아니라 모든 레벨의 액터를 불러오나?
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMS_Prop::StaticClass(), PropActors);
	
	for (AActor* PropActor : PropActors)
	{
		AMS_Prop* Prop = Cast<AMS_Prop>(PropActor);
		
		// Prop Center Grid
		FVector WorldCenterLocation = PropActor->GetActorLocation();
		
		FIntVector2 PropCenterGridPosition = FIntVector2(FMath::RoundToInt32(WorldCenterLocation.X) / MS_GridSizeInt.X
			, FMath::RoundToInt32(WorldCenterLocation.Y) / MS_GridSizeInt.Y);
		
		int32 PropCenterZoneIndex = GetGridZoneIndex(PropCenterGridPosition);
		if (PropCenterZoneIndex == INDEX_NONE)
		{
			continue;
		}

		Prop->SetZoneData(*Zones.Find(PropCenterZoneIndex));

		// Check Prop Type
		if (Prop->GetPropType() != EMS_PropType::Furniture && Prop->GetPropType() != EMS_PropType::Structure)
		{
			continue;
		}

		// Create Unit (임시)
		TObjectPtr<UMS_FurnitureUnit> Unit = Cast<UMS_FurnitureUnit>(gUnitMng.CreateUnit(EMS_UnitType::Furniture, Prop->GetTableIndex(), false));
		if (IsValid(Unit))
		{
			// Set Unit Actor
			if (!Unit->SetUnitActor(Prop))
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
					
					for (auto& Zone : Zones)
					{
						if (Zone.Value->IsGridContained(GridPosition))
						{
							Zone.Value->RegisterObjectToGrid(GridPosition, PropSpaceComponent);
							break;
						}
					}
				}
			}
		}
	}
}

void AMS_ConstructibleLevelScriptActorBase::RegisterGridObjectData(TArray<const FMS_GridData*>& aGridDatas,
	TWeakObjectPtr<UMS_PropSpaceComponent> aPropSpaceComponent)
{
	for (const FMS_GridData* GridData : aGridDatas)
	{
		AMS_Zone* Zone = Cast<AMS_Zone>(GridData->GetOwnerZone());
		Zone->RegisterObjectToGrid(GridData->GetGridPosition(), aPropSpaceComponent);
	}
}

void AMS_ConstructibleLevelScriptActorBase::RegisterGridObjectData(
	TArray<FMS_GridDataForPropSpace>& aGridDatasForPropSpaces)
{
	for (const FMS_GridDataForPropSpace& GridDataForPropSpace : aGridDatasForPropSpaces)
	{
		UMS_PropSpaceComponent* PropSpaceComponent = GridDataForPropSpace.PropSpaceComponent;
		if (!IsValid(PropSpaceComponent))
		{
			MS_ENSURE(false);
			return;
		}
		
		TArray<const FMS_GridData*> GridDatas = GridDataForPropSpace.GridDatas;
		
		for (const FMS_GridData* GridData : GridDatas)
		{
			AMS_Zone* Zone = Cast<AMS_Zone>(GridData->GetOwnerZone());
			Zone->RegisterObjectToGrid(GridData->GetGridPosition(), PropSpaceComponent);
		}
	}
}

void AMS_ConstructibleLevelScriptActorBase::UnregisterGridObjectData(TArray<const FMS_GridData*>& aGridDatas)
{
	for (const FMS_GridData* GridData : aGridDatas)
	{
		AMS_Zone* Zone = Cast<AMS_Zone>(GridData->GetOwnerZone());
		Zone->UnregisterObjectToGrid(GridData->GetGridPosition());
	}
}

void AMS_ConstructibleLevelScriptActorBase::UnregisterGridObjectData(
	TArray<FMS_GridDataForPropSpace>& aGridDatasForPropSpaces)
{
	for (const FMS_GridDataForPropSpace& GridDataForPropSpace : aGridDatasForPropSpaces)
	{
		TArray<const FMS_GridData*> GridDatas = GridDataForPropSpace.GridDatas;
		
		for (const FMS_GridData* GridData : GridDatas)
		{
			AMS_Zone* Zone = Cast<AMS_Zone>(GridData->GetOwnerZone());
			Zone->UnregisterObjectToGrid(GridData->GetGridPosition());
		}
	}
}

bool AMS_ConstructibleLevelScriptActorBase::GetGridDatasForAllPropSpaceLocations(class AMS_Prop* aInProp,
                                                                                 TArray<FMS_GridDataForPropSpace>& aOutGridDatasForPropSpaces, const FIntVector2& aInAddtiveGridPosition) // Ret : AllGridInZones
{
	if (!IsValid(aInProp))
	{
		return false;
	}
	
	if (aInProp->GetPropType() != EMS_PropType::Furniture && aInProp->GetPropType() != EMS_PropType::Structure)
	{
		return true;
	}

	aOutGridDatasForPropSpaces.Empty();
	
	const TArray<UMS_PropSpaceComponent*>& PropSpaceComponents = aInProp->GetPropSpaceComponents();
		
	for (UMS_PropSpaceComponent* PropSpaceComponent : PropSpaceComponents)
	{
		FMS_GridDataForPropSpace GridDataForPropSpace;
		GridDataForPropSpace.PropSpaceComponent = PropSpaceComponent;
		
		FIntVector2 StartGridPosition = FIntVector2::ZeroValue;
		FIntVector2 GridNum = FIntVector2::ZeroValue;
			
		PropSpaceComponent->GetGridPositions(StartGridPosition, GridNum);
		StartGridPosition += aInAddtiveGridPosition;
		
		// Set With Grid
		for (int i = 0; i < GridNum.Y; ++i)
		{
			for (int j = 0; j < GridNum.X; ++j)
			{
				FIntVector2 GridPosition = FIntVector2(StartGridPosition.X + j, StartGridPosition.Y + i);

				int32 ZoneIndex = GetGridZoneIndex(GridPosition);

				if (ZoneIndex == INDEX_NONE)
				{
					return false;
				}

				AMS_Zone* Zone = *Zones.Find(ZoneIndex);
				if (!IsValid(Zone) || !Zone->IsOpened())
				{
					return false;
				}
				
				const FMS_GridData* GridData = (*Zones.Find(ZoneIndex))->GetGrid(GridPosition);
				if (GridData == nullptr)
				{
					return false;
				}

				GridDataForPropSpace.GridDatas.Emplace(GridData);
			}
		}

		aOutGridDatasForPropSpaces.Emplace(GridDataForPropSpace);
	}

	return true;
}

bool AMS_ConstructibleLevelScriptActorBase::GetGridDatasForPropSpaceLocations(
	UMS_PropSpaceComponent* aPropSpaceComponent, TArray<const FMS_GridData*>& aOutGridDatas,
	const FIntVector2& aInAddtiveGridPosition)
{
	if (!IsValid(aPropSpaceComponent))
	{
		return false;
	}

	AMS_Prop* OwnerProp = aPropSpaceComponent->GetOwnerProp();
	if (!IsValid(OwnerProp))
	{
		return false;
	}
	
	if (OwnerProp->GetPropType() != EMS_PropType::Furniture && OwnerProp->GetPropType() != EMS_PropType::Structure)
	{
		return true;
	}

	aOutGridDatas.Empty();
	
	FIntVector2 StartGridPosition = FIntVector2::ZeroValue;
	FIntVector2 GridNum = FIntVector2::ZeroValue;
		
	aPropSpaceComponent->GetGridPositions(StartGridPosition, GridNum);
	StartGridPosition += aInAddtiveGridPosition;
	
	// Set With Grid
	for (int i = 0; i < GridNum.Y; ++i)
	{
		for (int j = 0; j < GridNum.X; ++j)
		{
			FIntVector2 GridPosition = FIntVector2(StartGridPosition.X + j, StartGridPosition.Y + i);

			int32 ZoneIndex = GetGridZoneIndex(GridPosition);

			if (ZoneIndex == INDEX_NONE)
			{
				return false;
			}

			AMS_Zone* Zone = *Zones.Find(ZoneIndex);
			if (!IsValid(Zone) || !Zone->IsOpened())
			{
				return false;
			}
				
			const FMS_GridData* GridData = (*Zones.Find(ZoneIndex))->GetGrid(GridPosition);
			if (GridData == nullptr)
			{
				return false;
			}

			aOutGridDatas.Emplace(GridData);
		}
	}

	return true;
}

int32 AMS_ConstructibleLevelScriptActorBase::GetGridZoneIndex(const FIntVector2& aGridPosition) const
{
	for (auto& Zone : Zones)
	{
		if (Zone.Value->IsGridContained(aGridPosition))
		{
			return Zone.Key;
		}
	}

	// MS_Ensure(false);
	return INDEX_NONE;
}

bool AMS_ConstructibleLevelScriptActorBase::IsGridOpened(const FIntVector2& aGridPosition) const
{
	int32 GridZoneIndex = GetGridZoneIndex(aGridPosition);
	if (GridZoneIndex == INDEX_NONE)
	{
		return false;
	}

	AMS_Zone* Zone = *Zones.Find(GridZoneIndex); // GetGridZoneIndex에서 ContainsCheck 완료
	if (IsValid(Zone))
	{
		return Zone->IsOpened();
	}

	return false;
}

void AMS_ConstructibleLevelScriptActorBase::SetWallVisibilities()
{
	// Prop
	TArray<AActor*> WallActors;

	// ToDo : 스트리밍 레벨 뿐 아니라 모든 레벨의 액터를 불러오나?
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMS_Wall::StaticClass(), WallActors);
	
	for (AActor* WallActor : WallActors)
	{
		AMS_Wall* Wall = Cast<AMS_Wall>(WallActor);
		
		if (IsValid(Wall))
		{
			Wall->SetVisibilityByGridOpened(this);
		}
	}
}

void AMS_ConstructibleLevelScriptActorBase::ShowUnconstructableGrid(bool bShow)
{
	return;
	
	if (bShowUnconstructableGrid != bShow)
	{
		bShowUnconstructableGrid = bShow;
		
		for (auto& Zone : Zones)
		{
			const TMap<FIntVector2, FMS_GridData>& Grids = Zone.Value->GetGrids();
			{
				for (auto& Grid : Grids)
				{
					if (AMS_Floor* Floor = Cast<AMS_Floor>(Grid.Value.Floor.Get()))
					{
						if (!bShowUnconstructableGrid || Grid.Value.Object == nullptr)
						{
							Floor->SetMaterial(FName("Normal"));
						}
						else
						{
							Floor->SetMaterial(FName("Unconstructable"));
						}
					}
				}
			}
		}
	}
}
