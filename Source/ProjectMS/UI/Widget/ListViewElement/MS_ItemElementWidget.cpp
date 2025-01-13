// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ItemElementWidget.h"

#include "MS_Define.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "ElementData/MS_ItemElementData.h"

void UMS_ItemElementWidget::NativeOnListItemObjectSet(UObject* aListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(aListItemObject);
	
	UMS_ItemElementData* ItemData = Cast<UMS_ItemElementData>(aListItemObject);
	
	CPP_ItemName->SetText(FText::FromString(ItemData->GetElementName()));
	CPP_ItemImage->SetBrushFromTexture(ItemData->GetImage());
}

void UMS_ItemElementWidget::NativeOnItemSelectionChanged(bool bIsSelected)
{
	IUserObjectListEntry::NativeOnItemSelectionChanged(bIsSelected);
}

void UMS_ItemElementWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	MS_LOG(TEXT("============ UMS_ItemElementWidget::NativeOnDragDetected"));
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
