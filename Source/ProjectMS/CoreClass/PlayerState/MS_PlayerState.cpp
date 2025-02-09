// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_PlayerState.h"

#include "MS_Define.h"
#include "Kismet/GameplayStatics.h"
#include "Test/TestServer/MS_TestDB.h"

AMS_PlayerState::AMS_PlayerState()
{
	SaveSlotName = FString("TestDB");
	
	InitPlayerData();
}

const TArray<int32>& AMS_PlayerState::GetOpenedZoneIds()
{
	return OpenedZoneIds;
}

void AMS_PlayerState::AddOpenedZoneId(int32 aZoneId)
{
	OpenedZoneIds.AddUnique(aZoneId);
	SavePlayerData();
}

void AMS_PlayerState::InitDefaultPlayerData()
{
	OpenedZoneIds.AddUnique(1);
	OpenedZoneIds.AddUnique(10);
}

void AMS_PlayerState::InitPlayerData()
{
	UMS_TestDB* TestDB = Cast<UMS_TestDB>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));
	if (TestDB == nullptr)
	{
		TestDB = GetMutableDefault<UMS_TestDB>();
	}

	bInitDefaultData = TestDB->bInitDefaultData;
	OpenedZoneIds = TestDB->OpenedZoneIds;

	if (!bInitDefaultData)
	{
		InitDefaultPlayerData();
	}
	
	SavePlayerData();
}

void AMS_PlayerState::SavePlayerData()
{
	UMS_TestDB* NewTestDBData = NewObject<UMS_TestDB>();
	
	NewTestDBData->OpenedZoneIds = OpenedZoneIds;
	
	if (!UGameplayStatics::SaveGameToSlot(NewTestDBData, SaveSlotName, 0))
	{
		MS_LOG_VERBOSITY(Error, TEXT("SaveGameError"));
		MS_ENSURE(false);
	}
}
