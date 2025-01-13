// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_SlotWidget.h"

#include "MS_Define.h"
#include "Blueprint/DragDropOperation.h"
#include "Components/Image.h"
#include "Widget/ListViewElement/MS_ItemElementWidget.h"

void UMS_SlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(CPP_Slot)
	{
		CPP_Slot->SetOpacity(0.f);
	}
}

bool UMS_SlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
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
