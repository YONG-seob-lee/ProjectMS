// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "MS_DialogWidget.generated.h"

UENUM()
enum class EMS_DialogType
{
	Undefined = 0,
	Process = 1,
	Finished = 2,
};

struct FMS_DialogParameter
{
public:
	FMS_DialogParameter() {}
	FMS_DialogParameter(const FString& aTypeText, float aTypeSpeed);

	FString ShowType() const;
	FORCEINLINE FString ShowFullType() { return TypeText; }
	
	FORCEINLINE void AddProcess() { ProcessNumber++; }
	FORCEINLINE float GetTypeSpeed() const { return TypeSpeed; }
	FORCEINLINE void FinishDialogEvent() const { if(DialogEndCallback){ DialogEndCallback(); } }

	FORCEINLINE void SetDialogType(EMS_DialogType aType) { DialogType = aType; }
	FORCEINLINE EMS_DialogType GetDialogType() const { return DialogType; }

	FORCEINLINE void SetIsLeft(bool _bIsLeft) { bIsLeft = _bIsLeft; }
	FORCEINLINE bool IsLeft() const { return bIsLeft; }
	
	FORCEINLINE bool IsTypingEnd() const { return ProcessNumber >= TotalTypeNumber; }
	
	FORCEINLINE void SetDialogEndCallback(const TFunction<void()>& _Func) { DialogEndCallback = _Func; } 

private:
	EMS_DialogType DialogType = EMS_DialogType::Undefined;

	bool bIsLeft = true;
	FString TypeText = FString();
	float TypeSpeed = 1.f;
	int32 TotalTypeNumber = 0;
	int32 ProcessNumber = 0;

	TFunction<void()> DialogEndCallback = nullptr;
};
/**
 * 
 */
namespace DialogAnimation
{
	const FName Start = TEXT("StartDialog");
	const FName Close = TEXT("CloseDialog");
	const FName SkipAnimation = TEXT("SkipAnimation");
}

UCLASS()
class PROJECTMS_API UMS_DialogWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	static FName GetWidgetName() { return TEXT("Dialog"); }

	virtual void NativeConstruct() override;
	virtual void OnAnimFinished(const FName& aAnimName) override;

	void RequestDialog(const TArray<FMS_DialogParameter>& aDialogParameters);

private:
	void PlayTyping();
	void ProcessTyping();
	void FinishedTyping();

	void PlayPortrait(bool bIsLeft) const;
	void FinishedPortrait(bool bIsLeft) const;
	
	void OnClickedSkipButton();

	int32 ProcessingDialogNumber = INDEX_NONE;
	TArray<FMS_DialogParameter> DialogParameters;
	FTimerHandle DialogTextTimerHandler;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_DialogText = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_Button> CPP_SkipButton = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UCanvasPanel> CPP_SkipPanel = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_DialogPortraitWidget> CPP_LeftPortraitWidget = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_DialogPortraitWidget> CPP_RightPortraitWidget = nullptr;
};
