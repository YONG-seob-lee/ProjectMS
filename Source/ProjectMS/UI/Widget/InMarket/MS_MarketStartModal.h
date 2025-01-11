// Fill out your copyright notice in the Description page of Project Settings.

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
	static FSoftObjectPath GetWidgetPath() { return FSoftObjectPath(TEXT("/Game/UI/Widget/Market/MarketStartModalWidget.MarketStartModalWidget"));}

	FORCEINLINE void SetOnClickedOpeningPlayButtonFunc(const TFunction<void()>& aFunc) { OnClickedOpeningPlayButtonCallback = aFunc; }
	FORCEINLINE void SetTest(const TFunction<void()>& aFunc) { Test = aFunc; }	
	virtual void NativeConstruct() override;

private:
	void OnClickedOpeningPlayButton();
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_Button> CPP_OpeningPlayButton = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_Button> CPP_FastButton = nullptr;
	
	TFunction<void()> OnClickedOpeningPlayButtonCallback = nullptr;
	TFunction<void()> Test = nullptr;
};
