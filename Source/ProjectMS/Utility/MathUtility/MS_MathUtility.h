#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MS_Define.h"
#include "MS_MathUtility.generated.h"

UENUM()
enum class EMS_InterpolationType
{
	Undefined,
	EaseIn,
	EaseOut,
	Linear
};

UENUM(BlueprintType)
enum class EMS_Rotation : uint8
{
	Rot0,
	Rot90,
	Rot180,
	Rot270
};

UENUM(BlueprintType)
enum class EMS_Direction : uint8
{
	None,
	Front,
	Back,
	Right,
	Left
};

UCLASS()
class UMS_MathUtility : public UObject
{
	GENERATED_BODY()

public:
	UMS_MathUtility() = default;
	
	static EMS_Rotation ConvertRotation(float aValue);
	
	static float ConvertRotation(EMS_Rotation aEnum);

	static EMS_Rotation RotateClockwise(EMS_Rotation aRotation);

	static FVector ConvertDirectionToVector(EMS_Direction aDirection);
	
	static EMS_Rotation ConvertDirectionToRotation(EMS_Direction aDirection);

	static FRotator ConvertDirectionToRotator(EMS_Direction aDirection);

	static EMS_Direction GetDirection(FVector2D LocationXY, FVector2D NextLocationXY);

	static bool IsRotationClockwise(float aYaw, float aTargetYaw);
};