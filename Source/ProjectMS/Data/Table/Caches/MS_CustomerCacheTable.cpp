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
	for(int32 i = 0 ; i < FMath::RandRange(0, aMaxItemKind) ; i++)
	{
		const int32 RandomIndex = FMath::RandRange(0, ItemIds.Num() - 1);
		PurchaseItem.Emplace(ItemIds[RandomIndex], FMath::RandRange(0, FMath::RandRange(0, aMaxItemCount)));
	}
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
	if(FMS_Customer** Customer = CustomerDatas.Find(FMath::RandRange(0, CustomerDatas.Num() - 1)))
	{
		NewCustomerData = FMS_CustomerData((*Customer)->ColorType, (*Customer)->PathFile, (*Customer)->MaxItemKind, (*Customer)->MaxItemCount);
	}
}
