// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "MS_ScheduleModalWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_ScheduleModalWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	static FName GetWidgetName() { return TEXT("Schedule"); }
	virtual void InitWidget(const FName& aTypeName, bool bManaged, bool bAttachToRoot) override;
	
private:
	void SetMonth(int32 aMonth) const;
	void OnClickedChangeMonthButton(int32 aChangeMonthProperty);

	int32 Month = 0;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_MonthScheduleText = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_Button> CPP_MonthChangeLeftButton = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_Button> CPP_MonthChangeRightButton = nullptr;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_TileView> CPP_DaysTileView = nullptr;
};
