// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ConstructCategoryElementWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "ElementData/MS_ConstructCategoryElementData.h"
#include "Widget/WidgetComponent/MS_TileView.h"

void UMS_ConstructCategoryElementWidget::NativeOnListItemObjectSet(UObject* aListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(aListItemObject);

	const UMS_ConstructCategoryElementData* ItemData = Cast<UMS_ConstructCategoryElementData>(aListItemObject);
	StorageType = ItemData->GetStorageType();
	CPP_CategoryImage->SetColorAndOpacity(FLinearColor::Gray);
	
	switch(static_cast<EMS_StorageType>(StorageType))
	{
	case EMS_StorageType::Display:
		{
			CPP_CategoryImage->SetColorAndOpacity(FLinearColor::White);
			CPP_CategoryName->SetText(FText::FromString(TEXT("Display")));
			break;
		}
	case EMS_StorageType::Shelf:
		{
			CPP_CategoryName->SetText(FText::FromString(TEXT("Shelf")));
			break;
		}
	case EMS_StorageType::Pallet:
		{
			CPP_CategoryName->SetText(FText::FromString(TEXT("Pallet")));
			break;
		}
		default:
		{
			break;
		}
	}
}

void UMS_ConstructCategoryElementWidget::NativeOnItemSelectionChanged(bool bIsSelected)
{
	IUserObjectListEntry::NativeOnItemSelectionChanged(bIsSelected);

	if(bIsSelected)
	{
		CPP_CategoryImage->SetColorAndOpacity(FLinearColor::White);
		gItemMng.OnClickedTileViewItem.Broadcast(StorageType);
	}
	else
	{
		CPP_CategoryImage->SetColorAndOpacity(FLinearColor::Gray);
	}
}