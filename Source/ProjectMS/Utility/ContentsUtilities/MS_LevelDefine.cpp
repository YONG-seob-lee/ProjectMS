#include "MS_LevelDefine.h"

#include "MS_Define.h"


const FVector FMS_GridData::GetGridLocation() const
{
	FVector2D GridPositionXY = ConvertGridPositionToLocation(GridPosition, false, false);
	
	if (OwnerZone == nullptr)
	{
		MS_ERROR(TEXT("[%s] OwnerZone is null"), *MS_FUNC_STRING);
		return FVector(GridPositionXY.X, GridPositionXY.Y,0.f);
	}

	return FVector(GridPositionXY.X, GridPositionXY.Y,OwnerZone->GetActorLocation().Z);
}

const FVector FMS_GridData::GetGridCenterLocation() const
{
	FVector2D GridPositionXY = ConvertGridPositionToLocation(GridPosition, true, true);
	
	if (OwnerZone == nullptr)
	{
		MS_ERROR(TEXT("[%s] OwnerZone is null"), *MS_FUNC_STRING);
		return FVector(GridPositionXY.X, GridPositionXY.Y,0.f);
	}

	return FVector(GridPositionXY.X, GridPositionXY.Y,OwnerZone->GetActorLocation().Z);
}

FIntVector2 FMS_GridData::ConvertLocationToGridPosition(const FVector& aLocation)
{
	int32 GridPositionX = FMath::RoundToInt32(aLocation.X) / MS_GridSizeInt.X;
	
	if (aLocation.X < 0)
	{
		if (FMath::RoundToInt32(aLocation.X) % MS_GridSizeInt.X != 0)
		{
			--GridPositionX;
		}
	}

	int32 GridPositionY = FMath::RoundToInt32(aLocation.Y) / MS_GridSizeInt.Y;
	
	if (aLocation.Y < 0)
	{
		if (FMath::RoundToInt32(aLocation.Y) % MS_GridSizeInt.Y != 0)
		{
			--GridPositionY;
		}
	}
	
	return  FIntVector2(GridPositionX, GridPositionY);
}

FVector2D FMS_GridData::ConvertGridPositionToLocation(const FIntVector2& aGridPosition,
	bool aIsXGridCenter /*= false*/, bool aIsYGridCenter /*= false*/)
{
	float LocationX = aIsXGridCenter ? MS_GridSize.X * static_cast<float>(aGridPosition.X) + MS_GridSize.X / 2.f
	: MS_GridSize.X * static_cast<float>(aGridPosition.X);

	float LocationY = aIsYGridCenter ? MS_GridSize.Y * static_cast<float>(aGridPosition.Y) + MS_GridSize.Y / 2.f
	: MS_GridSize.Y * static_cast<float>(aGridPosition.Y);

	return FVector2D(LocationX, LocationY);
}