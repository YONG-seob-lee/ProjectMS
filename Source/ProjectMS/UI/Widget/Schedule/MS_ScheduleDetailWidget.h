// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "MS_ScheduleDetailWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_ScheduleDetailWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	static FName GetWidgetName() { return TEXT("ScheduleDetail"); }
	virtual void InitWidget(const FName& aTypeName, bool bManaged, bool bAttachToRoot) override;

	void SetDay(int32 aDay) const;
private:
	void OnClickedBlankButton();
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_Button> CPP_SkipButton = nullptr;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_FinancialIndicator = nullptr;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_FinancialDetailWidget> CPP_FinancialDetailWidget = nullptr;
};
