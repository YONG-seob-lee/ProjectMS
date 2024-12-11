// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "MS_TownWidget.generated.h"

namespace ModePanelAnimation
{
	const FName SetMode = FName(TEXT("SetMode"));
	const FName UnSetMode = FName(TEXT("UnSetMode"));
}
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

	virtual void OnAnimFinished(const FName& aAnimName) override;
private:
	void OnClickedDefaultButton();
	void OnSetMode(uint8 aMode);
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_ContentsPartWidget> CPP_ContentsPart = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_SettingButtonWidget> CPP_SettingButton = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_ManagerButtonWidget> CPP_ManagerButton = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_ModeNameWidget> CPP_ModeName = nullptr;

	FTimerHandle OnSetTimerHandle;
	bool IsShowModePanel = false;
};