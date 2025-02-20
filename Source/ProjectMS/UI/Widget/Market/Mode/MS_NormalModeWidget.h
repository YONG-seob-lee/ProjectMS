// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_ModeWidget.h"
#include "MS_NormalModeWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_NormalModeWidget : public UMS_ModeWidget
{
	GENERATED_BODY()

public:
	static FName GetWidgetName() { return TEXT("NormalMode"); }

	virtual void NativeOnInitialized() override;
	
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	
	
	virtual void OnChangeMode(EMS_ModeState aModeState) override;
	
private:
	void OnClickedTownButton();
	void OnClickedConstructButton();
	void OnClickedOpenMarket();
	void OnClickedCloseMarket();
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_Button> CPP_TownButton;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_Button> CPP_ConstructButton;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_WidgetSwitcher> CPP_PlayButtonSwitcher;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_Button> CPP_OpenButton;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_Button> CPP_CloseButton;
};
