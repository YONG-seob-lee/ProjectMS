// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ModeSelectWidget.h"

#include "Button/MS_Button.h"
#include "Widget/ListViewElement/ElementData/MS_ConstructCategoryElementData.h"
#include "Widget/ListViewElement/ElementData/MS_ConstructItemElement.h"
#include "Widget/WidgetComponent/MS_TileView.h"
#include "Widget/WidgetComponent/MS_WidgetSwitcher.h"

void UMS_ModeSelectWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CPP_ModeButton01->GetOnClickedDelegate().AddUObject(this, &UMS_ModeSelectWidget::OnClickModeButton, EMS_ModeState::Construct);

	CPP_ConstructCategoryTileView->SetScrollbarVisibility(ESlateVisibility::Collapsed);
	CPP_ConstructItemTileView->SetScrollbarVisibility(ESlateVisibility::Collapsed);
}

void UMS_ModeSelectWidget::SetConstructListItems(const TArray<TObjectPtr<UMS_ConstructCategoryElementData>>& aConstructCategoryElements, const TArray<TObjectPtr<UMS_ConstructItemElement>>& aConstructItemElements) const
{
	if(CPP_ConstructCategoryTileView)
	{
		CPP_ConstructCategoryTileView->SetListItems(aConstructCategoryElements);
	}

	if(CPP_ConstructItemTileView)
	{
		CPP_ConstructItemTileView->SetListItems(aConstructItemElements);
	}
}


void UMS_ModeSelectWidget::SwitchWidget(EMS_ModeState aModeState) const
{
	CPP_WidgetSwitcher->SetActiveWidgetIndex(static_cast<int32>(aModeState));
}

void UMS_ModeSelectWidget::OnClickModeButton(EMS_ModeState aModeState)
{
	if(OnClickedModeButtonCallback)
	{
		OnClickedModeButtonCallback(aModeState);
	}
}
