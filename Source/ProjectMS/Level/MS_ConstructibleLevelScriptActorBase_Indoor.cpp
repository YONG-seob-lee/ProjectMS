// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ConstructibleLevelScriptActorBase_Indoor.h"

#include "MS_Define.h"
#include "Kismet/GameplayStatics.h"

#include "Prop/MS_Prop.h"
#include "Component/Prop/Grid/MS_GridBoxComponent.h"


AMS_ConstructibleLevelScriptActorBase_Indoor::AMS_ConstructibleLevelScriptActorBase_Indoor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMS_ConstructibleLevelScriptActorBase_Indoor::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AMS_ConstructibleLevelScriptActorBase_Indoor::BeginPlay()
{
	Super::BeginPlay();

	ParsingDefaultPropDatas();
}

void AMS_ConstructibleLevelScriptActorBase_Indoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMS_ConstructibleLevelScriptActorBase_Indoor::ParsingDefaultPropDatas()
{
	Super::ParsingDefaultPropDatas();

	// Floor
	TArray<AActor*> PropActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMS_Prop::StaticClass(), PropActors);

	LevelPropDatas_Indoor.FloorDatas.Empty();
	for (AActor* PropActor : PropActors)
	{
		AMS_Prop* Prop = Cast<AMS_Prop>(PropActor);

		const TArray<UMS_GridBoxComponent*>& GridBoxComponents = Prop->GetGridBoxComponents();
		
		for (const UMS_GridBoxComponent* GridBoxComponent : GridBoxComponents)
		{
			float PropYaw = Prop->GetActorRotation().Yaw;
			MS_LOG_Verbosity(Warning, TEXT("PropYaw : %f [PropName : %s]"), PropYaw, *Prop->GetName());

			FVector GridLocationOffset = GridBoxComponent->GetGridLocationOffset();
			GridLocationOffset = GridLocationOffset.RotateAngleAxis(PropYaw, FVector(0.f, 0.f, 1.f));
			
			FVector WorldLocation = GridBoxComponent->GetComponentLocation() + GridLocationOffset;
			MS_LOG_Verbosity(Warning, TEXT("WorldLocation : %f, %f, %f [PropName : %s]"), WorldLocation.X, WorldLocation.Y, WorldLocation.Z, *Prop->GetName());
			
			FIntVector GridPosition = FIntVector(
			FMath::RoundToInt32(WorldLocation.X / MS_GridSize.X),
			FMath::RoundToInt32(WorldLocation.Y / MS_GridSize.Y),
			FMath::RoundToInt32(WorldLocation.Z / MS_GridSize.Z));

			switch (Prop->GetPropType())
			{
			case EMS_PropType::Floor:
				{
					MS_Ensure(!LevelPropDatas_Indoor.FloorDatas.Contains(GridPosition));
					LevelPropDatas_Indoor.FloorDatas.Emplace(GridPosition, PropActor);
					break;
				}

			case EMS_PropType::Wall:
				{
					if (FMath::IsNearlyEqual(PropYaw, 0.f))
					{
						MS_Ensure(!LevelPropDatas_Indoor.WallDatas_0.Contains(GridPosition));
						LevelPropDatas_Indoor.WallDatas_0.Emplace(GridPosition, PropActor);
					}
					else if (FMath::IsNearlyEqual(PropYaw, 90.f) || FMath::IsNearlyEqual(PropYaw, -270.f))
					{
						MS_Ensure(!LevelPropDatas_Indoor.WallDatas_90.Contains(GridPosition));
						LevelPropDatas_Indoor.WallDatas_90.Emplace(GridPosition, PropActor);
					}
					else if (FMath::IsNearlyEqual(PropYaw, 180.f) || FMath::IsNearlyEqual(PropYaw, -180.f))
					{
						MS_Ensure(!LevelPropDatas_Indoor.WallDatas_180.Contains(GridPosition));
						LevelPropDatas_Indoor.WallDatas_180.Emplace(GridPosition, PropActor);
					}
					else if (FMath::IsNearlyEqual(PropYaw, 270.f) || FMath::IsNearlyEqual(PropYaw, -90.f))
					{
						MS_Ensure(!LevelPropDatas_Indoor.WallDatas_270.Contains(GridPosition));
						LevelPropDatas_Indoor.WallDatas_270.Emplace(GridPosition, PropActor);
					}
					else
					{
						MS_LOG_Verbosity(Error, TEXT("Wall Rotation is Wrong [PropName : %s]"), *Prop->GetFName().ToString());
					}
					break;
				}
			
			case EMS_PropType::Furniture:
				{
					MS_Ensure(!LevelPropDatas_Indoor.FurnitureDatas.Contains(GridPosition));
					MS_Ensure(!LevelPropDatas_Indoor.StructureDatas.Contains(GridPosition));
					LevelPropDatas_Indoor.FurnitureDatas.Emplace(GridPosition, PropActor);
					break;
				}

			case EMS_PropType::Structure:
				{
					MS_Ensure(!LevelPropDatas_Indoor.FurnitureDatas.Contains(GridPosition));
					MS_Ensure(!LevelPropDatas_Indoor.StructureDatas.Contains(GridPosition));
					LevelPropDatas_Indoor.StructureDatas.Emplace(GridPosition, PropActor);
					break;
				}
			
			default:
				{
					MS_LOG_Verbosity(Error, TEXT("Prop Type is Wrong [PropName : %s]"), *Prop->GetFName().ToString());
				}
			}
		}
	}
}
