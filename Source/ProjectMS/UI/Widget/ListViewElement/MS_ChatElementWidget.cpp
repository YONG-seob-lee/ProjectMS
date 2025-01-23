// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ChatElementWidget.h"

#include "Components/TextBlock.h"
#include "ElementData/MS_ChatElementData.h"
#include "Manager_Both/MS_TableManager.h"
#include "Table/Caches/MS_ResourceUnitCacheTable.h"

namespace Time
{
	constexpr int32 MinutePerOneHour = 60; 
}
void UMS_ChatElementWidget::NativeOnListItemObjectSet(UObject* aListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(aListItemObject);

	if(const TObjectPtr<UMS_ChatElementData> ChatElementData = Cast<UMS_ChatElementData>(aListItemObject))
	{
		const TObjectPtr<UMS_ResourceUnitCacheTable> UnitTable = Cast<UMS_ResourceUnitCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::ResourceUnit));
		if(!UnitTable)
		{
			MS_Ensure(UnitTable);
			return;
		}

		const FString UnitName = UnitTable->GetUnitName(ChatElementData->GetUnitHandle());
		
		CPP_Minute->SetText(FText::FromString(FString::Format(TEXT("  {0}시 {1}분  : "), {ChatElementData->GetMinute() / Time::MinutePerOneHour, ChatElementData->GetMinute() % Time::MinutePerOneHour})));
		CPP_ChatDesc->SetText(ChatElementData->GetChatting());
	}

}
