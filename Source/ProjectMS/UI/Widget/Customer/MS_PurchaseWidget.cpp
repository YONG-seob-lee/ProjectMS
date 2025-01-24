// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_PurchaseWidget.h"

#include "Components/TextBlock.h"
#include "LevelScriptActors/MS_MarketLevelScriptActor.h"
#include "Manager_Client/MS_SceneManager.h"
#include "Table/Caches/MS_ItemCacheTable.h"
#include "Table/Caches/MS_ResourceUnitCacheTable.h"
#include "Widget/WidgetComponent/MS_WidgetSwitcher.h"

namespace Time
{
	constexpr int32 MinutePerOneHour = 60; 
}

void UMS_PurchaseWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMS_PurchaseWidget::SetPurchase(MS_Handle aUnitHandle, EMS_PopulationNumber aPopulationNumber) const
{
	CPP_PurchaseWidgetSwitcher->SetActiveWidgetIndex(static_cast<int32>(aPopulationNumber));
	
	if(aPopulationNumber == EMS_PopulationNumber::One)
	{
		SetPurchaseOne_Internal(aUnitHandle);
		
	}
	else if(aPopulationNumber == EMS_PopulationNumber::Many)
	{
		SetPurchaseMany_Internal();
	}
}

void UMS_PurchaseWidget::SetPurchaseOne_Internal(MS_Handle aUnitHandle) const
{
	if(const TObjectPtr<AMS_MarketLevelScriptActor> MarketLevelScriptActor = Cast<AMS_MarketLevelScriptActor>(gSceneMng.GetCurrentLevelScriptActor()))
	{
		int32 ComeInMinute = 0;
		int32 ComeOutMinute = 0;
		MarketLevelScriptActor->GetUnitComeMarketData(aUnitHandle, ComeInMinute, ComeOutMinute);

		const TObjectPtr<UMS_ResourceUnitCacheTable> UnitTable = Cast<UMS_ResourceUnitCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::ResourceUnit));
		MS_Ensure(UnitTable);
		
		CPP_ComeInMarketText->SetText(FText::FromString(FString::Format(TEXT("   들어온 시각 : {0}시 {1}분"), {ComeInMinute / Time::MinutePerOneHour, ComeInMinute % Time::MinutePerOneHour})));
		if(aUnitHandle == INDEX_NONE)
		{
			CPP_ComeOutMarketText->SetText(FText::FromString(TEXT("   나간 시각 : 0시 0분")));
		}
		else
		{
			if(ComeOutMinute == 0)
			{
				CPP_ComeOutMarketText->SetText(FText::FromString(TEXT("   나간 시각 : \"매장 내에 있습니다!\"")));
			}
			else
			{
				CPP_ComeOutMarketText->SetText(FText::FromString(FString::Format(TEXT("   나간 시각 : {0}시 {1}분"), {ComeOutMinute / Time::MinutePerOneHour, ComeOutMinute % Time::MinutePerOneHour})));
			}	
		}
			
		TArray<FMS_PurchaseParameter> Parameters;
		MarketLevelScriptActor->GetUnitPurchase(aUnitHandle, Parameters);

		FString ItemListString = TEXT("");
		int32 TotalItemCount = 0;
		int32 TotalItemGoldAmount = 0;
		const TObjectPtr<UMS_ItemCacheTable> ItemTable = Cast<UMS_ItemCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::ItemData));
		MS_Ensure(ItemTable);

		for(const auto& Parameter : Parameters)
		{
			if(const FMS_ItemData* ItemData = ItemTable->GetItem(Parameter.ItemId))
			{
				ItemListString.Append(TEXT("\'") + ItemData->ItemName.ToString() + TEXT("\'") + TEXT(", "));
				TotalItemGoldAmount += ItemData->PriceMin * Parameter.ItemCount;
			}
			TotalItemCount += Parameter.ItemCount;
		}
		
		ItemListString = ItemListString.Reverse();
		for(int32 i = 0 ; i < 2 ; i++)
		{
			if(ItemListString.IsValidIndex(0))
			{
				ItemListString.RemoveAt(0);
			}	
		}
		ItemListString = ItemListString.Reverse();
			
		CPP_PurchaseItemsList->SetText(FText::FromString(FString::Format(TEXT("   구매한 물건 목록 : {0}"), {ItemListString})));
		CPP_PurchaseItemCount->SetText(FText::FromString(FString::Format(TEXT("   구매한 물건 갯수 : {0}"), { TotalItemCount })));
		CPP_PurchaseItemsGoldAmount->SetText(FText::FromString(FString::Format(TEXT("   구매 총 금액 : {0}"), { TotalItemGoldAmount})));
	}
}

void UMS_PurchaseWidget::SetPurchaseMany_Internal() const
{
	if(const TObjectPtr<AMS_MarketLevelScriptActor> MarketLevelScriptActor = Cast<AMS_MarketLevelScriptActor>(gSceneMng.GetCurrentLevelScriptActor()))
	{
		const int32 ComeInMarketPeoplePerDay = MarketLevelScriptActor->GetComeInMarketPeoplePerDay();
		CPP_ComeInMarketPeoplePerDay->SetText(FText::FromString(FString::Format(TEXT("   일일 총 방문 오리 수 : {0}"), {ComeInMarketPeoplePerDay})));
		
		TMap<int32, int32> PurchaseCollection;
		MarketLevelScriptActor->GetAllPurchaseCollection(PurchaseCollection);

		int32 TotalBuyItemCount = 0;
		int32 TotalBuyGoldAmount = 0;
		const TObjectPtr<UMS_ItemCacheTable> ItemTable = Cast<UMS_ItemCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::ItemData));
		MS_Ensure(ItemTable);
		
		for(const auto& PurchaseData : PurchaseCollection)
		{
			TotalBuyItemCount += PurchaseData.Value;

			if(const FMS_ItemData* ItemData = ItemTable->GetItem(PurchaseData.Key))
			{
				TotalBuyGoldAmount += PurchaseData.Value * ItemData->PriceMin;
			}
		}

		CPP_TotalBuyItemCount->SetText(FText::FromString(FString::Format(TEXT("   총 구매 아이템 갯수 : {0}"), {TotalBuyItemCount})));
		CPP_TotalBuyGoldAmount->SetText(FText::FromString(FString::Format(TEXT("   총 구매한 금액 : {0}"), {TotalBuyGoldAmount})));
	}
}
