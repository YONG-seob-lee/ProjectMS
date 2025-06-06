﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "MS_MarketStartModal.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_MarketStartModal : public UMS_Widget
{
	GENERATED_BODY()
public:
	static FSoftObjectPath GetWidgetPath() { return FSoftObjectPath(TEXT("/Game/UI/Widget/Market/Modal/MarketStartModalWidget.MarketStartModalWidget"));}

	virtual void NativeConstruct() override;

private:
	void OnClickedOpeningPlayButton();
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_WorkStaffListWidget> CPP_WorkStaffListWidget = nullptr;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_OrderStatusWidget> CPP_OrderStatusWidget = nullptr;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_Button> CPP_OpeningPlayButton = nullptr;
};
