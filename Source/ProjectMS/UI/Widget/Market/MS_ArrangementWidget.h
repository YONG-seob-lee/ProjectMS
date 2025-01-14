// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "MS_ArrangementWidget.generated.h"

/**
 * 
 */
DECLARE_DELEGATE_OneParam(FOnClickApplyButtonDelegate, UMS_ArrangementWidget*);
DECLARE_DELEGATE_OneParam(FOnClickCancelButtonDelegate, UMS_ArrangementWidget*);

UCLASS()
class PROJECTMS_API UMS_ArrangementWidget : public UMS_Widget
{
	GENERATED_BODY()


public:
	virtual void NativeOnInitialized() override;
	
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
