// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_MenuListElementWidget.h"

#include "MS_Define.h"
#include "Widget/System/Menu/MS_MenuExpanderWidget.h"

void UMS_MenuListElementWidget::NativeOnListItemObjectSet(UObject* aListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(aListItemObject);

	UMS_ListItemData* ItemData = Cast<UMS_ListItemData>(aListItemObject);
	
	MS_LOG(TEXT("asdf"));
}

void UMS_MenuListElementWidget::NativeOnItemSelectionChanged(bool bIsSelected)
{
	IUserObjectListEntry::NativeOnItemSelectionChanged(bIsSelected);
}
