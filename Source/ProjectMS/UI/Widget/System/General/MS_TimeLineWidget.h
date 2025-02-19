// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "ContentsUtilities/MS_GameProcessDefine.h"
#include "MS_TimeLineWidget.generated.h"

namespace RunTime
{
	const FName Animation = TEXT("RunTime");
}
/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_TimeLineWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void UpdateGameDate(const FMS_GameDate& aGameDate);

	void UpdateTimer(int32 aMinute) const;

	void StartRunTimeButtonAnim();
	void StopRunTimeButtonAnim();

	void StopRuntimeButton();
	
private:
	void FlickerDot(bool bFlicker);
	void InVisibilityDot() const;
	
	void OnClickedRunTimeButton();

private:
	FTimerHandle DotFlickerHandle;
	int32 SecondPerOneMinute = 0;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_Day = nullptr;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_Hour = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_Minute = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_Dot = nullptr;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_Button> CPP_RunTimeButton = nullptr;
};
