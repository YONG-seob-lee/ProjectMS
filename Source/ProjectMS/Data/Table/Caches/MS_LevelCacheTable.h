﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Table/MS_CacheTable.h"
#include "Data/Table/RowBase/MS_Level.h"
#include "Utility/Command/SceneCommand/MS_SceneCommand.h"
#include "MS_LevelCacheTable.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_LevelCacheTable : public UMS_CacheTable
{
	GENERATED_BODY()
public:
	virtual void Initialize(TObjectPtr<UMS_TableManager> aMng) override;
	virtual void Finalize() override;
	
	FName GetLevelName(EMS_LevelType aLevelType);
	FMS_Level* GetLevelData(EMS_LevelType aLevelType);
	FName GetPrimitiveWidgetName(EMS_LevelType aLevelType);
private:
	TMap<int32, FMS_Level*> LevelDatas; 
};
