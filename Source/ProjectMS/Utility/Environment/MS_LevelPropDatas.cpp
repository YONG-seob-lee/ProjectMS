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