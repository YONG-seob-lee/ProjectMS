

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
	static FName GetWidgetName() { return TEXT("InMarket"); }

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
	TObjectPtr<class UMS_WidgetSwitcher> CPP_ModeWidgetSwitcher = nullptr;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_InMarketNormalWidget> CPP_NormalModeWidet = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_InMarketConstructWidget> CPP_ConstructModeWidet = nullptr;
};
