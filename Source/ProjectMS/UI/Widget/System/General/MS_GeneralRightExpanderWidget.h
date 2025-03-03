// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "MS_GeneralRightExpanderWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_GeneralRightExpanderWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	void UpdateButton() const;
private:
	void OnClickedGotoButton();
	void OnClickedCheckOrderButton();
	void OnClickedManageStaffButton();
	void OnClickedFinancialIndicatorButton();
	void OnClickedSettingButton();

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_GeneralButton> CPP_GoToMarketorTownButton = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_GeneralButton> CPP_CheckOrderItemButton = nullptr;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_GeneralButton> CPP_StaffManageButton = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_GeneralButton> CPP_SalesDetailButton = nullptr;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_GeneralButton> CPP_SettingButton = nullptr;
};
