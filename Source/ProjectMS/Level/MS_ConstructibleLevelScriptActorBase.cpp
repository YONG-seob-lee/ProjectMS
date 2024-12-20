// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ConstructibleLevelScriptActorBase.h"

#include "MS_Define.h"
#include "Kismet/GameplayStatics.h"

#include "Prop/MS_Prop.h"
#include "Component/Prop/MS_PropSpaceComponent.h"
#include "Zone/MS_Zone.h"


AMS_ConstructibleLevelScriptActorBase::AMS_ConstructibleLevelScriptActorBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMS_ConstructibleLevelScriptActorBase::BeginPlay()
{
	Super::BeginPlay();

	ParsingDefaultPropDatas();
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
			FVector SpaceStartOffset = -PropSpaceComponent->GetUnscaledBoxExtent();
			SpaceStartOffset = SpaceStartOffset.RotateAngleAxis(PropYaw, FVector(0.f, 0.f, 1.f));
			
			FVector WorldStartLocation = PropSpaceComponent->GetComponentLocation() + SpaceStartOffset;
			MS_LOG_Verbosity(Warning, TEXT("WorldStartLocation : %f, %f, %f [PropName : %s]"), WorldStartLocation.X, WorldStartLocation.Y, WorldStartLocation.Z, *Prop->GetName());
			
			FIntVector WorldStartPosition = FIntVector(WorldStartLocation / MS_GridSize);

			// Num
			FVector DirectionalSpaceSize = PropSpaceComponent->GetUnscaledBoxExtent() * 2.f;
			DirectionalSpaceSize = DirectionalSpaceSize.RotateAngleAxis(PropYaw, FVector(0.f, 0.f, 1.f));

			FIntVector DirectionalGridNum = FIntVector(DirectionalSpaceSize / MS_GridSize);

			int32 WidthNum = FMath::Abs(DirectionalGridNum.X);
			int32 HeightNum = FMath::Abs(DirectionalGridNum.Y);

			int32 WidthSign = DirectionalGridNum.X >= 0 ? 1 : -1;
			int32 HeightSign = DirectionalGridNum.Y >= 0 ? 1 : -1;
			
			// Set With Grid
			for (int i = 0; i < HeightNum; ++i)
			{
				for (int j = 0; j < WidthNum; ++j)
				{
					FIntVector WorldGridPosition = FIntVector(WorldStartPosition.X + j * WidthSign, WorldStartPosition.Y + i * HeightSign, 0);

					switch (Prop->GetPropType())
					{
					case EMS_PropType::Floor:
						{
							for (auto& Zone : Zones)
							{
								FIntVector2 ZoneGridPosition;
								if (Zone.Value->IsWorldGridContained(FIntVector2(WorldGridPosition.X, WorldGridPosition.Y), ZoneGridPosition))
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
								if (Zone.Value->IsWorldGridContained(FIntVector2(WorldGridPosition.X, WorldGridPosition.Y), ZoneGridPosition))
								{
									Zone.Value->RegisterObjectToGrid(ZoneGridPosition, PropSpaceComponent);
									
									break;
								}
							}
							
							default:
								break;
						}
					}
				}
			}
		}
	}
}
