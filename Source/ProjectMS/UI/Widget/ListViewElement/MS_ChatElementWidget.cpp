// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ChatElementWidget.h"

#include "Components/TextBlock.h"
#include "ElementData/MS_ChatElementData.h"
#include "Manager_Both/MS_TableManager.h"
#include "Table/Caches/MS_StaffCacheTable.h"

namespace ChatTime
{
	constexpr int32 MinutePerOneHour = 60; 
}
void UMS_ChatElementWidget::NativeOnListItemObjectSet(UObject* aListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(aListItemObject);

	if(const TObjectPtr<UMS_ChatElementData> ChatElementData = Cast<UMS_ChatElementData>(aListItemObject))
	{
		const TObjectPtr<UMS_StaffCacheTable> StaffTable = Cast<UMS_StaffCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::Staff));
		MS_ENSURE(StaffTable);

		FName StaffName = FName();
		StaffTable->GetStaffName(ChatElementData->GetUnitHandle(), StaffName);
		
		CPP_Minute->SetText(FText::FromString(FString::Format(TEXT("({0}){1}시 {2}분 : "), {StaffName.ToString(), ChatElementData->GetMinute() / ChatTime::MinutePerOneHour, ChatElementData->GetMinute() % ChatTime::MinutePerOneHour})));
		CPP_ChatDesc->SetText(ChatElementData->GetChatting());
	}

}
