// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_BehaviorElementWidget.h"

#include "MS_Define.h"
#include "Components/TextBlock.h"
#include "ElementData/MS_BehaviorElementData.h"
#include "Table/Caches/MS_ResourceUnitCacheTable.h"

namespace BehaviorTime
{
	constexpr int32 MinutePerOneHour = 60;
}

void UMS_BehaviorElementWidget::NativeOnListItemObjectSet(UObject* aListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(aListItemObject);
	

	if(const TObjectPtr<UMS_BehaviorElementData> BehaviorElementData = Cast<UMS_BehaviorElementData>(aListItemObject))
	{
		const TObjectPtr<UMS_ResourceUnitCacheTable> UnitTable = Cast<UMS_ResourceUnitCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::ResourceUnit));
		if(!UnitTable)
		{
			MS_Ensure(UnitTable);
			return;
		}

		const FString UnitName = UnitTable->GetUnitName(BehaviorElementData->GetUnitHandle());
		
		CPP_Minute->SetText(FText::FromString(FString::Format(TEXT("({0}){1}시 {2}분 : "), {UnitName, BehaviorElementData->GetMinute() / BehaviorTime::MinutePerOneHour, BehaviorElementData->GetMinute() % BehaviorTime::MinutePerOneHour})));
		CPP_BehaviorDesc->SetText(BehaviorElementData->GetBehavior());
	}
}
