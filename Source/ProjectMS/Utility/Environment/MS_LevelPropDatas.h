

#pragma once

#include "CoreMinimal.h"
#include "MS_LevelPropDatas.generated.h"


#define MS_GridSize FVector(50.f, 50.f, 50.f)


UENUM(BlueprintType)
enum class EMS_PropType : uint8
{
	None = 0,
	Floor = 1,
	Wall = 2,
	Furniture = 3,
	Structure = 4,
};

UENUM(BlueprintType)
enum class EMS_PropSpaceType : uint8
{
	None = 0,
	ShapeSpace = 1,
	FreeSpace = 2,
};

// LevelPropDatas
USTRUCT(BlueprintType)
struct FMS_LevelPropDatas
{
	GENERATED_BODY()

public:
	FMS_LevelPropDatas()
	{
	}

	virtual ~FMS_LevelPropDatas()
	{
	}
};

USTRUCT(BlueprintType)
struct FMS_LevelPropDatas_Indoor : public FMS_LevelPropDatas
{
	GENERATED_BODY()

public:
	FMS_LevelPropDatas_Indoor()
	{
	}

	virtual ~FMS_LevelPropDatas_Indoor() override
	{
	}
	
public:
	UPROPERTY()
	TMap<FIntVector, TObjectPtr<AActor>> FloorDatas;

	UPROPERTY()
	TMap<FIntVector, TObjectPtr<AActor>> WallDatas_0;

	UPROPERTY()
	TMap<FIntVector, TObjectPtr<AActor>> WallDatas_90;

	UPROPERTY()
	TMap<FIntVector, TObjectPtr<AActor>> WallDatas_180;

	UPROPERTY()
	TMap<FIntVector, TObjectPtr<AActor>> WallDatas_270;
	
	UPROPERTY()
	TMap<FIntVector, TObjectPtr<AActor>> FurnitureDatas;

	UPROPERTY()
	TMap<FIntVector, TObjectPtr<AActor>> StructureDatas;
};

USTRUCT(BlueprintType)
struct FMS_LevelPropDatas_Outdoor : public FMS_LevelPropDatas
{
	GENERATED_BODY()

public:
	FMS_LevelPropDatas_Outdoor()
	{
	}

	virtual ~FMS_LevelPropDatas_Outdoor() override
	{
	}
};