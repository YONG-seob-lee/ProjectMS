// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "MS_ZoneOpenWidget.generated.h"

/**
 * 
 */
DECLARE_DELEGATE_OneParam(FMS_OnClickZoneOpenButtonDelegate, UMS_ZoneOpenWidget*);

UCLASS()
class PROJECTMS_API UMS_ZoneOpenWidget : public UMS_Widget
{
	GENERATED_BODY()


public:
	virtual void NativeOnInitialized() override;
	
	void OnClickZoneOpenButton();

	
protected:
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_Button> CPP_ZoneOpenButton = nullptr;

	
public:
	FMS_OnClickZoneOpenButtonDelegate OnClickZoneOpenButtonDelegate;
};
