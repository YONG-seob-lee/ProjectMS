// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_TutorialCacheTable.h"

void UMS_TutorialCacheTable::Initialize(TObjectPtr<UMS_TableManager> aMng)
{
	Super::Initialize(aMng);
	
	BuildTable(aMng, EMS_TableDataType::Tutorial, TutorialDatas);
}

void UMS_TutorialCacheTable::Finalize()
{
	Super::Finalize();
}

void UMS_TutorialCacheTable::GetTutorialDesc(int32 TutorialKey, FText& Desc, FText& SubDesc)
{
	if(FMS_Tutorial** TutorialData = TutorialDatas.Find(TutorialKey))
	{
		Desc = FText::FromStringTable(MS_LocalizedTableId::StringTable, (*TutorialData)->Desc);
		SubDesc = FText::FromStringTable(MS_LocalizedTableId::StringTable, (*TutorialData)->SubDesc);
	}
}
