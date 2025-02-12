// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "MS_TimeLineWidget.generated.h"

namespace Sleep
{
	const FName Animation = TEXT("Sleep");
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
	
	void IsStartTimer(bool bStart);
	void UpdateTimer(int32 aMinute) const;

	void StartSleepButtonAnim();

	void RequestPassTimer();
	
private:
	void FlickerDot(bool bFlicker);
	void InVisibilityDot() const;
	
	void OnClickedSleepButton();

	void ProcessPassDayTimer(float InDeltaTime);
	
	FTimerHandle DotFlickerHandle;
	int32 SecondPerOneMinute = 0;
	
	bool bStartPassDayTimer = false;
	int32 PassDayTimerMinute = 0;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_Hour = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_Minute = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_Dot = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_Button> CPP_SleepButton = nullptr;
};
