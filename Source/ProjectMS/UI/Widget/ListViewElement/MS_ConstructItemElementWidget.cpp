// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ConstructItemElementWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "ElementData/MS_ConstructItemElement.h"

void UMS_ConstructItemElementWidget::NativeOnListItemObjectSet(UObject* aListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(aListItemObject);

	UMS_ConstructItemElement* ItemData = Cast<UMS_ConstructItemElement>(aListItemObject);
	
	CPP_ConstructItemText->SetText(FText::FromString(ItemData->GetElementName()));
	CPP_ConstructItemImage->SetBrushFromTexture(ItemData->GetImage());
}

void UMS_ConstructItemElementWidget::NativeOnItemSelectionChanged(bool bIsSelected)
{
	IUserObjectListEntry::NativeOnItemSelectionChanged(bIsSelected);
}
