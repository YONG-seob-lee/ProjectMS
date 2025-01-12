#include "MS_MarketWidget.h"

#include "MS_Define.h"
#include "MS_MarketModeWidget.h"
#include "MS_MarketExpanderWidget.h"
#include "Manager_Client/MS_ModeManager.h"
#include "Table/Caches/MS_StorageCacheTable.h"
#include "Widget/ListViewElement/ElementData/MS_ConstructCategoryElementData.h"
#include "Widget/ListViewElement/ElementData/MS_ConstructItemElement.h"
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
}

void UMS_MarketWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UMS_MarketWidget::OnChangeMode(EMS_ModeState aModeState, EMS_ControllerModeType aControllerModeType)
{
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
