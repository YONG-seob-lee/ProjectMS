// Fill out your copyright notice in the Description page of Project Settings.


#include "SlotManagementWidget.h"

#include "Manager_Client/MS_ItemManager.h"

void USlotManagementWidget::NativeConstruct()
{
	Super::NativeConstruct();

	TArray<FMS_Item*> Items;
	gItemMng.GetItem(Items, EMS_ItemType::Beverage);
}

void USlotManagementWidget::NativeDestruct()
{
	Super::NativeDestruct();
}
