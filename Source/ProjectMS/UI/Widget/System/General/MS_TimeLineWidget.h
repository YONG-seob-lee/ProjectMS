// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "MS_TimeLineWidget.generated.h"

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
	
	void IsStartTimer(bool bStart);
	void UpdateTimer(int32 aMinute) const;

private:
	void FlickerDot(bool bFlicker);
	void InVisibilityDot() const;
	
	FTimerHandle DotFlickerHandle;
	int32 SecondPerOneMinute = 0;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_Hour = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_Minute = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_Dot = nullptr;
};
