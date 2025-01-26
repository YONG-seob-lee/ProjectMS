#include "MS_LevelPropDatas.h"

#include "MS_Define.h"


const FVector FMS_GridData::GetGridLocation() const
{
	if (OwnerZone == nullptr)
	{
		MS_LOG_VERBOSITY(Error, TEXT("[%s] OwnerZone is null"), *MS_FUNC_STRING);

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
		MS_LOG_VERBOSITY(Error, TEXT("[%s] OwnerZone is null"), *MS_FUNC_STRING);

		return FVector(MS_GridSize.X * static_cast<float>(GridPosition.X) + MS_GridSize.X / 2.f
			, MS_GridSize.Y * static_cast<float>(GridPosition.Y) + MS_GridSize.Y / 2.f
			, 0.f);
	}
	
	return FVector(MS_GridSize.X * static_cast<float>(GridPosition.X) + MS_GridSize.X / 2.f
		, MS_GridSize.Y * static_cast<float>(GridPosition.Y) + MS_GridSize.Y / 2.f
		, OwnerZone->GetActorLocation().Z);
}

FIntVector2 FMS_GridData::ConvertLocationToGridPosition(const FVector& aLocation)
{
	// Location이 Grid의 중간 값이라면 나머지 연산에 의해 자동으로 나머지 값 삭제
	
	return  FIntVector2(
	FMath::RoundToInt32(aLocation.X) / MS_GridSizeInt.X,
	FMath::RoundToInt32(aLocation.Y) / MS_GridSizeInt.Y);
}
