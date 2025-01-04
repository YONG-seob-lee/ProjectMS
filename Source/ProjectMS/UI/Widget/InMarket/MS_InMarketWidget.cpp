#include "MS_InMarketWidget.h"

#include "MS_Define.h"
#include "MS_InMarketModeWidget.h"
#include "MS_MarketExpanderWidget.h"
#include "Manager_Client/MS_ModeManager.h"
#include "Table/Caches/MS_StorageCacheTable.h"
#include "Widget/ListViewElement/ElementData/MS_ConstructCategoryElementData.h"
#include "Widget/ListViewElement/ElementData/MS_ConstructItemElement.h"
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

	CPP_ExpanderWidget->SetVisibility(ESlateVisibility::Visible);
	
	TArray<TObjectPtr<UMS_ConstructItemElement>> ConstructItemElements;
	const TObjectPtr<UMS_StorageCacheTable> StorageTable = Cast<UMS_StorageCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::Storage));
	StorageTable->GetStorageData(ConstructItemElements);
	
	if(CPP_ExpanderWidget)
	{
		for(int32 i = 0 ; i < 10 ; i++)
		{
			UMS_ConstructCategoryElementData* Data = MS_NewObject<UMS_ConstructCategoryElementData>(this);
			Data->SetElementName(FText::Format(FText::FromString(TEXT("건설목록\'{0}\'")), i).ToString());
			ConstructCategoryElements.Emplace(Data);
		}
		
		CPP_ExpanderWidget->SetListItems(ConstructCategoryElements, ConstructItemElements);
	}
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
