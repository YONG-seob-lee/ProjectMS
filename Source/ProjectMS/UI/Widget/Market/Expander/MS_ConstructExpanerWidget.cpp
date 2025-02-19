// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ConstructExpanerWidget.h"

#include "Button/MS_Button.h"
#include "Table/Caches/MS_StorageCacheTable.h"
#include "Widget/ListViewElement/MS_ConstructCategoryElementWidget.h"
#include "Widget/ListViewElement/ElementData/MS_ConstructCategoryElementData.h"
#include "Widget/ListViewElement/ElementData/MS_ConstructItemElement.h"
#include "Widget/WidgetComponent/MS_ListView.h"
#include "Widget/WidgetComponent/MS_TileView.h"

void UMS_ConstructExpanerWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	CPP_ExpanderCategoryListView->SetScrollbarVisibility(ESlateVisibility::Collapsed);
	CPP_ExpanderCategoryListView->OnItemClicked().AddUObject(this, &UMS_ConstructExpanerWidget::OnClickedCategoryButton);
	gItemMng.OnClickedTileViewItem.AddUObject(this, &UMS_ConstructExpanerWidget::OnClickedCategory);
	
	CPP_ExpanderItemListView->SetScrollbarVisibility(ESlateVisibility::Collapsed);

	InitCategory();
	RefreshConstructListItems(EMS_ZoneType::Display);
}

void UMS_ConstructExpanerWidget::InitCategory() const
{
	const TObjectPtr<UMS_StorageCacheTable> StorageTable = Cast<UMS_StorageCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::Storage));
	TArray<TObjectPtr<UMS_ConstructCategoryElementData>> CategoryArray;
	StorageTable->GetStorageCategoryData(CategoryArray);
	
	CPP_ExpanderCategoryListView->SetListItems(TArray<TObjectPtr<UObject>>(CategoryArray));
	CPP_ExpanderCategoryListView->ClearSelection();
}

void UMS_ConstructExpanerWidget::RefreshConstructListItems(EMS_ZoneType aZoneType)
{
	const TObjectPtr<UMS_StorageCacheTable> StorageTable = Cast<UMS_StorageCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::Storage));
	MS_CHECK(StorageTable);
	
	TArray<TObjectPtr<UMS_ConstructItemElement>> Items;
	StorageTable->GetStorageData(aZoneType, Items);
	
	CPP_ExpanderItemListView->SetListItems(Items);
}

void UMS_ConstructExpanerWidget::OnClickedCategoryButton(UObject* Object)
{
	const TObjectPtr<UMS_ConstructCategoryElementData> Data = Cast<UMS_ConstructCategoryElementData>(Object);
	if(!Data)
	{
		return;
	}
	
	if(OnClickedCategoryButtonCallback)
	{
		OnClickedCategoryButtonCallback();
	}	
}

void UMS_ConstructExpanerWidget::OnClickedCategory(int32 aCategoryType)
{
	RefreshConstructListItems(static_cast<EMS_ZoneType>(aCategoryType));
}
