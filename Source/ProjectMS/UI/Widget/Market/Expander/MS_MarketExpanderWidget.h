// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager_Client/MS_ModeManager.h"
#include "Widget/MS_Widget.h"
#include "MS_MarketExpanderWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_MarketExpanderWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	virtual void NativeOnInitialized() override;
	
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	void OnChangeModeState(EMS_ModeState aModeState, EMS_ControllerModeType aControllerModeType);
	
	void OnClickedArrowButton();
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_ModeSelectWidget> CPP_ModeSelectWidget = nullptr;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_Button> CPP_ArrowButton = nullptr;

	bool bOpen = false;
};
