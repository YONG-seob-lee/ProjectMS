// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ModeSelectWidget.h"

#include "Button/MS_Button.h"
#include "Table/Caches/MS_StorageCacheTable.h"
#include "Widget/ListViewElement/MS_ConstructCategoryElementWidget.h"
#include "Widget/ListViewElement/ElementData/MS_ConstructCategoryElementData.h"
#include "Widget/ListViewElement/ElementData/MS_ConstructItemElement.h"
#include "Widget/WidgetComponent/MS_ListView.h"
#include "Widget/WidgetComponent/MS_TileView.h"

void UMS_ModeSelectWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	CPP_ConstructCategoryListView->SetScrollbarVisibility(ESlateVisibility::Collapsed);
	CPP_ConstructCategoryListView->OnItemClicked().AddUObject(this, &UMS_ModeSelectWidget::OnClickedModeButton);
	gItemMng.OnClickedTileViewItem.AddUObject(this, &UMS_ModeSelectWidget::OnClickedCategory);
	
	CPP_ConstructItemListView->SetScrollbarVisibility(ESlateVisibility::Collapsed);

	InitCategory();
	RefreshConstructListItems(EMS_ZoneType::Display);
}

void UMS_ModeSelectWidget::InitCategory() const
{
	const TObjectPtr<UMS_StorageCacheTable> StorageTable = Cast<UMS_StorageCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::Storage));
	TArray<TObjectPtr<UMS_ConstructCategoryElementData>> CategoryArray;
	StorageTable->GetStorageCategoryData(CategoryArray);
	
	CPP_ConstructCategoryListView->SetListItems(TArray<TObjectPtr<UObject>>(CategoryArray));
	CPP_ConstructCategoryListView->ClearSelection();
}

void UMS_ModeSelectWidget::RefreshConstructListItems(EMS_ZoneType aZoneType)
{
	const TObjectPtr<UMS_StorageCacheTable> StorageTable = Cast<UMS_StorageCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::Storage));
	MS_CHECK(StorageTable);
	
	TArray<TObjectPtr<UMS_ConstructItemElement>> Items;
	StorageTable->GetStorageData(aZoneType, Items);
	
	CPP_ConstructItemListView->SetListItems(Items);
}

void UMS_ModeSelectWidget::OnClickedModeButton(UObject* Object)
{
	const TObjectPtr<UMS_ConstructCategoryElementData> Data = Cast<UMS_ConstructCategoryElementData>(Object);
	if(!Data)
	{
		return;
	}
	
	if(OnClickedModeButtonCallback)
	{
		OnClickedModeButtonCallback(static_cast<EMS_ModeState>(Data->GetZoneType()));
	}	
}

void UMS_ModeSelectWidget::OnClickedCategory(int32 aCategoryType)
{
	RefreshConstructListItems(static_cast<EMS_ZoneType>(aCategoryType));
}
