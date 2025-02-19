// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "MS_MarketExpanderWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_MarketExpanderWidget : public UMS_Widget
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnInitialized() override;
	
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	
	void OpenExpander();

private:
	void OnClickedArrowButton();
	

private:
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_ConstructExpanerWidget> CPP_ConstructExpanderWidget = nullptr;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_Button> CPP_ArrowButton = nullptr;

	bool bOpen = false;
	bool bOpenExpander = false;
};
