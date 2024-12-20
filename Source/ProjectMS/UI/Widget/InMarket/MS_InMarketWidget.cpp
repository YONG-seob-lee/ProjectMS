#include "MS_InMarketWidget.h"

#include "MS_Define.h"
#include "MS_InMarketModeWidget.h"
#include "Manager_Both/MS_ModeManager.h"
#include "Widget/WidgetComponent/MS_WidgetSwitcher.h"


void UMS_InMarketWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	gModeMng.OnChangeModeDelegate.AddUObject(this, &UMS_InMarketWidget::OnChangeMode);
}

void UMS_InMarketWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	SetActiveModeSwitcherIndex(EMS_ModeState::Normal);
}

void UMS_InMarketWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UMS_InMarketWidget::OnChangeMode(EMS_ModeState aModeState, EMS_ControllerModeType aControllerModeType)
{
	SetActiveModeSwitcherIndex(aModeState);
}

void UMS_InMarketWidget::SetActiveModeSwitcherIndex(EMS_ModeState aModeState)
{
	if (CPP_ModeWidgetSwitcher)
	{
		if (int32* Id = ModeStateToWidgetSwitcherId.Find(aModeState))
		{
			CPP_ModeWidgetSwitcher->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			
			CPP_ModeWidgetSwitcher->SetActiveWidgetIndex(*Id);

			if (UWidget* Child = CPP_ModeWidgetSwitcher->GetChildAt(*Id))
			{
				if (UMS_InMarketModeWidget* ChildModeWidget = Cast<UMS_InMarketModeWidget>(Child))
				{
					ChildModeWidget->OnShow();
				}
			}
		}
		else
		{
			CPP_ModeWidgetSwitcher->SetVisibility(ESlateVisibility::Collapsed);

			MS_LOG_Verbosity(Warning, TEXT("No ModeState found in ModeStateToWidgetSwitcherId [ModeState : %d]"), static_cast<int32>(aModeState));
		}
	}
}
