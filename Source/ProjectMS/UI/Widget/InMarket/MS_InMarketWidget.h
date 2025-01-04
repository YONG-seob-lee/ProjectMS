

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "MS_InMarketWidget.generated.h"

/**
 * 
 */
enum class EMS_ModeState : uint8;
enum class EMS_ControllerModeType : uint8;

UCLASS()
class PROJECTMS_API UMS_InMarketWidget : public UMS_Widget
{
	GENERATED_BODY()

public:
	static FName GetWidgetName() { return TEXT("Market"); }

	virtual void NativeOnInitialized() override;
	
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	virtual void OnChangeMode(EMS_ModeState aModeState, EMS_ControllerModeType aControllerModeType);

private:
	void SetActiveModeSwitcherIndex(EMS_ModeState aModeState);

	
private:
	UPROPERTY(EditDefaultsOnly)
	TMap<EMS_ModeState, int32> ModeStateToWidgetSwitcherId;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_MarketExpanderWidget> CPP_ExpanderWidget;

	// 일단 임시
	UPROPERTY()
	TArray<TObjectPtr<class UMS_ConstructCategoryElementData>> ConstructCategoryElements;
};
