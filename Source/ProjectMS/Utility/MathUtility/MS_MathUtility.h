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
	
	static EMS_Rotation ConvertRotation(float aValue)
	{
		if (FMath::IsNearlyEqual(aValue, 0.f))
		{
			return EMS_Rotation::Rot0;
		}
		if (FMath::IsNearlyEqual(aValue, 90.f) || FMath::IsNearlyEqual(aValue, -270.f))
		{
			return EMS_Rotation::Rot90;
		}
		if (FMath::IsNearlyEqual(aValue, 180.f) || FMath::IsNearlyEqual(aValue, -180.f))
		{
			return EMS_Rotation::Rot180;
		}
		if (FMath::IsNearlyEqual(aValue, 270.f) || FMath::IsNearlyEqual(aValue, -90.f))
		{
			return EMS_Rotation::Rot270;
		}
	
		MS_ENSURE(false);
		return EMS_Rotation::Rot0;
	}
	
	static float ConvertRotation(EMS_Rotation aEnum)
	{
		switch (aEnum)
		{
		case EMS_Rotation::Rot0 :
			return 0.f;
		case EMS_Rotation::Rot90 :
			return 90.f;
		case EMS_Rotation::Rot180 :
			return 180.f;
		case EMS_Rotation::Rot270 :
			return 270.f;
		}

		MS_ENSURE(false);
		return 0.f;
	}

	static EMS_Rotation RotateClockwise(EMS_Rotation aRotation)
	{
		switch (aRotation)
		{
		case EMS_Rotation::Rot0 :
			return EMS_Rotation::Rot90;
		case EMS_Rotation::Rot90 :
			return EMS_Rotation::Rot180;
		case EMS_Rotation::Rot180 :
			return EMS_Rotation::Rot270;
		case EMS_Rotation::Rot270 :
			return EMS_Rotation::Rot0;
		}

		MS_ENSURE(false);
		return EMS_Rotation::Rot0;
	}

	static FVector ConvertDirectionToVector(EMS_Direction aDirection)
	{
		switch (aDirection)
		{
		case EMS_Direction::Front :
			return FVector(0.f, -1.f, 0.f);
		case EMS_Direction::Back :
			return FVector(0.f, 1.f, 0.f);
		case EMS_Direction::Right :
			return FVector(1.f, 0.f, 0.f);
		case EMS_Direction::Left :
			return FVector(-1.f, 0.f, 0.f);
		}

		MS_ENSURE(false);
		return FVector::ZeroVector;
	}
	
	static EMS_Rotation ConvertDirectionToRotation(EMS_Direction aDirection)
	{
		switch (aDirection)
		{
		case EMS_Direction::Front :
			return EMS_Rotation::Rot0;
		case EMS_Direction::Back :
			return EMS_Rotation::Rot90;
		case EMS_Direction::Right :
			return EMS_Rotation::Rot180;
		case EMS_Direction::Left :
			return EMS_Rotation::Rot270;
		}

		MS_ENSURE(false);
		return EMS_Rotation::Rot0;
	}

	static FRotator ConvertDirectionToRotator(EMS_Direction aDirection)
	{
		EMS_Rotation Rotation = UMS_MathUtility::ConvertDirectionToRotation(aDirection);
		return FRotator(0.f, UMS_MathUtility::ConvertRotation(Rotation), 0.f);
	}
};