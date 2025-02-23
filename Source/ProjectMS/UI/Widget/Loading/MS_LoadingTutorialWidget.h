// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "MS_LoadingTutorialWidget.generated.h"

UENUM()
enum class EMS_LoadingTutorial
{
	Loading_Tutorial_First = 0,
	Loading_Tutorial_01,
	Loading_Tutorial_02,
	Loading_Tutorial_03,
	Loading_Tutorial_04,
	Loading_Tutorial_05,
	Loading_Tutorial_06,
	Loading_Tutorial_07,
	Loading_Tutorial_08,
	Loading_Tutorial_09,
	Loading_Tutorial_10,
	Loading_Tutorial_11,
	Loading_Tutorial_12,
	Loading_Tutorial_Last,
};

namespace TutorialAnimation
{
	const FName Play = TEXT("PlayTutorial");
}
/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_LoadingTutorialWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void OnAnimFinished(const FName& aAnimName) override;
	
	void SetTutorial();
	
private:
	FString GetRandomTutorial();
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_TutorialText = nullptr;
};
