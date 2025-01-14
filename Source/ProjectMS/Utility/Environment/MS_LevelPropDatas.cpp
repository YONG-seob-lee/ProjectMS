#include "MS_LevelPropDatas.h"

#include "MS_Define.h"


const FVector FMS_GridData::GetGridWorldLocation() const
{
	if (OwnerZone == nullptr)
	{
		MS_LOG_Verbosity(Error, TEXT("[%s] OwnerZone is null"), *MS_FUNC_STRING);

		return FVector(MS_GridSize.X * static_cast<float>(WorldGridPosition.X)
			, MS_GridSize.Y * static_cast<float>(WorldGridPosition.Y)
			, 0.f);
	}
		
	return FVector(MS_GridSize.X * static_cast<float>(WorldGridPosition.X)
		, MS_GridSize.Y * static_cast<float>(WorldGridPosition.Y)
		, OwnerZone->GetActorLocation().Z);
}

const FVector FMS_GridData::GetGridWorldCenterLocation() const
{
	if (OwnerZone == nullptr)
	{
		MS_LOG_Verbosity(Error, TEXT("[%s] OwnerZone is null"), *MS_FUNC_STRING);

		return FVector(MS_GridSize.X * static_cast<float>(WorldGridPosition.X) + MS_GridSize.X / 2.f
			, MS_GridSize.Y * static_cast<float>(WorldGridPosition.Y) + MS_GridSize.Y / 2.f
			, 0.f);
	}
	
	return FVector(MS_GridSize.X * static_cast<float>(WorldGridPosition.X) + MS_GridSize.X / 2.f
		, MS_GridSize.Y * static_cast<float>(WorldGridPosition.Y) + MS_GridSize.Y / 2.f
		, OwnerZone->GetActorLocation().Z);
}
