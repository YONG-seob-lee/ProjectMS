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
	virtual void NativeConstruct() override;
	
	FORCEINLINE void InitPersonHandle(MS_Handle aUnitHandle) { PersonUnitHandle = aUnitHandle; }
	FORCEINLINE void SetOnUpdateCustomerDetailTypeFunc(const TFunction<void(EMS_CustomerDetailType)>& aFunc) { OnUpdateCustomerDetailTypeCallback = aFunc; }
	
	void SetType(EMS_PopulationNumber aPopulationNumber, EMS_CustomerDetailType aDetailType);

private:
	void ResetActivateCustomerDetailButton() const;

	void OnClickedDetailButton(EMS_CustomerDetailType aCustomerDetailButtonType);
	
	MS_Handle PersonUnitHandle = INDEX_NONE;
	EMS_PopulationNumber PopulationNumber = EMS_PopulationNumber::One;
	EMS_CustomerDetailType CustomerDetailType = EMS_CustomerDetailType::Chatting;

	TFunction<void(EMS_CustomerDetailType)> OnUpdateCustomerDetailTypeCallback = nullptr;;
	
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
