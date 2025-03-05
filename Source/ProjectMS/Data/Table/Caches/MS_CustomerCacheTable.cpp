// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_CustomerCacheTable.h"

#include "MS_ItemCacheTable.h"
#include "Manager_Client/MS_ItemManager.h"

FMS_CustomerData::FMS_CustomerData(const FString& aCustomerName, int32 aDuckColor, int32 aCharacterBPPathFile, int32 aMaxItemKind, int32 aMaxItemCount)
{
	CustomerName = aCustomerName;
	DuckColor = aDuckColor;
	CharacterBPPathFile = aCharacterBPPathFile;

	TArray<int32> MarketItemIds;
	gItemMng.GetMarketItemKeys(MarketItemIds);

	// 일단 Display에 위치한 아이템만으로 구성하자. (너무 확률적으로 안됨)
	TMap<int32, int32> DisplayItemIds;
	gItemMng.GetStorageItems(EMS_ZoneType::Display, DisplayItemIds);

	DisplayItemIds.GenerateKeyArray(MarketItemIds);
	for(int32 i = 0 ; i < FMath::RandRange(1, aMaxItemKind) ; i++)
	{
		const int32 RandomIndex = FMath::RandRange(0, MarketItemIds.Num() - 1);
		WannaBuyItems.Emplace(MarketItemIds[RandomIndex], FMath::RandRange(1, aMaxItemCount));
	}
}

bool FMS_CustomerData::IsPickUpAllItems()
{
	for(const auto WannaBuyItem : WannaBuyItems)
	{
		if(const int32* PickUpItemCount = PickUpItems.Find(WannaBuyItem.Key))
		{
			// AITest
			continue;
			
			// 실제로 모두 구하면
			if(*PickUpItemCount < WannaBuyItem.Value)
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}

	return true;
}

void FMS_CustomerData::GetRemainItems(TMap<int32, int32>& RemainItems)
{
	RemainItems.Empty();
	
	for(const auto PurchaseItem : WannaBuyItems)
	{
		if(const int32* CollectItemCount = PickUpItems.Find(PurchaseItem.Key))
		{
			if(*CollectItemCount < PurchaseItem.Value)
			{
				RemainItems.Emplace(PurchaseItem.Key, PurchaseItem.Value - *CollectItemCount);
			}
		}
		else
		{
			RemainItems.Emplace(PurchaseItem.Key, PurchaseItem.Value);
		}
	}
}

void FMS_CustomerData::PickUpItem(int32 _PickUpItemTableId, int32 _PickUpItemCount)
{
	if(const int32* WannaItemCount = WannaBuyItems.Find(_PickUpItemTableId))
	{
		int32& BeforePickUpItemCount = PickUpItems.FindOrAdd(_PickUpItemTableId);
		if(*WannaItemCount < BeforePickUpItemCount + _PickUpItemCount)
		{
			MS_ENSURE(false);
			MS_LOG_VERBOSITY(Error, TEXT("[%s] I bought more than I wanted. Something Is Wrong."), *MS_FUNC_STRING);
		}
		BeforePickUpItemCount += _PickUpItemCount;
	}
	else
	{
		MS_ENSURE(false);
		MS_LOG_VERBOSITY(Error, TEXT("[%s] Wrong Wanna To Buy Items Data. Please Check CustomerSupervisor Class."), *MS_FUNC_STRING);
	}
}

void UMS_CustomerCacheTable::Initialize(TObjectPtr<UMS_TableManager> aMng)
{
	Super::Initialize(aMng);
	BuildTable(aMng, EMS_TableDataType::Customer, CustomerDatas);

	CustomerFirstName.Emplace(TEXT("하찮은 "));
	CustomerFirstName.Emplace(TEXT("호기심많은 "));
	CustomerFirstName.Emplace(TEXT("배고픈 "));
	CustomerFirstName.Emplace(TEXT("광기의 "));
	CustomerFirstName.Emplace(TEXT("행복한 "));
	CustomerFirstName.Emplace(TEXT("심심한 "));
	CustomerFirstName.Emplace(TEXT("조급한 "));
	CustomerFirstName.Emplace(TEXT("얼떨떨한 "));
	CustomerFirstName.Emplace(TEXT("잔망 "));
	CustomerFirstName.Emplace(TEXT("돈이두둑한 "));
	CustomerFirstName.Emplace(TEXT("옹졸한 "));
	
	CustomerLastName.Emplace(TEXT("오리"));
	CustomerLastName.Emplace(TEXT("오오리"));
	CustomerLastName.Emplace(TEXT("요리"));
	CustomerLastName.Emplace(TEXT("호리"));
	CustomerLastName.Emplace(TEXT("뽀리"));
	CustomerLastName.Emplace(TEXT("타다끼"));
	CustomerLastName.Emplace(TEXT("거위"));
	CustomerLastName.Emplace(TEXT("공작"));
	CustomerLastName.Emplace(TEXT("백조"));
	CustomerLastName.Emplace(TEXT("참새"));
}

void UMS_CustomerCacheTable::Finalize()
{
	Super::Finalize();
}

void UMS_CustomerCacheTable::MakeNewCustomerData(FMS_CustomerData& NewCustomerData)
{
	if(FMS_Customer** Customer = CustomerDatas.Find(FMath::RandRange(1, CustomerDatas.Num())))
	{
		FString ResultName = FString();
		const int32 RandomFirstName = FMath::RandRange(0, CustomerFirstName.Num() - 1);
		if(CustomerFirstName.IsValidIndex(RandomFirstName))
		{
			ResultName += CustomerFirstName[RandomFirstName];
		}

		const int32 RandomLastName = FMath::RandRange(0, CustomerLastName.Num() - 1);
		if(CustomerLastName.IsValidIndex(RandomLastName))
		{
			ResultName += CustomerLastName[RandomLastName];
		}
		
		NewCustomerData = FMS_CustomerData(ResultName, (*Customer)->ColorType, (*Customer)->PathFile, (*Customer)->MaxItemKind, (*Customer)->MaxItemCount);
	}
}
