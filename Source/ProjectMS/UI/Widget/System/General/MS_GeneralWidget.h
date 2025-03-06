// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Button/MS_GeneralButton.h"
#include "Widget/MS_Widget.h"
#include "MS_GeneralWidget.generated.h"

UENUM()
enum class EMS_GeneralWidgetType
{
	None = 0,
	Town,
	Market,
};

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_GeneralWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	
	void InitializeGeneralWidgetType();

private:
	void OnClickedLeftButton();
	void OnClickedRightButton();
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UCanvasPanel> CPP_LeftPanel = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UCanvasPanel> CPP_RightPanel = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_GeneralLeftExpanderWidget> CPP_LeftExpanderWidget = nullptr;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_GeneralRightExpanderWidget> CPP_RightExpanderWidget = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_GeneralButton> CPP_LeftButton = nullptr;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_GeneralButton> CPP_RightButton = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_MoneyWidget> CPP_MoneyWidget = nullptr;

	UPROPERTY(EditInstanceOnly, Category=MS_Widget)
	EMS_GeneralWidgetType GeneralWidgetType = EMS_GeneralWidgetType::None;
	
	EMS_GeneralButtonType LeftButtonType = EMS_GeneralButtonType::None;
	EMS_GeneralButtonType RightButtonType = EMS_GeneralButtonType::None;
};
