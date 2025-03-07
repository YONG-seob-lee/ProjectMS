

#pragma once

#include "CoreMinimal.h"
#include "MS_ItemDefine.h"
#include "MathUtility/MS_MathUtility.h"
#include "MS_LevelDefine.generated.h"


#define MS_GridSize FVector(50.f, 50.f, 50.f)
#define MS_GridSizeInt FIntVector(50, 50, 50)

UENUM(BlueprintType)
enum class EMS_ZoneType : uint8
{
	None = 0,
	Display = 1,
	Shelf = 2,
	Pallet = 3,
	Outside = 4,

	Passage = 100,
};

UENUM(BlueprintType)
enum class EMS_PropType : uint8
{
	None = 0,
	Furniture = 1,
	Structure = 2,
	Gate = 3,
};

UENUM(BlueprintType)
enum class EMS_FurnitureType : uint8
{
	None = 0,
	Counter = 1,
	Storage = 2,
};

UENUM(BlueprintType)
enum class EMS_PropSpaceType : uint8
{
	None = 0,
	
	ShapeSpace = 1,
	FreeSpace = 2,
	StaffSpace = 3,
	
	PurposefulCustomerOnly = 4,
	PurposefulStaffOnly = 5,
	PurposefulCustomerAndStaffOnly = 6,
};

UENUM(BlueprintType)
enum class EMS_PurposeType : uint8
{
	None = 0,

	Cashier = 1,
	BeforePayment = 2,
	AfterPayment = 3,

	UseStorage = 4,
	
	UseGate = 5,
	UseWardrobe = 6,
	
	Any = 100,	// != None
};

UENUM(BlueprintType)
enum class EMS_FloorState : uint8
{
	Normal = 0,
	Unconstructable = 1,
	Selected = 2,
	SelectedUnconstructable = 3,
};

// GridDatas
USTRUCT()
struct FMS_GridData
{
	GENERATED_BODY()

public:
	FMS_GridData()
	: GridPosition(FIntVector2::ZeroValue), FloorMeshId(INDEX_NONE)
	{
	}

	FMS_GridData(TWeakObjectPtr<AActor> aOwnerZone, FIntVector2 aWorldGridPosition)
		: OwnerZone(aOwnerZone), GridPosition(aWorldGridPosition), FloorMeshId(INDEX_NONE)
	{
	}
	
	virtual ~FMS_GridData()
	{
	}

	TWeakObjectPtr<AActor> GetOwnerZone() const { return OwnerZone; }
	const FIntVector2& GetGridPosition() const { return GridPosition; }

	const FVector GetGridLocation() const;
	const FVector GetGridCenterLocation() const;

	static FIntVector2 ConvertLocationToGridPosition(const FVector& aLocation);
	static FVector2D ConvertGridPositionToLocation(const FIntVector2& aGridPosition, bool aIsXGridCenter = false, bool aIsYGridCenter = false);

	
private:
	UPROPERTY()
	TWeakObjectPtr<AActor> OwnerZone;

	UPROPERTY()
	FIntVector2 GridPosition;

public:
	UPROPERTY()
	int32 FloorMeshId;

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

	UPROPERTY()
	class UMS_PropSpaceComponent* PropSpaceComponent;
	
	TArray<const FMS_GridData*> GridDatas;
};

USTRUCT()
struct FMS_WallData
{
	GENERATED_BODY()

public:
	FMS_WallData()
		: Location(FVector::ZeroVector), Rotator(FRotator::ZeroRotator), WallMeshId(INDEX_NONE)
	{
	}
	
	FMS_WallData(const FVector& aLocation, const FRotator& aRotation)
		: Location(aLocation), Rotator(aRotation), WallMeshId(INDEX_NONE)
	{
	}
	
	UPROPERTY()
	FVector Location;

	UPROPERTY()
	FRotator Rotator;
	
	UPROPERTY()
	int32 WallMeshId;
};

USTRUCT()
struct FMS_FurniturePositionData
{
	GENERATED_BODY()

public:
	FMS_FurniturePositionData()
	{
	}

	FMS_FurniturePositionData(int32 aFurnitureTableId, const FIntVector2& aGridPosition,
	EMS_Rotation aRotation)
		: FurnitureTableId(aFurnitureTableId), GridPosition(aGridPosition), Rotation(aRotation)
	{
		SlotDatas.Empty();
	}

	FMS_FurniturePositionData(int32 aFurnitureTableId, const FIntVector2& aGridPosition,
	EMS_Rotation aRotation, const TArray<FMS_SlotData>& aSlotDatas)
	: FurnitureTableId(aFurnitureTableId), GridPosition(aGridPosition), Rotation(aRotation),
	SlotDatas(aSlotDatas)
	{
	}
	
	UPROPERTY()
	int32 FurnitureTableId = 0;

	UPROPERTY()
	FIntVector2 GridPosition = FIntVector2::NoneValue;
	
	UPROPERTY()
	EMS_Rotation Rotation = EMS_Rotation::Rot0;

	UPROPERTY()
	TArray<FMS_SlotData> SlotDatas = {};
};

namespace LevelSpecificActorName
{
	const FName UglyDuck = TEXT("UglyDuck");
}

namespace FurnitureUnitMap
{
	const TMap<EMS_FurnitureType, EMS_UnitType> FurnitureUnitTypeMap =
		{{EMS_FurnitureType::Counter, EMS_UnitType::Counter}
		, {EMS_FurnitureType::Storage, EMS_UnitType::Storage}};
}