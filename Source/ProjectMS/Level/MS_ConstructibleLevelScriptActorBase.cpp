// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ConstructibleLevelScriptActorBase.h"

#include "MS_Define.h"
#include "Kismet/GameplayStatics.h"

#include "Prop/MS_Prop.h"
#include "Component/Prop/Grid/MS_GridBoxComponent.h"
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

		const TArray<UMS_GridBoxComponent*>& GridBoxComponents = Prop->GetGridBoxComponents();
		
		for (UMS_GridBoxComponent* GridBoxComponent : GridBoxComponents)
		{
			float PropYaw = Prop->GetActorRotation().Yaw;
			MS_LOG_Verbosity(Warning, TEXT("PropYaw : %f [PropName : %s]"), PropYaw, *Prop->GetName());

			FVector GridLocationOffset = GridBoxComponent->GetGridLocationOffset();
			GridLocationOffset = GridLocationOffset.RotateAngleAxis(PropYaw, FVector(0.f, 0.f, 1.f));
			
			FVector WorldLocation = GridBoxComponent->GetComponentLocation() + GridLocationOffset;
			MS_LOG_Verbosity(Warning, TEXT("WorldLocation : %f, %f, %f [PropName : %s]"), WorldLocation.X, WorldLocation.Y, WorldLocation.Z, *Prop->GetName());
			
			FIntVector WorldGridPosition = FIntVector(WorldLocation / MS_GridSize);

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

							Prop->SetZoneData(Zone.Value, ZoneGridPosition);

							break;
						}
					}
					
					break;
				}
			
			default:
				break;
			}

			// OnRegister
			// GridBoxComponent->OnRegisteredWithLevelPropDatas(WorldGridPosition);
		}
	}
}
