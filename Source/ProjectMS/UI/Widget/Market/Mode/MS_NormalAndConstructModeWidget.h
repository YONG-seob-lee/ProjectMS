// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_ModeWidget.h"
#include "MS_NormalAndConstructModeWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_NormalAndConstructModeWidget : public UMS_ModeWidget
{
	GENERATED_BODY()
	
public:
	static FName GetWidgetName() { return TEXT("NormalAndConstruct"); }

	virtual void NativeOnInitialized() override;
	
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	void OnClickedRunButton();
	void OnClickedExitButton();
	
	virtual void OnChangeMode(EMS_ModeState aModeState) override;
	
private:
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_MarketExpanderWidget> CPP_ExpanderWidget;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_Button> CPP_RunButton;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_Button> CPP_ExitButton;
};
