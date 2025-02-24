// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "MS_DialogPortraitWidget.generated.h"

UENUM()
enum class EMS_MouseType
{
	e = 0,
	o
};
/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_DialogPortraitWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	void PlayMouse();
	void StopMouse();
	
protected:
	void ChangeMouse() const;
	
	FTimerHandle MouseTimeHandle;
	
private:
	EMS_MouseType CurrentMouseType = EMS_MouseType::e;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_WidgetSwitcher> CPP_MouseSwitcher = nullptr;
};
