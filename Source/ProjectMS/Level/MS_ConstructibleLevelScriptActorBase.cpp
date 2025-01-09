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

bool AMS_ConstructibleLevelScriptActorBase::AreAllPropSpacesInValidGrids(AMS_Prop* aProp)
{
	if (!IsValid(aProp))
	{
		return false;
	}
	
	if (aProp->GetPropType() != EMS_PropType::Furniture && aProp->GetPropType() != EMS_PropType::Structure)
	{
		return true;
	}
	
	const TArray<UMS_PropSpaceComponent*>& PropSpaceComponents = aProp->GetPropSpaceComponents();
		
	for (const UMS_PropSpaceComponent* PropSpaceComponent : PropSpaceComponents)
	{
		FIntVector WorldStartGridPosition = FIntVector::ZeroValue;
		FIntVector GridNum = FIntVector::ZeroValue;
			
		PropSpaceComponent->GetGridPositions(WorldStartGridPosition, GridNum);

		bool IsInValidGrid = false;
		
		// Set With Grid
		for (int i = 0; i < GridNum.Y; ++i)
		{
			if (IsInValidGrid)
			{
				break;
			}
			
			for (int j = 0; j < GridNum.X; ++j)
			{
				FIntVector2 WorldGridPosition = FIntVector2(WorldStartGridPosition.X + j, WorldStartGridPosition.Y + i);

				int32 ZoneIndex;
				FIntVector2 ZoneGridPosition;
							
				if (ConvertWorldGridPositionToZoneGridPosition(WorldGridPosition, ZoneIndex, ZoneGridPosition))
				{
					IsInValidGrid = true;
					break;
				}
			}
		}

		if (!IsInValidGrid)
		{
			return false;
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
