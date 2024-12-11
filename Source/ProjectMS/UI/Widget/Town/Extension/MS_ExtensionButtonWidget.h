// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_ModeManager.h"
#include "Widget/MS_Widget.h"
#include "MS_ExtensionButtonWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_ExtensionButtonWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	static FSoftObjectPath GetWidgetPath() { return FSoftObjectPath(TEXT("/Game/UI/Widget/Town/Extension/ExtensionButtonWidget.ExtensionButtonWidget")); }
	
	virtual void NativeConstruct() override;

	FORCEINLINE void SetModeType(EMS_ModeType aMode) { Mode = aMode; }
private:
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_Button> CPP_ExtensionButton = nullptr;

	EMS_ModeType Mode = EMS_ModeType::Normal;
};
