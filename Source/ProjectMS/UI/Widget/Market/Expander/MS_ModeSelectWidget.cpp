// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ModeSelectWidget.h"

#include "Button/MS_Button.h"
#include "Table/Caches/MS_StorageCacheTable.h"
#include "Widget/ListViewElement/ElementData/MS_ConstructCategoryElementData.h"
#include "Widget/ListViewElement/ElementData/MS_ConstructItemElement.h"
#include "Widget/WidgetComponent/MS_TileView.h"
#include "Widget/WidgetComponent/MS_WidgetSwitcher.h"

void UMS_ModeSelectWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CPP_ModeButton01->GetOnClickedDelegate().AddUObject(this, &UMS_ModeSelectWidget::OnClickModeButton, EMS_ModeState::Construct);
	
	CPP_ConstructCategoryTileView->SetScrollbarVisibility(ESlateVisibility::Collapsed);
	gItemMng.OnClickedTileViewItem.AddUObject(this, &UMS_ModeSelectWidget::OnClickedCategory);
	CPP_ConstructItemTileView->SetScrollbarVisibility(ESlateVisibility::Collapsed);

	InitCategory();
	RefreshConstructListItems(EMS_StorageType::Display);
}

void UMS_ModeSelectWidget::SwitchWidget(EMS_ModeState aModeState) const
{
	CPP_WidgetSwitcher->SetActiveWidgetIndex(static_cast<int32>(aModeState));
}

void UMS_ModeSelectWidget::InitCategory() const
{
	const TObjectPtr<UMS_StorageCacheTable> StorageTable = Cast<UMS_StorageCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::Storage));
	TArray<TObjectPtr<UMS_ConstructCategoryElementData>> CategoryArray;
	StorageTable->GetStorageCategoryData(CategoryArray);
	
	CPP_ConstructCategoryTileView->SetElements(TArray<TObjectPtr<UObject>>(CategoryArray));
}

void UMS_ModeSelectWidget::RefreshConstructListItems(EMS_StorageType aStorageType)
{
	const TObjectPtr<UMS_StorageCacheTable> StorageTable = Cast<UMS_StorageCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::Storage));
	TArray<TObjectPtr<UMS_ConstructItemElement>> Items;
	StorageTable->GetStorageData(aStorageType, Items);
	
	CPP_ConstructItemTileView->SetListItems(Items);
}

void UMS_ModeSelectWidget::OnClickModeButton(EMS_ModeState aModeState)
{
	if(OnClickedModeButtonCallback)
	{
		OnClickedModeButtonCallback(aModeState);
	}
}

void UMS_ModeSelectWidget::OnClickedCategory(int32 aCategoryType)
{
	RefreshConstructListItems(static_cast<EMS_StorageType>(aCategoryType));
}
