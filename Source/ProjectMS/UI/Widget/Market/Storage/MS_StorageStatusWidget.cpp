// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_StorageStatusWidget.h"

#include "MS_Define.h"
#include "MS_SelectRequestedItemWidget.h"
#include "Manager_Client/MS_ItemManager.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "Widget/ListViewElement/ElementData/MS_StorageSlotElementData.h"
#include "Widget/WidgetComponent/MS_TileView.h"
#include "Widget/WidgetComponent/MS_WidgetSwitcher.h"


void UMS_StorageStatusWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	// Click Shelf Slot
	CPP_SelectRequestedItemWidget->SetVisibility(ESlateVisibility::Hidden);
	CPP_SelectRequestedItemWidget->SetOnClickedShelfSlotFunc([this](int32 aDisplayIndex, int32 aItemId)
	{
		bool IsBound = OnClickRequestSlotDelegate.ExecuteIfBound(aDisplayIndex, aItemId);
	});
	
	CPP_ConfirmButton->GetOnClickedDelegate().AddUObject(this, &UMS_StorageStatusWidget::OnClickedConfirmButton);
	
	CPP_TileView->SetScrollbarVisibility(ESlateVisibility::Collapsed);
	CPP_TileView->SetListItems(StorageItemElementDatas);

	if (CPP_SkipButton)
	{
		CPP_SkipButton->SetVisibility(ESlateVisibility::Visible);
		CPP_SkipButton->GetOnClickedDelegate().AddUObject(this, &UMS_StorageStatusWidget::OnClickedCloseButton);
	}

	CPP_BgSwitcher->SetActiveWidgetIndex(0);
}

void UMS_StorageStatusWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UMS_StorageStatusWidget::OnClickedConfirmButton()
{
	OnClickedConfirmButtonDelegate.ExecuteIfBound();
}

void UMS_StorageStatusWidget::OnClickedStorageSlotButton(int32 aSlotIndex)
{
	if (OwnerZoneType != EMS_ZoneType::Display && OwnerZoneType != EMS_ZoneType::Shelf)
	{
		return;
	}
	
	CPP_SelectRequestedItemWidget->SetDisplaySlotIndex(aSlotIndex);
	
	if (!CPP_SelectRequestedItemWidget->IsVisible())
	{
		CPP_SelectRequestedItemWidget->SetVisibility(ESlateVisibility::Visible);
		CPP_SelectRequestedItemWidget->SetTileView(TemperatureType);
		CPP_BgSwitcher->SetActiveWidgetIndex(1);
	}
}

void UMS_StorageStatusWidget::OnClickedCloseButton()
{
	gWidgetMng.DestroyWidget(this);
}

void UMS_StorageStatusWidget::InitializeStorageDatas(EMS_ZoneType aOwnerZoneType, EMS_TemperatureType aTemperatureType, int32 aSlotCount)
{
	OwnerZoneType = aOwnerZoneType;
	TemperatureType = aTemperatureType;
	SlotCount = aSlotCount;

	if (CPP_SelectRequestedItemWidget)
	{
		CPP_SelectRequestedItemWidget->SetOwnerZoneType(aOwnerZoneType);
	}

	for(int32 i = 0 ; i < aSlotCount ; ++i)
	{
		const TObjectPtr<UMS_StorageSlotElementData> Data = MS_NewObject<UMS_StorageSlotElementData>(this);
		Data->SetOwnerZoneType(OwnerZoneType);
		Data->SetSlotType(OwnerZoneType == EMS_ZoneType::Pallet ? EMS_ItemSlotUIType::StorageCurrentStatus : EMS_ItemSlotUIType::StorageRequestStatus);
		Data->SetSlotIndex(i);
		Data->SetSlotData(FMS_SlotData());
		Data->OnClickDisplaySlotDelegate.AddUObject(this, &UMS_StorageStatusWidget::OnClickedStorageSlotButton);
		
		StorageItemElementDatas.Emplace(Data);
	}
}

void UMS_StorageStatusWidget::UpdateSlotDatas(const TArray<FMS_SlotData>& aSlotDatas)
{
	for (int32 i = 0; i < StorageItemElementDatas.Num(); ++i)
	{
		MS_ENSURE(IsValid(StorageItemElementDatas[i]));

		if (aSlotDatas.IsValidIndex(i))
		{
			StorageItemElementDatas[i]->SetSlotData(aSlotDatas[i]);
		}
		else
		{
			StorageItemElementDatas[i]->SetSlotData(FMS_SlotData());
		}
	}

	CPP_TileView->SetListItems(StorageItemElementDatas);
	CPP_TileView->RegenerateAllEntries();
	CPP_SelectRequestedItemWidget->SetVisibility(ESlateVisibility::Hidden);
	CPP_BgSwitcher->SetActiveWidgetIndex(0);
}
