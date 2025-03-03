// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "MS_MenuButtonWidget.generated.h"


/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_MenuButtonWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

private:
	void OnClickSettingButton();
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_Button> CPP_MenuButton = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UCanvasPanel> CPP_MenuExpanderPanel = nullptr;
};
