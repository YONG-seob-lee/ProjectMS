// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_StockElementWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "ElementData/MS_StockItemElementData.h"

void UMS_StockElementWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMS_StockElementWidget::NativeOnListItemObjectSet(UObject* aListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(aListItemObject);
	
	if(UMS_StockItemElementData* ItemData = Cast<UMS_StockItemElementData>(aListItemObject))
	{
		CPP_ItemImage->SetBrushFromTexture(ItemData->GetImage());
		
		CPP_ItemName->SetText(FText::FromString(FString::Format(TEXT("품목 : {0}"), {ItemData->GetItemName()})));

		const int32 ItemCount = ItemData->GetItemCount();
		CPP_ItemCount->SetText(FText::FromString(FString::Format(TEXT("수량 : \"{0}\" 개"), {ItemCount})));

		if(ItemCount == 0)
		{
			CPP_ItemName->SetColorAndOpacity(FLinearColor(0.1f, 0.1f, 0.1f));
			CPP_ItemCount->SetColorAndOpacity(FLinearColor(0.1f, 0.1f, 0.1f));
		}
		else
		{
			CPP_ItemName->SetColorAndOpacity(FLinearColor::White);
			CPP_ItemCount->SetColorAndOpacity(FLinearColor::White);
		}
	}
}

void UMS_StockElementWidget::NativeOnItemSelectionChanged(bool bIsSelected)
{
	IUserObjectListEntry::NativeOnItemSelectionChanged(bIsSelected);
}
