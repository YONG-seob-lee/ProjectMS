// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_LevelCacheTable.h"

void UMS_LevelCacheTable::Initialize(TObjectPtr<UMS_TableManager> aMng)
{
	Super::Initialize(aMng);
	
	TMap<int32, FMS_Level*> PrimitiveLevel;
	PrimitiveLevel.Empty();
	
	BuildTable(aMng, EMS_TableDataType::Level, PrimitiveLevel);

	for(const auto& LevelData : PrimitiveLevel)
	{
		LevelDatas.Emplace(LevelData.Value->LevelKey, LevelData.Value);
	}
}

void UMS_LevelCacheTable::Finalize()
{
	Super::Finalize();
}

FName UMS_LevelCacheTable::GetLevelName(EMS_LevelType aLevelType)
{
	if(FMS_Level** LevelData = LevelDatas.Find(static_cast<int32>(aLevelType)))
	{
		return (*LevelData)->LevelName;
	}

	return FName();
}

FMS_Level* UMS_LevelCacheTable::GetLevelData(EMS_LevelType aLevelType)
{
	if(FMS_Level** LevelData = LevelDatas.Find(static_cast<int32>(aLevelType)))
	{
		return *LevelData;
	}

	return nullptr;
}

FName UMS_LevelCacheTable::GetPrimitiveWidgetName(EMS_LevelType aLevelType)
{
	if(const FMS_Level* LevelData = GetLevelData(aLevelType))
	{
		return LevelData->PrimitiveWidgetName;
	}

	return FName();
}
