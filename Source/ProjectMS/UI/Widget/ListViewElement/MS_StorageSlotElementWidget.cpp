// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_StorageSlotElementWidget.h"

#include "ElementData/MS_StorageSlotElementData.h"
#include "Widget/Market/Storage/MS_SlotWidget.h"
#include "Widget/System/MS_CountWidget.h"

void UMS_StorageSlotElementWidget::NativeOnListItemObjectSet(UObject* aListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(aListItemObject);

	if(const UMS_StorageSlotElementData* SlotElementData = Cast<UMS_StorageSlotElementData>(aListItemObject))
	{
		CPP_SlotWidget->SetSlot(SlotElementData->GetItemId());
		CPP_CountWidget->SetCount(SlotElementData->GetMolecular(), SlotElementData->GetDenominator());
	}
}

void UMS_StorageSlotElementWidget::NativeOnItemSelectionChanged(bool bIsSelected)
{
	IUserObjectListEntry::NativeOnItemSelectionChanged(bIsSelected);
}
