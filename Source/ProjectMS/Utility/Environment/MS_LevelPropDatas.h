

#pragma once

#include "CoreMinimal.h"
#include "MS_LevelPropDatas.generated.h"


#define MS_GridSize FVector(50.f, 50.f, 50.f)
#define MS_GridSizeInt FVector(50, 50, 50)


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
	StaffSpace = 3,
	
	PurposefulCustomerSpace = 4,
	PurposefulStaffSpace = 5,
	PurposefulCustomerAndStaffSpace = 6,
};

UENUM(BlueprintType)
enum class EMS_PurposeType : uint8
{
	None = 0,

	Cashier = 1,
	BeforePayment = 2,
	AfterPayment = 3,

	UseStorage = 4,
	
	Any = 100,	// != None
};

UENUM(BlueprintType)
enum class EMS_Rotation : uint8
{
	Rot0,
	Rot90,
	Rot180,
	Rot270
};

namespace MS_RotationFunc
{
	EMS_Rotation ConvertRotation(float aValue);
	float ConvertRotation(EMS_Rotation aEnum);

	EMS_Rotation RotateClockwise(EMS_Rotation aRotation);
}

// GridDatas
USTRUCT(BlueprintType)
struct FMS_GridData
{
	GENERATED_BODY()

public:
	FMS_GridData()
	: GridPosition(FIntVector2::ZeroValue)
	{
	}

	FMS_GridData(TWeakObjectPtr<AActor> aOwnerZone, FIntVector2 aWorldGridPosition)
		: OwnerZone(aOwnerZone), GridPosition(aWorldGridPosition)
	{
	}
	
	virtual ~FMS_GridData()
	{
	}

	TWeakObjectPtr<AActor> GetOwnerZone() const { return OwnerZone; }
	const FIntVector2& GetGridPosition() const { return GridPosition; }

	const FVector GetGridLocation() const;
	const FVector GetGridCenterLocation() const;

	
private:
	UPROPERTY()
	TWeakObjectPtr<AActor> OwnerZone;

	UPROPERTY()
	FIntVector2 GridPosition;

public:
	UPROPERTY()
	TWeakObjectPtr<AActor> Floor;

	UPROPERTY()
	TWeakObjectPtr<AActor> Object;

	UPROPERTY()
	TWeakObjectPtr<class UMS_PropSpaceComponent> PropSpaceComponent;
};

USTRUCT()
struct FMS_GridDataForPropSpace
{
	GENERATED_BODY()

public:
	FMS_GridDataForPropSpace()
		: PropSpaceComponent(nullptr)
	{
		GridDatas.Empty();
	}
	
	class UMS_PropSpaceComponent* PropSpaceComponent;
	TArray<const FMS_GridData*> GridDatas;
};