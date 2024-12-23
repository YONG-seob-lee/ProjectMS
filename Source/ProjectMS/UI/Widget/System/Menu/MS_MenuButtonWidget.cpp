// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_MenuButtonWidget.h"

#include "Button/MS_Button.h"
#include "Components/CanvasPanel.h"
#include "Manager_Both/MS_TableManager.h"
#include "..\..\..\..\Data\Table\Caches\MS_MenuElementCacheTable.h"
#include "Widget/ListViewElement/MS_MenuListElementWidget.h"
#include "Widget/ListViewElement/ElementData/MS_MenuElementData.h"
#include "Widget/WidgetComponent/MS_TileView.h"

void UMS_MenuButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if(CPP_MenuButton)
	{
		CPP_MenuButton->GetOnClickedDelegate().AddUObject(this, &UMS_MenuButtonWidget::OnClickSettingButton);
	}

	CPP_MenuExpanderPanel->SetVisibility(ESlateVisibility::Collapsed);

	if(CPP_MenuList)
	{
		const TObjectPtr<UMS_MenuElementCacheTable> MenuElement = Cast<UMS_MenuElementCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::MenuElement));
		MS_CHECK(MenuElement);

		TArray<TObjectPtr<UMS_MenuElementData>> Elements;
		MenuElement->GetMenuData(Elements);
		CPP_MenuList->SetListItems(TArray<UObject*>(Elements));
	}
}

void UMS_MenuButtonWidget::OnClickSettingButton()
{
	if(CPP_MenuExpanderPanel->IsVisible())
	{
		CPP_MenuExpanderPanel->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		CPP_MenuExpanderPanel->SetVisibility(ESlateVisibility::Visible);
	}
}
