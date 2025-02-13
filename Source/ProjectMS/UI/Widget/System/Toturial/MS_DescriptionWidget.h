// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "MS_DescriptionWidget.generated.h"

namespace DescAnim
{
	const FName StartTutorial = TEXT("StartTutorial");
	const FName StopTutorial = TEXT("StopTutorial");
	const FName DotAnimation = TEXT("DotAnimation");
}

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_DescriptionWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void OnAnimFinished(const FName& aAnimName) override;

	FORCEINLINE void SetOnFinishedTutorialFunc(const TFunction<void()>& aFunc) { OnFinishedTutorialCallback = aFunc; }
	
	void Start(const FString& Desc, const FString& SubDesc);
	void Stop();

private:
	TFunction<void()> OnFinishedTutorialCallback = nullptr;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_Desc = nullptr;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_SubDesc = nullptr;
};
