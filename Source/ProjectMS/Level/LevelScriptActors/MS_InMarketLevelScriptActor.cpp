// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_InMarketLevelScriptActor.h"

#include "Manager_Client/MS_ItemManager.h"
#include "Manager_Client/MS_SceneManager.h"
#include "Manager_Client/MS_ScheduleManager.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "Widget/Market/Modal/MS_MarketStartModal.h"


AMS_InMarketLevelScriptActor::AMS_InMarketLevelScriptActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMS_InMarketLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();

	// 패킷으로 데이터를 받음
	
	TMap<int32, FPacketItemDatas*> Items;

	gSceneMng.OnFadeFinishedEventDelegate.AddWeakLambda(this, [this]
	{
		FMS_ModalParameter ModalParameter;
		ModalParameter.OnCloseWidgetCallback = []()
		{
			gScheduleMng.TransferServer();
		};
		ModalParameter.InModalWidget = gWidgetMng.Create_Widget_NotManaging(UMS_MarketStartModal::GetWidgetPath());
		gWidgetMng.ShowModalWidget(ModalParameter);
	});
}

void AMS_InMarketLevelScriptActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

