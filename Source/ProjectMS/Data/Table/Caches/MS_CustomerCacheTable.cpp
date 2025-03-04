// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_CustomerCacheTable.h"

#include "MS_ItemCacheTable.h"

FMS_CustomerData::FMS_CustomerData(int32 aDuckColor, int32 aCharacterBPPathFile, int32 aMaxItemKind, int32 aMaxItemCount)
{
	DuckColor = aDuckColor;
	CharacterBPPathFile = aCharacterBPPathFile;
	const TObjectPtr<UMS_ItemCacheTable> ItemTable = Cast<UMS_ItemCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::ItemData));
	MS_ENSURE(ItemTable);


	TMap<int32, FMS_ItemData*> ItemDatas = {};
	ItemTable->GetItems(ItemDatas);

	TArray<int32> ItemIds;
	ItemDatas.GenerateKeyArray(ItemIds);
	for(int32 i = 0 ; i < FMath::RandRange(1, aMaxItemKind) ; i++)
	{
		const int32 RandomIndex = FMath::RandRange(0, ItemIds.Num() - 1);
		WannaBuyItems.Emplace(ItemIds[RandomIndex], FMath::RandRange(1, aMaxItemCount));
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

bool FMS_CustomerData::PickUpItem(int32 _PickUpItemTableId, int32 _PickUpItemCount)
{
	int32& BeforePickUpItemCount = PickUpItems.FindOrAdd(_PickUpItemTableId);

	if(const int32* WannaItemCount = WannaBuyItems.Find(_PickUpItemTableId))
	{
		if(*WannaItemCount < BeforePickUpItemCount + _PickUpItemCount)
		{
			MS_ENSURE(false);
			MS_LOG_VERBOSITY(Error, TEXT("[%s] I bought more than I wanted. Something Is Wrong."), *MS_FUNC_STRING);
			return false;
		}
	}
	else
	{
		MS_ENSURE(false);
		MS_LOG_VERBOSITY(Error, TEXT("[%s] Wrong Wanna To Buy Items Data. Please Check CustomerSupervisor Class."), *MS_FUNC_STRING);
		return false;
	}
	
	BeforePickUpItemCount += _PickUpItemCount;
	return true;
}

void UMS_CustomerCacheTable::Initialize(TObjectPtr<UMS_TableManager> aMng)
{
	Super::Initialize(aMng);
	BuildTable(aMng, EMS_TableDataType::Customer, CustomerDatas);
}

void UMS_CustomerCacheTable::Finalize()
{
	Super::Finalize();
}

void UMS_CustomerCacheTable::MakeNewCustomerData(FMS_CustomerData& NewCustomerData)
{
	if(FMS_Customer** Customer = CustomerDatas.Find(FMath::RandRange(1, CustomerDatas.Num())))
	{
		NewCustomerData = FMS_CustomerData((*Customer)->ColorType, (*Customer)->PathFile, (*Customer)->MaxItemKind, (*Customer)->MaxItemCount);
	}
}
