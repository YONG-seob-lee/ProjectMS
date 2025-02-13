// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_StorageStatusWidget.h"

#include "MS_Define.h"
#include "MS_ShelfStatus.h"
#include "MS_UnitBase.h"
#include "Manager_Client/MS_ItemManager.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "Prop/Furniture/Storage/MS_Storage.h"
#include "Widget/ListViewElement/ElementData/MS_StorageSlotElementData.h"
#include "Widget/WidgetComponent/MS_TileView.h"

void UMS_StorageStatusWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	// Click Shelf Slot
	CPP_ShelfStatusWidget->SetVisibility(ESlateVisibility::Hidden);
	CPP_ShelfStatusWidget->SetOnClickedShelfSlotFunc([this](int32 aDisplayIndex, int32 aItemId)
	{
		bool IsBound = OnClickShelfSlotDelegate.ExecuteIfBound(aDisplayIndex, aItemId);
		
		if(StorageItemElementDatas.IsValidIndex(aDisplayIndex))
		{
			StorageItemElementDatas[aDisplayIndex]->SetItemId(aItemId);

			CPP_TileView->SetListItems(StorageItemElementDatas);
			CPP_TileView->RegenerateAllEntries();
			CPP_ShelfStatusWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	});
	
	CPP_ConfirmButton->GetOnClickedDelegate().AddUObject(this, &UMS_StorageStatusWidget::OnClickedConfirmButton);

	for(int32 i = 0 ; i < 4 ; i++)
	{
		const TObjectPtr<UMS_StorageSlotElementData> Data = MS_NewObject<UMS_StorageSlotElementData>(this);
		Data->SetSlotType(static_cast<int32>(EMS_ZoneType::Display));
		Data->SetSlotIndex(i);
		Data->SetItemId(INDEX_NONE);
		Data->SetMolecular(0);
		Data->SetDenominator(0);
		Data->OnClickDisplaySlotDelegate.AddUObject(this, &UMS_StorageStatusWidget::OnClickedStorageSlotButton);
		
		StorageItemElementDatas.Emplace(Data);
	}
	
	CPP_TileView->SetScrollbarVisibility(ESlateVisibility::Collapsed);
	CPP_TileView->SetListItems(StorageItemElementDatas);

	if (CPP_SkipButton)
	{
		CPP_SkipButton->SetVisibility(ESlateVisibility::Visible);
		CPP_SkipButton->GetOnClickedDelegate().AddUObject(this, &UMS_StorageStatusWidget::OnClickedCloseButton);
	}
}

void UMS_StorageStatusWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UMS_StorageStatusWidget::OnClickedConfirmButton()
{
	gWidgetMng.DestroyWidget(UMS_StorageStatusWidget::GetWidgetName());
}

void UMS_StorageStatusWidget::OnClickedStorageSlotButton(int32 aSlotIndex)
{
	CPP_ShelfStatusWidget->SetDisplaySlotIndex(aSlotIndex);
	
	if (!CPP_ShelfStatusWidget->IsVisible())
	{
		CPP_ShelfStatusWidget->SetVisibility(ESlateVisibility::Visible);
		CPP_ShelfStatusWidget->SetTileView();	
	}
}

void UMS_StorageStatusWidget::OnClickedCloseButton()
{
	gWidgetMng.DestroyWidget(this);
}

void UMS_StorageStatusWidget::OnChangeSlotDatas(const TArray<FMS_SlotData>& aSlotDatas)
{
	if (CPP_ShelfStatusWidget->IsVisible())
	{
		CPP_ShelfStatusWidget->SetTileView();
	}
}

void UMS_StorageStatusWidget::SetOwnerUnit(TWeakObjectPtr<UMS_UnitBase> aOwnerUnit)
{
	OwnerUnit = aOwnerUnit;

	if (CPP_ShelfStatusWidget)
	{
		CPP_ShelfStatusWidget->SetOwnerUnit(aOwnerUnit);
	}
}
