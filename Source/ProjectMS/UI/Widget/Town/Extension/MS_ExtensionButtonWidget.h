// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	virtual void NativeConstruct() override;

private:
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_Button> CPP_ExtensionButton = nullptr;
};
