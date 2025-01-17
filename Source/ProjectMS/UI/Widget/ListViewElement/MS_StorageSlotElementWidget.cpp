// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_StorageSlotElementWidget.h"

#include "Components/TextBlock.h"
#include "ElementData/MS_StorageSlotElementData.h"
#include "Widget/Market/Storage/MS_SlotWidget.h"
#include "Widget/System/MS_CountWidget.h"
#include "Widget/WidgetComponent/MS_WidgetSwitcher.h"

void UMS_StorageSlotElementWidget::NativeOnListItemObjectSet(UObject* aListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(aListItemObject);

	if(const UMS_StorageSlotElementData* SlotElementData = Cast<UMS_StorageSlotElementData>(aListItemObject))
	{
		SlotIndex = SlotElementData->GetSlotIndex();
		ItemId = SlotElementData->GetItemId();
		const int32 ShelfCount = SlotElementData->GetShelfCount();
		
		if(static_cast<EMS_StorageType>(SlotElementData->GetSlotType()) == EMS_StorageType::Display)
		{
			CPP_TextSwitcher->SetActiveWidgetIndex(0);
			CPP_CountWidget->SetCount(SlotElementData->GetMolecular(), SlotElementData->GetDenominator());
		}
		else
		{
			CPP_TextSwitcher->SetActiveWidgetIndex(1);
			if(ItemId == INDEX_NONE)
			{
				CPP_RemainCount->SetVisibility(ESlateVisibility::Collapsed);
			}
			else
			{
				CPP_RemainCount->SetText(FText::FromString(FString::Format(TEXT("{0} 개"), {ShelfCount})));
			}
		}
		
		CPP_SlotWidget->SetSlot(ItemId);
	}
}

void UMS_StorageSlotElementWidget::NativeOnItemSelectionChanged(bool bIsSelected)
{
	IUserObjectListEntry::NativeOnItemSelectionChanged(bIsSelected);
}

FReply UMS_StorageSlotElementWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if(const TObjectPtr<UMS_StorageSlotElementData> StorageSlotElementData = GetListItem<UMS_StorageSlotElementData>())
	{
		if(static_cast<EMS_StorageType>(StorageSlotElementData->GetSlotType()) == EMS_StorageType::Display)
		{
			StorageSlotElementData->OnClickDisplaySlotDelegate.Broadcast(SlotIndex);
		}
		else
		{
			StorageSlotElementData->OnClickShelfSlotDelegate.Broadcast(ItemId);
		}
	}
	
	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}
