// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ConstructCategoryElementWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "ElementData/MS_ConstructCategoryElementData.h"

void UMS_ConstructCategoryElementWidget::NativeOnListItemObjectSet(UObject* aListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(aListItemObject);

	UMS_ConstructCategoryElementData* ItemData = Cast<UMS_ConstructCategoryElementData>(aListItemObject);
	
	CPP_CategoryImage->SetBrushFromTexture(ItemData->GetImage());
	CPP_CategoryName->SetText(FText::FromString(ItemData->GetElementName()));
}

void UMS_ConstructCategoryElementWidget::NativeOnItemSelectionChanged(bool bIsSelected)
{
	IUserObjectListEntry::NativeOnItemSelectionChanged(bIsSelected);
}
