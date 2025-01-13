// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_StorageStatusModalWidget.h"

#include "Manager_Both/MS_TableManager.h"
#include "Manager_Client/MS_ItemManager.h"
#include "Table/Caches/MS_ItemCacheTable.h"
#include "Widget/Market/Storage/MS_SlotManagementWidget.h"

void UMS_StorageStatusModalWidget::NativeConstruct()
{
	Super::NativeConstruct();

	const TObjectPtr<UMS_ItemCacheTable> ItemTable = Cast<UMS_ItemCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::ItemData));
	MS_CHECK(ItemTable);
	
	TArray<TObjectPtr<UMS_ItemElementData>> ItemElementDatas;
	ItemTable->GetItemElementDatas(ItemElementDatas);
	
	CPP_SlotManagementWidget->SettingItems(ItemElementDatas);
}

void UMS_StorageStatusModalWidget::NativeDestruct()
{
	Super::NativeDestruct();
}
