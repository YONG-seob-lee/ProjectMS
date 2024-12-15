// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_CommonCacheTable.h"

void UMS_CommonCacheTable::Initialize(TObjectPtr<UMS_TableManager> aMng)
{
	Super::Initialize(aMng);

	TMap<int32, FMS_Common*> PrimitiveCommon;
	PrimitiveCommon.Empty();

	BuildTable(aMng, EMS_TableDataType::Common, PrimitiveCommon);

	for(const auto& CommonData : PrimitiveCommon)
	{
		CommonDatas.Emplace(CommonData.Value->Contents, CommonData.Value);
	}
}

void UMS_CommonCacheTable::Finalize()
{
	CommonDatas.Empty();
	
	Super::Finalize();
}

int32 UMS_CommonCacheTable::GetParameter01(const FString& aContents)
{
	if(FMS_Common** CommonData = CommonDatas.Find(aContents))
	{
		return (*CommonData)->Parameter01;
	}

	return -1;
}

float UMS_CommonCacheTable::GetParameter02(const FString& aContents)
{
	if(FMS_Common** CommonData = CommonDatas.Find(aContents))
	{
		return (*CommonData)->Parameter02;
	}

	return -1;
}
