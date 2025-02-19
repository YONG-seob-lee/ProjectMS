#include "MS_MathUtility.h"

EMS_Rotation UMS_MathUtility::ConvertRotation(float aValue)
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

float UMS_MathUtility::ConvertRotation(EMS_Rotation aEnum)
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

EMS_Rotation UMS_MathUtility::RotateClockwise(EMS_Rotation aRotation)
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

FVector UMS_MathUtility::ConvertDirectionToVector(EMS_Direction aDirection)
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

EMS_Rotation UMS_MathUtility::ConvertDirectionToRotation(EMS_Direction aDirection)
{
	switch (aDirection)
	{
	case EMS_Direction::Front :
		return EMS_Rotation::Rot0;
	case EMS_Direction::Back :
		return EMS_Rotation::Rot180;
	case EMS_Direction::Right :
		return EMS_Rotation::Rot90;
	case EMS_Direction::Left :
		return EMS_Rotation::Rot270;
	}

	MS_ENSURE(false);
	return EMS_Rotation::Rot0;
}

FRotator UMS_MathUtility::ConvertDirectionToRotator(EMS_Direction aDirection)
{
	EMS_Rotation Rotation = UMS_MathUtility::ConvertDirectionToRotation(aDirection);
	return FRotator(0.f, UMS_MathUtility::ConvertRotation(Rotation), 0.f);
}

EMS_Direction UMS_MathUtility::GetDirection(FVector2D LocationXY, FVector2D NextLocationXY)
{
	float DiffX = NextLocationXY.X - LocationXY.X;
	float DiffY = NextLocationXY.Y - LocationXY.Y;

	if (FMath::IsNearlyEqual(DiffX, 0.f) && FMath::IsNearlyEqual(DiffY, 0.f))
	{
		return EMS_Direction::None;
	}
	
	if (FMath::Abs(DiffX) < FMath::Abs(DiffY))
	{
		if (DiffY < 0.f)
		{
			return EMS_Direction::Front;
		}
		else
		{
			return EMS_Direction::Back;
		}
	}
	else
	{
		if (DiffX < 0.f)
		{
			return EMS_Direction::Left;
		}
		else
		{
			return EMS_Direction::Right;
		}
	}
}

bool UMS_MathUtility::IsRotationClockwise(float aYaw, float aTargetYaw)
{
	if (aYaw < 0.f)
	{
		aYaw += 360.f;
	}

	if (aTargetYaw < 0.f)
	{
		aTargetYaw += 360.f;
	}
	
	if (aTargetYaw > aYaw)
	{
		if (aTargetYaw - aYaw > 180.f)
		{
			return false;
		}

		return true;
	}
	else
	{
		if (aYaw - aTargetYaw > 180.f)
		{
			return true;
		}

		return false;
	}
}