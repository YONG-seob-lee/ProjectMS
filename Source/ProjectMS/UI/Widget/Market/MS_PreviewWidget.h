// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "MS_PreviewWidget.generated.h"

/**
 * 
 */
DECLARE_DELEGATE_OneParam(FOnClickApplyButtonDelegate, UMS_PreviewWidget*);
DECLARE_DELEGATE_OneParam(FOnClickCancelButtonDelegate, UMS_PreviewWidget*);

UCLASS()
class PROJECTMS_API UMS_PreviewWidget : public UMS_Widget
{
	GENERATED_BODY()


public:
	void NativeOnInitialized() override;
	
	void OnClickApplyButton();
	void OnClickCancelButton();
	
protected:
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_Button> CPP_ApplyButton = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_Button> CPP_CancelButton = nullptr;

public:
	FOnClickApplyButtonDelegate OnClickApplyButtonDelegate;
	FOnClickCancelButtonDelegate OnClickCancelButtonDelegate;
};
