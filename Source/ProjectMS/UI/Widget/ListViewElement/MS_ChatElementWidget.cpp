// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ChatElementWidget.h"

#include "Components/TextBlock.h"
#include "ElementData/MS_ChatElementData.h"
#include "Manager_Both/MS_TableManager.h"
#include "Manager_Both/MS_UnitManager.h"
#include "Units/MS_CustomerAIUnit.h"

namespace ChatTime
{
	constexpr int32 MinutePerOneHour = 60; 
}
void UMS_ChatElementWidget::NativeOnListItemObjectSet(UObject* aListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(aListItemObject);

	if(const TObjectPtr<UMS_ChatElementData> ChatElementData = Cast<UMS_ChatElementData>(aListItemObject))
	{
		if(const TObjectPtr<UMS_CustomerAIUnit> CustomerUnit = Cast<UMS_CustomerAIUnit>(gUnitMng.GetUnit(ChatElementData->GetUnitHandle())))
		{
			CPP_Minute->SetText(FText::FromString(FString::Format(TEXT("{1}시 {2}분 : ({0})"), {CustomerUnit->GetCustomerName(), ChatElementData->GetMinute() / ChatTime::MinutePerOneHour, ChatElementData->GetMinute() % ChatTime::MinutePerOneHour})));
			CPP_ChatDesc->SetText(ChatElementData->GetChatting());
		}
	}

}
