// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "MS_DescriptionWidget.generated.h"

namespace DescAnim
{
	const FName StartUpToRight = TEXT("Start_UpToRight");
	const FName StopUpToRight = TEXT("Stop_UpToRight");
	const FName DotAnimation_UpToRight = TEXT("DotAnimation_UpToRight");

	const FName StartDownToRight = TEXT("Start_DownToRight");
	const FName StopDownToRight = TEXT("Stop_DownToRight");
	const FName DotAnimation_DownToRight = TEXT("DotAnimation_DownToRight");
}

UENUM()
enum class EMS_TutorialDirection
{
	UpToRight = 1,
	DownToRight = 2,
	UpToLeft = 3,
	DownToLeft = 4
};


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

	void Start(EMS_TutorialDirection aDirection, const FString& Desc, const FString& SubDesc);
	void Stop();

private:
	void PlayDescription(EMS_TutorialDirection aDirection);

	EMS_TutorialDirection TargetDirection = EMS_TutorialDirection::UpToRight; 
	TFunction<void()> OnFinishedTutorialCallback = nullptr;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_Desc = nullptr;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_SubDesc = nullptr;
};
