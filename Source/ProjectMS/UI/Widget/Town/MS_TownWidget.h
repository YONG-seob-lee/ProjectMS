// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "ContentsUtilities/MS_GameProcessDefine.h"
#include "MS_TownWidget.generated.h"


namespace ModePanelAnimation
{
	const FName IdleMode = FName(TEXT("IdleMode"));
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

	virtual void NativeOnInitialized() override;
	
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	void OnUpdateGameDate(const FMS_GameDate& aGameDate);
	
private:
	void OnClickedSleepButton();
	

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UMS_TimeLineWidget> CPP_TimeLineWidget = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UMS_Button> CPP_SleepButton = nullptr;
};