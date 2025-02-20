// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_MenuListElementWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "ElementData/MS_MenuElementData.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "Widget/Market/Modal/MS_MarketOrderModalWidget.h"
#include "Widget/Market/Modal/MS_MarketOrderCheckModalWidget.h"
#include "Widget/System/Modal/MS_ModalWidget.h"

void UMS_MenuListElementWidget::NativeOnListItemObjectSet(UObject* aListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(aListItemObject);

	UMS_MenuElementData* ItemData = Cast<UMS_MenuElementData>(aListItemObject);
	MenuName = ItemData->GetElementName();
	CPP_MenuImage->SetBrushFromTexture(ItemData->GetImage());
	CPP_MenuName->SetText(FText::FromString(ItemData->GetElementName()));
}

FReply UMS_MenuListElementWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if(MenuName == TEXT("dollar"))
	{
		// FMS_ModalParameter ModalParameter;
		// ModalParameter.InModalWidget = gWidgetMng.Create_Widget_NotManaging(UMS_MarketOrderModalWidget::GetWidgetPath());
		// ModalParameter.bPlayOpenAnimation = true;
		// ModalParameter.bPlayCloseAnimation = true;
		// gWidgetMng.ShowModalWidget(ModalParameter);
	}
	else if(MenuName == TEXT("User"))
	{
		FMS_ModalParameter ModalParameter;
		ModalParameter.InModalWidget = gWidgetMng.Create_Widget_NotManaging(UMS_MarketOrderCheckModalWidget::GetWidgetPath());
		gWidgetMng.ShowModalWidget(ModalParameter);
	}

	if(const UMS_MenuElementData* MenuElementData = GetListItem<UMS_MenuElementData>())
	{
		MenuElementData->OnClickMenuElementDelegate.Broadcast();
	}
	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

void UMS_MenuListElementWidget::NativeOnItemSelectionChanged(bool bIsSelected)
{
	IUserObjectListEntry::NativeOnItemSelectionChanged(bIsSelected);
}
