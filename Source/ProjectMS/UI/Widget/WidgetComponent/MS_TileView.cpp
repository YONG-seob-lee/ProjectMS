// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_TileView.h"

void UMS_TileView::SetElements(const TArray<TObjectPtr<UObject>>& aListItems)
{
	SetListItems(aListItems);
	if(aListItems.IsValidIndex(0))
	{
		SetSelectedItem(aListItems[0]);
	}
}
