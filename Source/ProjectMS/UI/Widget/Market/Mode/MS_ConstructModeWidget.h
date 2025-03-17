// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_ModeWidget.h"
#include "ContentsUtilities/MS_GameProcessDefine.h"
#include "MS_ConstructModeWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_ConstructModeWidget : public UMS_ModeWidget
{
	GENERATED_BODY()

public:
	static FName GetWidgetName() { return TEXT("ConstructMode"); }

	virtual void NativeOnInitialized() override;
	
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	
	void OnClickedExitButton();
	
	virtual void OnChangeMode(EMS_ModeState aModeState) override;

	void OnCloseArrow() const;
	
private:
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_MarketExpanderWidget> CPP_ExpanderWidget;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_Button> CPP_ExitButton;
};
