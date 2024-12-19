// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_InMarketLevelScriptActor.h"

#include "Manager_Both/MS_InventoryManager.h"

AMS_InMarketLevelScriptActor::AMS_InMarketLevelScriptActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMS_InMarketLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();

	// 패킷으로 데이터를 받음
	
	TMap<int32, FPacketItemDatas*> Items;
	gInvenMng.CreateItem(Items);
}

void AMS_InMarketLevelScriptActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

