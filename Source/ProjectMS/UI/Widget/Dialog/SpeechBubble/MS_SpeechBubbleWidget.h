// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "MS_SpeechBubbleWidget.generated.h"

UENUM()
enum class EMS_SpeechImageType
{
	None = 0,
	PutDownItems = 1,
	Pay = 2,
};

namespace SpeechImagePath
{
	const FString PutDownItems = TEXT("/Game/UI/Image/Icon/PutDownItems.PutDownItems");
	const FString Pay = TEXT("/Game/UI/Image/Icon/Pay.Pay");
}

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_SpeechBubbleWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	
	void SetText(const FText& SpeechString) const;
	void SetImage(EMS_SpeechImageType aSpeechImageType) const;

	virtual void OnAnimationStarted_Implementation(const UWidgetAnimation* Animation) override;
	virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;

	FORCEINLINE void SetOnFinishedSpeechFunc(const TFunction<void()>& _Func) { OnFinishedSpeechCallback = _Func; }
	void PlaySpeech();

	bool bIsConstructed = false;
private:
	TFunction<void()> OnFinishedSpeechCallback = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_WidgetSwitcher> CPP_SpeechSwitcher = nullptr;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_Speech = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UImage> CPP_Image = nullptr;
	
	UPROPERTY(Meta = (BindWidgetAnim), Transient)
	TObjectPtr<class UWidgetAnimation> SpeechBubbleStart = nullptr;

	UPROPERTY(Meta = (BindWidgetAnim), Transient)
	TObjectPtr<class UWidgetAnimation> SpeechBubbleIdle = nullptr;

	UPROPERTY(Meta = (BindWidgetAnim), Transient)
	TObjectPtr<class UWidgetAnimation> SpeechBubbleEnd = nullptr;
};
