#include "MS_LevelPropDatas.h"

#include "MS_Define.h"


EMS_Rotation MS_RotationFunc::ConvertRotation(float aValue)
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
	
	MS_Ensure(false);
	return EMS_Rotation::Rot0;
}

float MS_RotationFunc::ConvertRotation(EMS_Rotation aEnum)
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

	MS_Ensure(false);
	return 0.f;
}

EMS_Rotation MS_RotationFunc::RotateClockwise(EMS_Rotation aRotation)
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

	MS_Ensure(false);
	return EMS_Rotation::Rot0;
}

const FVector FMS_GridData::GetGridLocation() const
{
	if (OwnerZone == nullptr)
	{
		MS_LOG_Verbosity(Error, TEXT("[%s] OwnerZone is null"), *MS_FUNC_STRING);

		return FVector(MS_GridSize.X * static_cast<float>(GridPosition.X)
			, MS_GridSize.Y * static_cast<float>(GridPosition.Y)
			, 0.f);
	}
		
	return FVector(MS_GridSize.X * static_cast<float>(GridPosition.X)
		, MS_GridSize.Y * static_cast<float>(GridPosition.Y)
		, OwnerZone->GetActorLocation().Z);
}

const FVector FMS_GridData::GetGridCenterLocation() const
{
	if (OwnerZone == nullptr)
	{
		MS_LOG_Verbosity(Error, TEXT("[%s] OwnerZone is null"), *MS_FUNC_STRING);

		return FVector(MS_GridSize.X * static_cast<float>(GridPosition.X) + MS_GridSize.X / 2.f
			, MS_GridSize.Y * static_cast<float>(GridPosition.Y) + MS_GridSize.Y / 2.f
			, 0.f);
	}
	
	return FVector(MS_GridSize.X * static_cast<float>(GridPosition.X) + MS_GridSize.X / 2.f
		, MS_GridSize.Y * static_cast<float>(GridPosition.Y) + MS_GridSize.Y / 2.f
		, OwnerZone->GetActorLocation().Z);
}
