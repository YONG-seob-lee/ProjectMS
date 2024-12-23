// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_MenuListElementWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "ElementData/MS_MenuElementData.h"

void UMS_MenuListElementWidget::NativeOnListItemObjectSet(UObject* aListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(aListItemObject);

	UMS_MenuElementData* ItemData = Cast<UMS_MenuElementData>(aListItemObject);
	
	CPP_MenuImage->SetBrushFromTexture(ItemData->GetImage());
	CPP_MenuName->SetText(FText::FromString(ItemData->GetElementName()));
}

void UMS_MenuListElementWidget::NativeOnItemSelectionChanged(bool bIsSelected)
{
	IUserObjectListEntry::NativeOnItemSelectionChanged(bIsSelected);
}
