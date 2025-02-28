// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ModeSelectWidget.h"

#include "Button/MS_Button.h"
#include "Manager_Client/MS_ItemManager.h"
#include "Table/Caches/MS_FurnitureCacheTable.h"
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
	const TObjectPtr<UMS_FurnitureCacheTable> StorageTable = Cast<UMS_FurnitureCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::Furniture));
	TArray<TObjectPtr<UMS_ConstructCategoryElementData>> CategoryArray;
	StorageTable->GetFurnitureCategoryData(CategoryArray);
	
	CPP_ConstructCategoryListView->SetListItems(TArray<TObjectPtr<UObject>>(CategoryArray));
	CPP_ConstructCategoryListView->ClearSelection();
}

void UMS_ModeSelectWidget::RefreshConstructListItems(EMS_ZoneType aZoneType)
{
	const TObjectPtr<UMS_FurnitureCacheTable> StorageTable = Cast<UMS_FurnitureCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::Furniture));
	MS_CHECK(StorageTable);
	
	TArray<TObjectPtr<UMS_ConstructItemElement>> Items;
	StorageTable->GetFurnitureData(aZoneType, Items);
	
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
		OnClickedModeButtonCallback(EMS_ModeState::Construct);
	}	
}

void UMS_ModeSelectWidget::OnClickedCategory(int32 aCategoryType)
{
	RefreshConstructListItems(static_cast<EMS_ZoneType>(aCategoryType));
}
