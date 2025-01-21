// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "CustomerDetailWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UCustomerDetailWidget : public UMS_Widget
{
	GENERATED_BODY()
public:

private:
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_CustomerButton> CPP_ChatButton = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_CustomerButton> CPP_BehaviorButton = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_CustomerButton> CPP_PurchaseButton = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_WidgetSwitcher> CPP_DetailWidgetSwitcher = nullptr;
};
