// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "MS_MarketEndModal.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_MarketEndModal : public UMS_Widget
{
	GENERATED_BODY()
public:
	static FSoftObjectPath GetWidgetPath() { return FSoftObjectPath(TEXT("/Game/UI/Widget/Market/Modal/MarketEndModalWidget.MarketEndModalWidget"));}

	FORCEINLINE void SetOnClickedOpeningPlayButtonFunc(const TFunction<void()>& aFunc) { OnClickedOpeningPlayButtonCallback = aFunc; }
	
	virtual void NativeConstruct() override;

private:
	void OnClickedClosingPlayButton();
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_Button> CPP_ClosingPlayButton = nullptr;
	
	TFunction<void()> OnClickedOpeningPlayButtonCallback = nullptr;
};
