// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "MS_TownWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_TownWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	static FName GetWidgetName() { return TEXT("Town"); }
	virtual void NativeConstruct() override;

private:
	void OnClickedDefaultButton();
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_ContentsPartWidget> CPP_ContentsPartWidget = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_SettingButtonWidget> CPP_SettingButton = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_ManagerButtonWidget> CPP_ManagerButton = nullptr;
};
