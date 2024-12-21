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
			float PropYaw = Prop->GetActorRotation().Yaw;
			MS_LOG_Verbosity(Warning, TEXT("PropYaw : %f [PropName : %s]"), PropYaw, *Prop->GetName());

			
			// Start Position
			FVector SpaceStartOffset;
			if (FMath::IsNearlyEqual(PropYaw, 0.f) || FMath::IsNearlyEqual(PropYaw, 180.f) || FMath::IsNearlyEqual(PropYaw, -180.f))
			{
				SpaceStartOffset = FVector(-PropSpaceComponent->GetUnscaledBoxExtent().X, -PropSpaceComponent->GetUnscaledBoxExtent().Y, 0.f);
			}
			else
			{
				SpaceStartOffset = FVector(-PropSpaceComponent->GetUnscaledBoxExtent().Y, -PropSpaceComponent->GetUnscaledBoxExtent().X, 0.f);
			}
			
			FVector WorldStartLocation = PropSpaceComponent->GetComponentLocation() + SpaceStartOffset;
			FIntVector WorldStartPosition = FIntVector(FMath::RoundToInt32(WorldStartLocation.X / MS_GridSize.X), FMath::RoundToInt32(WorldStartLocation.Y / MS_GridSize.Y), 0);

			// Num
			FVector SpaceSize;
			if (FMath::IsNearlyEqual(PropYaw, 0.f) || FMath::IsNearlyEqual(PropYaw, 180.f) || FMath::IsNearlyEqual(PropYaw, -180.f))
			{
				SpaceSize = FVector(PropSpaceComponent->GetUnscaledBoxExtent().X * 2.f, PropSpaceComponent->GetUnscaledBoxExtent().Y * 2.f, 0.f);
			}
			else
			{
				SpaceSize = FVector(PropSpaceComponent->GetUnscaledBoxExtent().Y * 2.f, PropSpaceComponent->GetUnscaledBoxExtent().X * 2.f, 0.f);
			}

			FIntVector GridNum = FIntVector(FMath::RoundToInt32(SpaceSize.X / MS_GridSize.X), FMath::RoundToInt32(SpaceSize.Y / MS_GridSize.Y), 0);

			// Set With Grid
			for (int i = 0; i < GridNum.Y; ++i)
			{
				for (int j = 0; j < GridNum.X; ++j)
				{
					FIntVector2 WorldGridPosition = FIntVector2(WorldStartPosition.X + j, WorldStartPosition.Y + i);

					switch (Prop->GetPropType())
					{
					case EMS_PropType::Floor:
						{
							for (auto& Zone : Zones)
							{
								FIntVector2 ZoneGridPosition;
								if (Zone.Value->IsWorldGridContained(WorldGridPosition, ZoneGridPosition))
								{
									Zone.Value->RegisterFloorToGrid(ZoneGridPosition, Prop);
									
									break;
								}
							}
					
							break;
						}

					case EMS_PropType::Furniture:
					case EMS_PropType::Structure:
						{
							for (auto& Zone : Zones)
							{
								FIntVector2 ZoneGridPosition;
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

	// Debug
	/*
#if WITH_EDITOR
	for (auto& Zone : Zones)
	{
		Zone.Value->ShowDebugZoneData();
	}
#endif
*/
}
