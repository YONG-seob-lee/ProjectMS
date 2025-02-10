// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Save/MS_SaveData.h"
#include "MS_TestDB.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_TestDB : public USaveGame
{
	GENERATED_BODY()

public:
	UMS_TestDB();

	UPROPERTY()
	bool bInitDefaultData;
	
	UPROPERTY()
	TArray<int32> OpenedZoneIds;

	UPROPERTY()
	TArray<FMS_LevelFurnitureSaveData> MarketFurnitureDatas;
};
