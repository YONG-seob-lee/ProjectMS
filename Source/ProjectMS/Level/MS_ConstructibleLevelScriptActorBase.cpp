// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ConstructibleLevelScriptActorBase.h"

#include "MS_Define.h"
#include "Kismet/GameplayStatics.h"

#include "Prop/MS_Prop.h"
#include "Component/Prop/MS_PropSpaceComponent.h"
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
	}
	
	// Prop
	TArray<AActor*> PropActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMS_Prop::StaticClass(), PropActors);
	
	for (AActor* PropActor : PropActors)
	{
		AMS_Prop* Prop = Cast<AMS_Prop>(PropActor);

		if (Prop->GetPropType() == EMS_PropType::Furniture)
		{
			MS_LOG(TEXT("Debug"));
		}
		
		// Center Position
		FVector WorldCenterLocation = PropActor->GetActorLocation();

		// Set With Center
		for (auto& Zone : Zones)
		{
			FVector PropCenterLocation;
			if (Zone.Value->IsWorldLocationContained(WorldCenterLocation, PropCenterLocation))
			{
				Prop->SetZoneData(Zone.Value, PropCenterLocation);
									
				break;
			}
		}
		
		const TArray<UMS_PropSpaceComponent*>& PropSpaceComponents = Prop->GetPropSpaceComponents();
		
		for (UMS_PropSpaceComponent* PropSpaceComponent : PropSpaceComponents)
		{
			FIntVector WorldStartGridPosition = FIntVector::ZeroValue;
			FIntVector GridNum = FIntVector::ZeroValue;
			
			PropSpaceComponent->GetGridPositions(WorldStartGridPosition, GridNum);
			
			// Set With Grid
			for (int i = 0; i < GridNum.Y; ++i)
			{
				for (int j = 0; j < GridNum.X; ++j)
				{
					FIntVector2 WorldGridPosition = FIntVector2(WorldStartGridPosition.X + j, WorldStartGridPosition.Y + i);

					switch (Prop->GetPropType())
					{
					case EMS_PropType::Floor:
						{
							int32 ZoneIndex;
							FIntVector2 ZoneGridPosition;
							
							if (ConvertWorldGridPositionToZoneGridPosition(WorldGridPosition, ZoneIndex, ZoneGridPosition))
							{
								(*Zones.Find(ZoneIndex))->RegisterFloorToGrid(ZoneGridPosition, Prop);
							}
					
							break;
						}

					case EMS_PropType::Furniture:
					case EMS_PropType::Structure:
						{
							for (auto& Zone : Zones)
							{
								FIntVector2 ZoneGridPosition = FIntVector2::ZeroValue;
								if (Zone.Value->IsWorldGridContained(WorldGridPosition, ZoneGridPosition))
								{
									Zone.Value->RegisterObjectToGrid(ZoneGridPosition, PropSpaceComponent);
									
									break;
								}
							}
							break;
							
							default:
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
		Zone->RegisterObjectToGrid(GridData->GetZoneGridPosition(), aPropSpaceComponent);
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
			MS_Ensure(false);
			return;
		}
		
		TArray<const FMS_GridData*> GridDatas = GridDataForPropSpace.GridDatas;
		
		for (const FMS_GridData* GridData : GridDatas)
		{
			AMS_Zone* Zone = Cast<AMS_Zone>(GridData->GetOwnerZone());
			Zone->RegisterObjectToGrid(GridData->GetZoneGridPosition(), PropSpaceComponent);
		}
	}
}

void AMS_ConstructibleLevelScriptActorBase::UnregisterGridObjectData(TArray<const FMS_GridData*>& aGridDatas)
{
	for (const FMS_GridData* GridData : aGridDatas)
	{
		AMS_Zone* Zone = Cast<AMS_Zone>(GridData->GetOwnerZone());
		Zone->UnregisterObjectToGrid(GridData->GetZoneGridPosition());
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
			Zone->UnregisterObjectToGrid(GridData->GetZoneGridPosition());
		}
	}
}

bool AMS_ConstructibleLevelScriptActorBase::GetGridDatasForAllPropSpaceLocations(class AMS_Prop* aInProp,
                                                                                 TArray<FMS_GridDataForPropSpace>& aOutGridDatasForPropSpaces, const FIntVector& aInAddtiveGridPosition) // Ret : AllGridInZones
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
		
		FIntVector WorldStartGridPosition = FIntVector::ZeroValue;
		FIntVector GridNum = FIntVector::ZeroValue;
			
		PropSpaceComponent->GetGridPositions(WorldStartGridPosition, GridNum);
		WorldStartGridPosition += aInAddtiveGridPosition;
		
		// Set With Grid
		for (int i = 0; i < GridNum.Y; ++i)
		{
			for (int j = 0; j < GridNum.X; ++j)
			{
				FIntVector2 WorldGridPosition = FIntVector2(WorldStartGridPosition.X + j, WorldStartGridPosition.Y + i);

				int32 ZoneIndex;
				FIntVector2 ZoneGridPosition;
							
				if (ConvertWorldGridPositionToZoneGridPosition(WorldGridPosition, ZoneIndex, ZoneGridPosition))
				{
					const FMS_GridData& GridData = (*Zones.Find(ZoneIndex))->GetGrid(ZoneGridPosition);
					GridDataForPropSpace.GridDatas.Emplace(&GridData);
				}
				else
				{
					aOutGridDatasForPropSpaces.Empty();
					return false;
				}
			}
		}

		aOutGridDatasForPropSpaces.Emplace(GridDataForPropSpace);
	}

	return true;
}

bool AMS_ConstructibleLevelScriptActorBase::GetGridDatasForPropSpaceLocations(
	UMS_PropSpaceComponent* aPropSpaceComponent, TArray<const FMS_GridData*>& aOutGridDatas,
	const FIntVector& aInAddtiveGridPosition)
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
	
	FIntVector WorldStartGridPosition = FIntVector::ZeroValue;
	FIntVector GridNum = FIntVector::ZeroValue;
		
	aPropSpaceComponent->GetGridPositions(WorldStartGridPosition, GridNum);
	WorldStartGridPosition += aInAddtiveGridPosition;
	
	// Set With Grid
	for (int i = 0; i < GridNum.Y; ++i)
	{
		for (int j = 0; j < GridNum.X; ++j)
		{
			FIntVector2 WorldGridPosition = FIntVector2(WorldStartGridPosition.X + j, WorldStartGridPosition.Y + i);

			int32 ZoneIndex;
			FIntVector2 ZoneGridPosition;
						
			if (ConvertWorldGridPositionToZoneGridPosition(WorldGridPosition, ZoneIndex, ZoneGridPosition))
			{
				const FMS_GridData& GridData = (*Zones.Find(ZoneIndex))->GetGrid(ZoneGridPosition);
				aOutGridDatas.Emplace(&GridData);
			}
			else
			{
				aOutGridDatas.Empty();
				return false;
			}
		}
	}

	return true;
}

bool AMS_ConstructibleLevelScriptActorBase::ConvertWorldGridPositionToZoneGridPosition(
	const FIntVector2& aInWorldGridPosition, int32& aOutZoneIndex, FIntVector2& aOutZoneGridPosition)
{
	for (auto& Zone : Zones)
	{
		FIntVector2 ZoneGridPosition;
		if (Zone.Value->IsWorldGridContained(aInWorldGridPosition, ZoneGridPosition))
		{
			aOutZoneIndex = Zone.Key;
			aOutZoneGridPosition = ZoneGridPosition;
			return true;
		}
	}

	return false;
}
