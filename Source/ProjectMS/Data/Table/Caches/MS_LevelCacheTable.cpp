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
		LevelDatas.Emplace(LevelData.Value->LevelName, LevelData.Value);
	}
}

void UMS_LevelCacheTable::Finalize()
{
	Super::Finalize();
}

FName UMS_LevelCacheTable::GetLevelName(EMS_LevelType LevelType)
{
	return FName();
}
