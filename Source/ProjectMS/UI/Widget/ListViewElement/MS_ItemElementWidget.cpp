// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ItemElementWidget.h"

#include "MS_Define.h"
#include "Blueprint/DragDropOperation.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "ElementData/MS_ItemElementData.h"
#include "Manager_Client/MS_WidgetManager.h"

void UMS_ItemElementWidget::NativeOnListItemObjectSet(UObject* aListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(aListItemObject);
	
	UMS_ItemElementData* ItemData = Cast<UMS_ItemElementData>(aListItemObject);

	ItemName = ItemData->GetElementName();
	ItemImage = ItemData->GetImage();
	CPP_ItemName->SetText(FText::FromString(ItemName));
	CPP_ItemImage->SetBrushFromTexture(ItemImage);

	if(ItemData->IsShowItemName() == false)
	{
		CPP_ItemName->SetVisibility(ESlateVisibility::Collapsed);
	}

	if(ItemData->IsShowItemCount() == false)
	{
		CPP_CountText->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		CPP_CountText->SetText(FText::FromString(FString::FromInt(ItemData->GetItemCount())));
	}
}

void UMS_ItemElementWidget::NativeOnItemSelectionChanged(bool bIsSelected)
{
	IUserObjectListEntry::NativeOnItemSelectionChanged(bIsSelected);
}

void UMS_ItemElementWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	MS_LOG(TEXT("============ UMS_ItemElementWidget::NativeOnDragDetected"));

	const TObjectPtr<UDragDropOperation> DragWidget = MS_NewObject<UDragDropOperation>();
	MS_CHECK(DragWidget);
	DragWidget->Pivot = EDragPivot::MouseDown;
	DragWidget->DefaultDragVisual = gWidgetMng.Create_Widget_NotManaging(GetWidgetPath());
	const TObjectPtr<UMS_ItemElementWidget> ItemElementWidget = Cast<UMS_ItemElementWidget>(DragWidget->DefaultDragVisual);
	ItemElementWidget->InitializeItem(ItemName, ItemImage);
	OutOperation = DragWidget;
}

void UMS_ItemElementWidget::NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragEnter(InGeometry, InDragDropEvent, InOperation);

	MS_LOG(TEXT("============ UMS_ItemElementWidget::NativeOnDragEnter"));
}

void UMS_ItemElementWidget::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);

	MS_LOG(TEXT("============ UMS_ItemElementWidget::NativeOnDragCancelled"));
}

void UMS_ItemElementWidget::InitializeItem(const FString& aItemName, UTexture2D* aItemImage)
{
	ItemName = aItemName;
	ItemImage = aItemImage;
	CPP_ItemName->SetText(FText::FromString(aItemName));
	CPP_ItemImage->SetBrushFromTexture(aItemImage);
}
