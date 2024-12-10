// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "Widget/MS_Widget.h"
#include "MS_ContentButtonWidget.generated.h"

namespace ExtensionAnim
{
	const FName OpenExtension = TEXT("OpenExtension");
	const FName CloseExtension = TEXT("CloseExtension");
}
/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_ContentButtonWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	void SetIconImage(UTexture2D* aIconImage) const;
	void SetVerticalBoxVisibility(bool bShow) const;

	virtual void OnAnimFinished(const FName& aAnimName) override;
	
	UCommonButtonBase::FCommonButtonEvent& GetOnClickedDelegate() const;
	
	void OpenExtensionUI();

private:
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_Button> CPP_ContentButton = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UImage> CPP_IconImage = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UCanvasPanel> CPP_ExtensionPanel = nullptr;
	bool bOpen = false;
};
