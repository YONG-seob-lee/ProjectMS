// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_BehaviorElementWidget.h"

#include "Components/TextBlock.h"
#include "ElementData/MS_BehaviorElementData.h"
#include "Manager_Both/MS_UnitManager.h"
#include "Units/MS_CustomerAIUnit.h"

namespace BehaviorTime
{
	constexpr int32 MinutePerOneHour = 60;
}

void UMS_BehaviorElementWidget::NativeOnListItemObjectSet(UObject* aListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(aListItemObject);
	

	if(const TObjectPtr<UMS_BehaviorElementData> BehaviorElementData = Cast<UMS_BehaviorElementData>(aListItemObject))
	{
		if(const TObjectPtr<UMS_CustomerAIUnit> CustomerUnit = Cast<UMS_CustomerAIUnit>(gUnitMng.GetUnit(BehaviorElementData->GetUnitHandle())))
		{
		
			CPP_Minute->SetText(FText::FromString(FString::Format(TEXT("{1}시 {2}분 : ({0})"), {CustomerUnit->GetCustomerName(), BehaviorElementData->GetMinute() / BehaviorTime::MinutePerOneHour, BehaviorElementData->GetMinute() % BehaviorTime::MinutePerOneHour})));
			CPP_BehaviorDesc->SetText(BehaviorElementData->GetBehavior());
		}
	}
}
