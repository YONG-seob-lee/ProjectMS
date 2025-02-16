#include "MS_MarketWidget.h"

#include "MS_Define.h"
#include "Expander/MS_MarketExpanderWidget.h"
#include "Manager_Client/MS_ModeManager.h"
#include "Mode/MS_ModeWidget.h"
#include "Widget/WidgetComponent/MS_WidgetSwitcher.h"


void UMS_MarketWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	gModeMng.OnChangeModeDelegate.AddUObject(this, &UMS_MarketWidget::OnChangeMode);
}

void UMS_MarketWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	SetActiveModeSwitcherIndex(gModeMng.GetCurrentModeStateId());
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
	if (ModeStateToWidgetSwitcherId.Contains(aModeState))
	{
		CPP_ModeWidgetSwitcher->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		int32 Id = *ModeStateToWidgetSwitcherId.Find(aModeState);
		CPP_ModeWidgetSwitcher->SetActiveWidgetIndex(Id);

		UWidget* Widget = CPP_ModeWidgetSwitcher->GetActiveWidget();
		if (UMS_ModeWidget* ModeWidget = Cast<UMS_ModeWidget>(Widget))
		{
			ModeWidget->OnChangeMode(aModeState);
		}
	}
	else
	{
		CPP_ModeWidgetSwitcher->SetVisibility(ESlateVisibility::Collapsed);
	}
}
