// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Modal/MS_CustomerManagementWidget.h"
#include "Widget/MS_Widget.h"
#include "MS_CustomerDetailWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_CustomerDetailWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	FORCEINLINE void InitPersonHandle(MS_Handle aUnitHandle) { PersonUnitHandle = aUnitHandle; }
	void SetType(EMS_PopulationNumber aPopulationNumber, EMS_CustomerDetailType aDetailType) const;

private:
	void ResetActivateButton() const;

	MS_Handle PersonUnitHandle = INDEX_NONE;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_CustomerButton> CPP_ChatButton = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_CustomerButton> CPP_BehaviorButton = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_CustomerButton> CPP_PurchaseButton = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_WidgetSwitcher> CPP_DetailWidgetSwitcher = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_ChatWidget> CPP_ChatWidget = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_BehaviorWidget> CPP_BehaviorWidget = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_PurchaseWidget> CPP_PurchaseWidget = nullptr;
};
