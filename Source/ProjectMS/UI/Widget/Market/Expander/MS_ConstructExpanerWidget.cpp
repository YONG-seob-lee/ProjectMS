// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ConstructExpanerWidget.h"

#include "Button/MS_Button.h"
#include "Manager_Client/MS_ItemManager.h"
#include "Table/Caches/MS_FurnitureCacheTable.h"
#include "Widget/ListViewElement/ElementData/MS_ConstructCategoryElementData.h"
#include "Widget/ListViewElement/ElementData/MS_ConstructItemElement.h"
#include "Widget/WidgetComponent/MS_ListView.h"
#include "Widget/WidgetComponent/MS_TileView.h"
#include "Widget/WidgetComponent/MS_WidgetSwitcher.h"

void UMS_ConstructExpanerWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	CPP_ExpanderCategoryListView->SetScrollbarVisibility(ESlateVisibility::Collapsed);
	CPP_ExpanderCategoryListView->OnItemClicked().AddUObject(this, &UMS_ConstructExpanerWidget::OnClickedCategoryButton);
	gItemMng.OnClickedTileViewItem.AddUObject(this, &UMS_ConstructExpanerWidget::OnClickedCategory);
	
	CPP_ExpanderItemListView->SetScrollbarVisibility(ESlateVisibility::Collapsed);

	RefreshConstructListItems(EMS_ZoneType::Display);
}

void UMS_ConstructExpanerWidget::InitCategory() const
{
	const TObjectPtr<UMS_FurnitureCacheTable> FurnitureTable = Cast<UMS_FurnitureCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::Furniture));
	TArray<TObjectPtr<UMS_ConstructCategoryElementData>> CategoryArray;
	FurnitureTable->GetFurnitureCategoryData(CategoryArray);
	
	CPP_ExpanderCategoryListView->SetListItems(TArray<TObjectPtr<UObject>>(CategoryArray));
	CPP_ExpanderCategoryListView->ClearSelection();
}

void UMS_ConstructExpanerWidget::RefreshConstructListItems(EMS_ZoneType aZoneType) const
{
	TMap<int32, int32> NotDeployFurnitures;
	gItemMng.GetNotDeployFurniture(NotDeployFurnitures);

	const TObjectPtr<UMS_FurnitureCacheTable> FurnitureTable = Cast<UMS_FurnitureCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::Furniture));
	MS_CHECK(FurnitureTable);
	TArray<TObjectPtr<UMS_ConstructItemElement>> FurnitureItems;
	for(const auto& NotDeployFurniture : NotDeployFurnitures)
	{
		if(NotDeployFurniture.Value < 0)
		{
			MS_ERROR(TEXT("[%s] There isn't Furniture at Shelf Furniture. Check Save Data.")
			, *MS_FUNC_STRING);
			// MS_ENSURE(false);
			continue;
		}
		if(NotDeployFurniture.Value == 0)
		{
			// 전부 배치가 되었을 때
			continue;
		}
		
		const FMS_FurnitureData* StorageData = FurnitureTable->GetFurnitureData(NotDeployFurniture.Key);
		
		if(StorageData->ZoneType != static_cast<int32>(aZoneType))
		{
			continue;
		}
		
		TObjectPtr<UMS_ConstructItemElement> ConstructItem = MS_NewObject<UMS_ConstructItemElement>();
		ConstructItem->SetElementName(StorageData->StandName.ToString());
		const FString ImagePath = gTableMng.GetPath(EMS_TableDataType::BasePathImgFile, StorageData->ImagePath); 
		if(UTexture2D* ImageImage = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *ImagePath)))
		{
			ConstructItem->SetImage(ImageImage);
		}
		ConstructItem->SetItemId(NotDeployFurniture.Key);
		ConstructItem->OnClickConstructItem.AddWeakLambda(this, [this]()
		{
			if(OnClickedConstructItemCallback)
			{
				OnClickedConstructItemCallback();
			}
		});
		FurnitureItems.Emplace(ConstructItem);
	}

	if(FurnitureItems.Num() == 0)
	{
		CPP_ItemExistSwitcher->SetActiveWidgetIndex(0);
	}
	else
	{
		CPP_ItemExistSwitcher->SetActiveWidgetIndex(1);
		CPP_ExpanderItemListView->SetListItems(FurnitureItems);	
	}
	CPP_ExpanderCategoryListView->SetSelectedIndex(static_cast<int32>(aZoneType) - 1);
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
		OnClickedCategoryButtonCallback(Data->GetZoneType());
	}	
}

void UMS_ConstructExpanerWidget::OnClickedCategory(int32 aCategoryType)
{
	RefreshConstructListItems(static_cast<EMS_ZoneType>(aCategoryType));
}
