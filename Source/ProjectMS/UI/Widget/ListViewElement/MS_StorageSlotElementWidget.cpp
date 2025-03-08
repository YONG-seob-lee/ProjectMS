// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_StorageSlotElementWidget.h"

#include "Components/TextBlock.h"
#include "ElementData/MS_StorageSlotElementData.h"
#include "Manager_Both/MS_TableManager.h"
#include "Table/RowBase/MS_ItemData.h"
#include "Widget/Market/Storage/MS_ItemSlotWidget.h"
#include "Widget/System/MS_CountWidget.h"
#include "Widget/WidgetComponent/MS_WidgetSwitcher.h"


void UMS_StorageSlotElementWidget::NativeOnListItemObjectSet(UObject* aListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(aListItemObject);

	if(const UMS_StorageSlotElementData* SlotElementData = Cast<UMS_StorageSlotElementData>(aListItemObject))
	{
		OwnerZoneType = SlotElementData->GetOwnerZoneType();
		SlotUIType = SlotElementData->GetSlotUIType();
		SlotIndex = SlotElementData->GetSlotIndex();
		SlotData = SlotElementData->GetSlotData();
		
		if (SlotElementData->GetSlotUIType() == EMS_ItemSlotUIType::StorageRequestStatus)
		{
			UpdateWhenStorageRequestStatus();
		}
		else if (SlotElementData->GetSlotUIType() == EMS_ItemSlotUIType::StorageCurrentStatus)
		{
			UpdateWhenStorageCurrentStatus();
		}
		else
		{
			UpdateWhenRequestable();
		}
	}
}

void UMS_StorageSlotElementWidget::NativeOnItemSelectionChanged(bool bIsSelected)
{
	IUserObjectListEntry::NativeOnItemSelectionChanged(bIsSelected);
	
	if(const TObjectPtr<UMS_StorageSlotElementData> StorageSlotElementData = GetListItem<UMS_StorageSlotElementData>())
	{
		if(static_cast<EMS_ZoneType>(StorageSlotElementData->GetSlotUIType()) == EMS_ZoneType::Display)
		{
			StorageSlotElementData->OnClickDisplaySlotDelegate.Broadcast(SlotIndex);
		}
		else
		{
			StorageSlotElementData->OnClickShelfSlotDelegate.Broadcast(SlotData.CurrentItemTableId);
		}
	}
}

FReply UMS_StorageSlotElementWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	// if(const TObjectPtr<UMS_StorageSlotElementData> StorageSlotElementData = GetListItem<UMS_StorageSlotElementData>())
	// {
	// 	if(static_cast<EMS_ZoneType>(StorageSlotElementData->GetSlotUIType()) == EMS_ZoneType::Display)
	// 	{
	// 		StorageSlotElementData->OnClickDisplaySlotDelegate.Broadcast(SlotIndex);
	// 	}
	// 	else
	// 	{
	// 		StorageSlotElementData->OnClickShelfSlotDelegate.Broadcast(SlotData.CurrentItemTableId);
	// 	}
	// }
	
	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

void UMS_StorageSlotElementWidget::UpdateWhenStorageRequestStatus()
{
	CPP_TextSwitcher->SetActiveWidgetIndex(0);

	FMS_ItemData* ItemData = gTableMng.GetTableRowData<FMS_ItemData>(EMS_TableDataType::ItemData, SlotData.RequestItemTableId);
	if (ItemData == nullptr)
	{
		CPP_ItemSlotWidget->SetSlot(INDEX_NONE);
		CPP_CountWidget->SetCount(-1, 0);
		CPP_CountWidget->SetVisibility(ESlateVisibility::Hidden);

		return;
	}
	
	CPP_TextSwitcher->SetActiveWidgetIndex(0);
	CPP_CountWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	
	if (OwnerZoneType == EMS_ZoneType::Display)
	{
		CPP_CountWidget->SetCount(SlotData.CurrentItemTableId == SlotData.RequestItemTableId ? SlotData.CurrentItemCount : -1, ItemData->Slot100x100MaxCount);
	}
	else if (OwnerZoneType == EMS_ZoneType::Shelf)
	{
		CPP_CountWidget->SetCount(SlotData.CurrentItemTableId == SlotData.RequestItemTableId ? SlotData.CurrentItemCount : -1, ItemData->BoxMaxCount);
	}
	else if (OwnerZoneType == EMS_ZoneType::Pallet)
	{
		CPP_CountWidget->SetCount(SlotData.CurrentItemCount, ItemData->BoxMaxCount);
	}
	else
	{
		CPP_CountWidget->SetCount(SlotData.CurrentItemTableId == SlotData.RequestItemTableId ? SlotData.CurrentItemCount : -1, -1);
	}
	
	CPP_ItemSlotWidget->SetSlot(SlotData.RequestItemTableId);
}

void UMS_StorageSlotElementWidget::UpdateWhenStorageCurrentStatus()
{
	CPP_TextSwitcher->SetActiveWidgetIndex(0);

	FMS_ItemData* ItemData = gTableMng.GetTableRowData<FMS_ItemData>(EMS_TableDataType::ItemData, SlotData.CurrentItemTableId);
	if (ItemData == nullptr)
	{
		CPP_ItemSlotWidget->SetSlot(INDEX_NONE);
		CPP_CountWidget->SetCount(-1, 0);
		CPP_CountWidget->SetVisibility(ESlateVisibility::Hidden);
		return;
	}
	
	CPP_TextSwitcher->SetActiveWidgetIndex(0);
	CPP_CountWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	
	CPP_CountWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	
	if (OwnerZoneType == EMS_ZoneType::Display)
	{
		CPP_CountWidget->SetCount(SlotData.CurrentItemCount, ItemData->SlotPath100x100);
	}
	else if (OwnerZoneType == EMS_ZoneType::Shelf || OwnerZoneType == EMS_ZoneType::Pallet)
	{
		CPP_CountWidget->SetCount(SlotData.CurrentItemCount, ItemData->BoxMaxCount);
	}
	else
	{
		CPP_CountWidget->SetCount(SlotData.CurrentItemCount, -1);
	}
		
	CPP_ItemSlotWidget->SetSlot(SlotData.CurrentItemTableId);
}

void UMS_StorageSlotElementWidget::UpdateWhenRequestable()
{
	CPP_TextSwitcher->SetActiveWidgetIndex(1);
	if(SlotData.CurrentItemTableId == INDEX_NONE)
	{
		CPP_RemainCount->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		CPP_RemainCount->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		CPP_RemainCount->SetText(FText::FromString(FString::Format(TEXT("{0} 개"), {SlotData.CurrentItemCount})));
	}

	CPP_ItemSlotWidget->SetSlot(SlotData.CurrentItemTableId);
}
