// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_PlayerData.h"

UMS_PlayerData::UMS_PlayerData()
{
	bInitDefaultData = false;
	GameDate = FMS_GameDate();
	OpenedZoneIds.Empty();
	MarketFurnitureDatas.Empty();
	Items.Empty();
	StaffDatas.Empty();
	Diary.Empty();
}
