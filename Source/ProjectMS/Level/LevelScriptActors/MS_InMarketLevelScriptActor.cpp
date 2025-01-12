// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_InMarketLevelScriptActor.h"

#include "Manager_Client/MS_ItemManager.h"
#include "Manager_Client/MS_SceneManager.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "Widget/Market/MS_MarketStartModal.h"


AMS_InMarketLevelScriptActor::AMS_InMarketLevelScriptActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMS_InMarketLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();

	// 패킷으로 데이터를 받음
	
	TMap<int32, FPacketItemDatas*> Items;
	gItemMng.CreateItem(Items);

	gSceneMng.OnFadeFinishedEventDelegate.AddWeakLambda(this, [this]
	{
		gWidgetMng.ShowModalWidget(UMS_MarketStartModal::GetWidgetPath(), true, TEXT("PlayModal"));
	});
}

void AMS_InMarketLevelScriptActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

