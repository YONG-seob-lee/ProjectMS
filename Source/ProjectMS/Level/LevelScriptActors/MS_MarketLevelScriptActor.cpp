// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_MarketLevelScriptActor.h"

#include "MS_Define.h"
#include "Manager_Client/MS_ItemManager.h"
#include "Manager_Client/MS_SceneManager.h"
#include "Manager_Client/MS_ScheduleManager.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "ScriptActorComponent/MS_UnitChattingCollectComponent.h"
#include "ScriptActorComponent/MS_UnitPurchaseCollectComponent.h"
#include "Widget/Market/Modal/MS_MarketStartModal.h"


AMS_MarketLevelScriptActor::AMS_MarketLevelScriptActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMS_MarketLevelScriptActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMS_MarketLevelScriptActor::GetUnitsHandle(TMap<MS_Handle, bool>& aUnitsHandle) const
{
	if(ChattingCollectComponent)
	{
		ChattingCollectComponent->GetUnitsHandle(aUnitsHandle);
	}
}

int32 AMS_MarketLevelScriptActor::GetComeInMarketPeoplePerDay() const
{
	TMap<MS_Handle, bool> UnitsHandle;
	UnitsHandle.Empty();
	GetUnitsHandle(UnitsHandle);

	return UnitsHandle.Num();
}

void AMS_MarketLevelScriptActor::GetUnitComeMarketData(MS_Handle aUnitHandle, int32& ComeInMinute, int32& ComeOutMinute) const
{
	TArray<FMS_ChattingParameter> Parameters;
	GetUnitChatting(aUnitHandle, Parameters);

	if(Parameters.IsValidIndex(0))
	{
		ComeInMinute = Parameters[0].Minute;

		if(Parameters.Last().bIsInMarket == false)
		{
			ComeOutMinute = Parameters.Last().Minute;
		}
	}
}

void AMS_MarketLevelScriptActor::GetUnitChatting(MS_Handle aUnitHandle, TArray<FMS_ChattingParameter>& aParameters) const
{
	if(ChattingCollectComponent)
	{
		aParameters.Empty();
		ChattingCollectComponent->GetUnitChatting(aUnitHandle, aParameters);
	}
}

void AMS_MarketLevelScriptActor::GetAllChattingCollection(TArray<FMS_ChattingParameter>& aChattingCollection) const
{
	if(ChattingCollectComponent)
	{
		aChattingCollection.Empty();
		ChattingCollectComponent->GetAllChatting(aChattingCollection);
	}
}

void AMS_MarketLevelScriptActor::GetUnitPurchase(MS_Handle aUnitHandle, TArray<FMS_PurchaseParameter>& aParameters) const
{
	if(PurchaseCollectComponent)
	{
		aParameters.Empty();
		PurchaseCollectComponent->GetUnitPurchase(aUnitHandle, aParameters);
	}
}

void AMS_MarketLevelScriptActor::GetAllPurchaseCollection(TMap<int32, int32>& aPurchaseCollection) const
{
	if(PurchaseCollectComponent)
	{
		aPurchaseCollection.Empty();
		PurchaseCollectComponent->GetAllUnitPurchase(aPurchaseCollection);
	}
}

void AMS_MarketLevelScriptActor::BeginPlay()
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

	ChattingCollectComponent = MS_NewObject<UMS_UnitChattingCollectComponent>(this);
	if(ChattingCollectComponent)
	{
		ChattingCollectComponent->Initialize();
	}
	PurchaseCollectComponent = MS_NewObject<UMS_UnitPurchaseCollectComponent>(this);
	if(PurchaseCollectComponent)
	{
		PurchaseCollectComponent->Initialize();
	}
}

void AMS_MarketLevelScriptActor::Destroyed()
{
	if(ChattingCollectComponent)
	{
		ChattingCollectComponent->Finalize();
		MS_DeleteObject(ChattingCollectComponent);
	}
	if(PurchaseCollectComponent)
	{
		PurchaseCollectComponent->Finalize();
		MS_DeleteObject(PurchaseCollectComponent);
	}
	Super::Destroyed();
}

