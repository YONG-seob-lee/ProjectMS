// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_StorageCategoryElementWidget.h"

void UMS_StorageCategoryElementWidget::NativeOnListItemObjectSet(UObject* aListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(aListItemObject);
}

void UMS_StorageCategoryElementWidget::NativeOnItemSelectionChanged(bool bIsSelected)
{
	IUserObjectListEntry::NativeOnItemSelectionChanged(bIsSelected);
}
