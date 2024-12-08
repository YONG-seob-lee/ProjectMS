// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "Widget/MS_Widget.h"
#include "MS_ContentButtonWidget.generated.h"

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
	
	UCommonButtonBase::FCommonButtonEvent& GetOnClickedDelegate() const;
private:
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_Button> CPP_ContentButton = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UImage> CPP_IconImage = nullptr;
};
