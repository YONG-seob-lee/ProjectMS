// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameUserSettings/MS_GameUserSettings.h"
#include "Widget/MS_Widget.h"
#include "MS_TiltSettingWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_TiltSettingWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	UFUNCTION()
	virtual void NativeConstruct() override;
	
private:
	UFUNCTION()
	void OnCheckVVLow(bool bIsChecked);
	UFUNCTION()
	void OnCheckVeryLow(bool bIsChecked);
	UFUNCTION()
	void OnCheckLow(bool bIsChecked);
	UFUNCTION()
	void OnCheckDefault(bool bIsChecked);
	UFUNCTION()
	void OnCheckHigh(bool bIsChecked);
	UFUNCTION()
	void OnCheckVeryHigh(bool bIsChecked);
	UFUNCTION()
	void OnCheckVVHigh(bool bIsChecked);

	void RefreshCheckBoxes();

	EMS_TiltType TargetTileType = EMS_TiltType::Default;
	TMap<EMS_TiltType, TObjectPtr<class UCheckBox>> CheckBoxes = {};
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UCheckBox> CPP_VVLow = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UCheckBox> CPP_VeryLow = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UCheckBox> CPP_Low = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UCheckBox> CPP_Default = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UCheckBox> CPP_High = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UCheckBox> CPP_VeryHigh = nullptr;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UCheckBox> CPP_VVHigh = nullptr;
};
