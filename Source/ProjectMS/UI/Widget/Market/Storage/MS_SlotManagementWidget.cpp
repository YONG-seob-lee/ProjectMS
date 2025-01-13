// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_SlotManagementWidget.h"

#include "Widget/ListViewElement/ElementData/MS_ItemElementData.h"
#include "Widget/WidgetComponent/MS_TileView.h"


void UMS_SlotManagementWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMS_SlotManagementWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UMS_SlotManagementWidget::SettingItems(TArray<TObjectPtr<UMS_ItemElementData>>& aItemElementDatas) const
{
	CPP_SelectItemTileView->SetElements(TArray<TObjectPtr<UObject>>(aItemElementDatas));
}
