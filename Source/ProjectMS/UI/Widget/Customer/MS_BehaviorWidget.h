// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_Define.h"
#include "Modal/MS_CustomerManagementWidget.h"
#include "Widget/MS_Widget.h"
#include "MS_BehaviorWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_BehaviorWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	void SetBehavior(MS_Handle aUnitHandle, EMS_PopulationNumber aPopulationNumber) const;
private:
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_WidgetSwitcher> CPP_BehaviorWidgetSwitcher = nullptr;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_BehaviorEntryWidget> CPP_BehaviorEntry = nullptr;
};
