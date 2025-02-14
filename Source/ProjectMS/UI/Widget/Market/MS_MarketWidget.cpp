#include "MS_MarketWidget.h"

#include "MS_Define.h"
#include "Expander/MS_MarketExpanderWidget.h"
#include "Manager_Client/MS_ModeManager.h"
#include "Widget/WidgetComponent/MS_WidgetSwitcher.h"


void UMS_MarketWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	gModeMng.OnChangeModeDelegate.AddUObject(this, &UMS_MarketWidget::OnChangeMode);
}

void UMS_MarketWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	SetActiveModeSwitcherIndex(EMS_ModeState::Normal);

	CPP_ExpanderWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

	if(gModeMng.GetCurrentModeStateId() == EMS_ModeState::RunMarket)
	{
		SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		SetVisibility(ESlateVisibility::Visible);
	}
}

void UMS_MarketWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UMS_MarketWidget::OnChangeMode(EMS_ModeState aModeState, EMS_ControllerModeType aControllerModeType)
{
	if(aModeState == EMS_ModeState::RunMarket)
	{
		SetVisibility(ESlateVisibility::Collapsed);
	}
	else if(aModeState == EMS_ModeState::Construct)
	{
		SetVisibility(ESlateVisibility::Visible);
	}
	SetActiveModeSwitcherIndex(aModeState);
}

void UMS_MarketWidget::SetActiveModeSwitcherIndex(EMS_ModeState aModeState)
{
	// if (CPP_ModeWidgetSwitcher)
	// {
	// 	if (int32* Id = ModeStateToWidgetSwitcherId.Find(aModeState))
	// 	{
	// 		CPP_ModeWidgetSwitcher->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	// 		
	// 		CPP_ModeWidgetSwitcher->SetActiveWidgetIndex(*Id);
	//
	// 		if (UWidget* Child = CPP_ModeWidgetSwitcher->GetChildAt(*Id))
	// 		{
	// 			if (UMS_InMarketModeWidget* ChildModeWidget = Cast<UMS_InMarketModeWidget>(Child))
	// 			{
	// 				ChildModeWidget->OnShow();
	// 			}
	// 		}
	// 	}
	// 	else
	// 	{
	// 		CPP_ModeWidgetSwitcher->SetVisibility(ESlateVisibility::Collapsed);
	//
	// 		MS_LOG_Verbosity(Warning, TEXT("No ModeState found in ModeStateToWidgetSwitcherId [ModeState : %d]"), static_cast<int32>(aModeState));
	// 	}
	// }
}
