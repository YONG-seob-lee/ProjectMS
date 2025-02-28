// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_MarketLevelScriptActor.h"

#include "MS_Define.h"
#include "Controller/MS_PlayerController.h"
#include "Manager_Client/MS_ItemManager.h"
#include "Manager_Client/MS_SceneManager.h"
#include "Manager_Client/MS_ScheduleManager.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "PlayerState/MS_PlayerState.h"
#include "ScriptActorComponent/MS_UnitBehaviorCollectComponent.h"
#include "ScriptActorComponent/MS_UnitChattingCollectComponent.h"
#include "ScriptActorComponent/MS_UnitPurchaseCollectComponent.h"
#include "Units/MS_StorageUnit.h"
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

void AMS_MarketLevelScriptActor::GetUnitBehavior(MS_Handle aUnitHandle,	TArray<FMS_BehaviorParameter>& aParameters) const
{
	if(BehaviorCollectComponent)
	{
		aParameters.Empty();
		BehaviorCollectComponent->GetUnitBehavior(aUnitHandle, aParameters);
	}
}

void AMS_MarketLevelScriptActor::GetAllBehaviorCollection(TArray<FMS_BehaviorParameter>& aBehaviorCollection) const
{
	if(BehaviorCollectComponent)
	{
		aBehaviorCollection.Empty();
		BehaviorCollectComponent->GetAllBehavior(aBehaviorCollection);
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

#if WITH_EDITOR
void AMS_MarketLevelScriptActor::AddTestAIActorComeInMarket(int32 aUnitId) const
{
	if(PurchaseCollectComponent)
	{
		PurchaseCollectComponent->TestInitialize(aUnitId);
	}
	if(ChattingCollectComponent)
	{
		ChattingCollectComponent->TestInitialize(aUnitId);
	}
}

bool AMS_MarketLevelScriptActor::IsUnitInMarket(int32 aUnitHandle) const
{
	if(ChattingCollectComponent)
	{
		return ChattingCollectComponent->IsUnitInMarket(aUnitHandle);
	}

	return false;
}
#endif

void AMS_MarketLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();
	
	ChattingCollectComponent = MS_NewObject<UMS_UnitChattingCollectComponent>(this);
	if(ChattingCollectComponent)
	{
		ChattingCollectComponent->Initialize();
	}
	BehaviorCollectComponent =MS_NewObject<UMS_UnitBehaviorCollectComponent>(this);
	if(BehaviorCollectComponent)
	{
		BehaviorCollectComponent->Initialize();
	}
	PurchaseCollectComponent = MS_NewObject<UMS_UnitPurchaseCollectComponent>(this);
	if(PurchaseCollectComponent)
	{
		PurchaseCollectComponent->Initialize();
	}

	InitializePlayerDataFurnitures();
}

void AMS_MarketLevelScriptActor::Destroyed()
{
	if(ChattingCollectComponent)
	{
		ChattingCollectComponent->Finalize();
		MS_DeleteObject(ChattingCollectComponent);
	}
	if(BehaviorCollectComponent)
	{
		BehaviorCollectComponent->Finalize();
		MS_DeleteObject(BehaviorCollectComponent);
	}
	if(PurchaseCollectComponent)
	{
		PurchaseCollectComponent->Finalize();
		MS_DeleteObject(PurchaseCollectComponent);
	}
	Super::Destroyed();
}

void AMS_MarketLevelScriptActor::InitializePlayerDataFurnitures()
{
	const TObjectPtr<UWorld> World = GetWorld();
	if (!IsValid(World))
	{
		return;
	}

	const TObjectPtr<AMS_PlayerController> PlayerController = World->GetFirstPlayerController<AMS_PlayerController>();
	if (!IsValid(PlayerController))
	{
		return;
	}

	const TObjectPtr<AMS_PlayerState> PlayerState = PlayerController->GetPlayerState<AMS_PlayerState>();
	if (!IsValid(PlayerState))
	{
		return;
	}

	TMap<FIntVector2, FMS_FurniturePositionData> FurnitureDatas;
	gItemMng.GetAllFurnitureDatas(FurnitureDatas);
	
	for (const auto& It : FurnitureDatas)
	{
		FMS_FurniturePositionData FurnitureData = It.Value;
		
		TWeakObjectPtr<UMS_StorageUnit> NewUnit = CreateProp(EMS_PropType::Furniture, FurnitureData.FurnitureTableId, FurnitureData.GridPosition, FurnitureData.Rotation);
		NewUnit->SetSlotDatas(FurnitureData.SlotDatas);
	}
}