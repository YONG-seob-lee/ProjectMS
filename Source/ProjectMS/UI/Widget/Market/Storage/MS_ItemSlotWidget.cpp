// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ItemSlotWidget.h"

#include "MS_Define.h"
#include "Blueprint/DragDropOperation.h"
#include "Components/Image.h"
#include "Table/Caches/MS_ItemCacheTable.h"
#include "Widget/ListViewElement/MS_ItemElementWidget.h"

void UMS_ItemSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

bool UMS_ItemSlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	if(const TObjectPtr<UMS_ItemElementWidget> ItemElementWidget = Cast<UMS_ItemElementWidget>(InOperation->DefaultDragVisual))
	{
		CPP_Slot->SetBrushFromTexture(ItemElementWidget->GetItemImage());
		CPP_Slot->SetVisibility(ESlateVisibility::HitTestInvisible);
		CPP_Slot->SetOpacity(1.f);

		return true;
	}
	
	return false;
}

void UMS_ItemSlotWidget::SetSlot(int32 aItemId) const
{
	if(aItemId == INDEX_NONE)
	{
		const FString SlotImagePath = TEXT("/Game/UI/Image/Item/BlankSlot.BlankSlot");
		UTexture2D* SlotTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *SlotImagePath));
		if(SlotTexture)
		{
			CPP_Slot->SetBrushFromTexture(SlotTexture);
		}
	}
	else
	{
		const TObjectPtr<UMS_ItemCacheTable> ItemTable = Cast<UMS_ItemCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::ItemData));
		MS_CHECK(ItemTable);

		UTexture2D* ItemImage = ItemTable->GetItemImage(aItemId);
		CPP_Slot->SetBrushFromTexture(ItemImage);
	}
}
