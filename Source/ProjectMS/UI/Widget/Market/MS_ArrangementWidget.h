// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "MS_ArrangementWidget.generated.h"

/**
 * 
 */
DECLARE_DELEGATE_OneParam(FMS_OnClickApplyButtonDelegate, UMS_ArrangementWidget*);
DECLARE_DELEGATE_OneParam(FMS_OnClickCancelButtonDelegate, UMS_ArrangementWidget*);
DECLARE_DELEGATE_OneParam(FMS_OnClickRotateButtonDelegate, UMS_ArrangementWidget*);

UCLASS()
class PROJECTMS_API UMS_ArrangementWidget : public UMS_Widget
{
	GENERATED_BODY()


public:
	virtual void NativeOnInitialized() override;
	
	void OnClickApplyButton();
	void OnClickCancelButton();
	void OnClickRotateButton();

	
protected:
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_Button> CPP_ApplyButton = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_Button> CPP_CancelButton = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_Button> CPP_RotateButton = nullptr;

	
public:
	FMS_OnClickApplyButtonDelegate OnClickApplyButtonDelegate;
	FMS_OnClickCancelButtonDelegate OnClickCancelButtonDelegate;
	FMS_OnClickRotateButtonDelegate OnClickRotateButtonDelegate;
};
