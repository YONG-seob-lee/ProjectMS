// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_OrderElementWidget.h"

#include "Button/MS_Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "ElementData/MS_OrderItemElementData.h"

void UMS_OrderElementWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(CPP_CountUpButton)
	{
		CPP_CountUpButton->GetOnClickedDelegate().AddUObject(this, &UMS_OrderElementWidget::OnClickedCountButton, 1);
	}

	if(CPP_CountDownButton)
	{
		CPP_CountDownButton->GetOnClickedDelegate().AddUObject(this, &UMS_OrderElementWidget::OnClickedCountButton, -1);
	}
}

void UMS_OrderElementWidget::NativeOnListItemObjectSet(UObject* aListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(aListItemObject);
	
	if(UMS_OrderItemElementData* ItemData = Cast<UMS_OrderItemElementData>(aListItemObject))
	{
		CPP_ItemImage->SetBrushFromTexture(ItemData->GetImage());
		
		CPP_ItemName->SetText(FText::FromString(FString::Format(TEXT("품목 : {0}"), {ItemData->GetItemName()})));
		CPP_ItemPrice->SetText(FText::FromString(FString::Format(TEXT("가격 : {0}Gold"), {ItemData->GetItemPrice()})));
		CPP_ItemCount->SetText(FText::FromString(FString::Format(TEXT("수량 : \"{0}\" 개"), {ItemData->GetItemCount()})));
	}
}

void UMS_OrderElementWidget::NativeOnItemSelectionChanged(bool bIsSelected)
{
	IUserObjectListEntry::NativeOnItemSelectionChanged(bIsSelected);
}

void UMS_OrderElementWidget::OnClickedCountButton(int32 aCount)
{
	if(ItemCheckedCount == 0 && aCount < ItemCheckedCount)
	{
		return;
	}
	ItemCheckedCount += aCount;
	CPP_ItemCount->SetText(FText::FromString(FString::Format(TEXT("수량 : \"{0}\" 개"), {ItemCheckedCount})));

	if(const UMS_OrderItemElementData* OrderElement = GetListItem<UMS_OrderItemElementData>())
	{
		OrderElement->OnClickCountDelegate.Broadcast(ItemCheckedCount);
	}
}
