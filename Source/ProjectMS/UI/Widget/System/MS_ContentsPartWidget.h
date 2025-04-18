﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "MS_ContentsPartWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_ContentsPartWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	FORCEINLINE void SetOnClickMarketButtonFunc(const TFunction<void()>& aFunc) { OnClickMarketButtonCallback = aFunc; }
private:
	void OnClickMarketButton();
	void OnClickHamburgerButton(TObjectPtr<class UMS_ContentButtonWidget> aCommandModeButton);
	void OnClickModalButton();
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_HorizontalBox> CPP_HorizontalBox = nullptr;

	TFunction<void()> OnClickMarketButtonCallback = nullptr;
};
