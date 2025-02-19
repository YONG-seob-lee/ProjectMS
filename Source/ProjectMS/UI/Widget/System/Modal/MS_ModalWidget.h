// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "MS_ModalWidget.generated.h"

namespace DefaultModal
{
	const FSoftObjectPath InModalWidgetPath = FSoftObjectPath(TEXT("/Game/UI/Widget/SystemWidgets/Modal/InModalWidget.InModalWidget"));
}

namespace ModalWidgetAnimation
{
	const FName Open = TEXT("OpenModal");
	const FName Close = TEXT("CloseModal");
}

struct FMS_ModalParameter
{
public:
	UMS_Widget* InModalWidget = nullptr;
	bool bPlayOpenAnimation = true;
	bool bPlayCloseAnimation = true;
	FVector2D InModalPosition = FVector2D::ZeroVector;
	TFunction<void()> OnCloseWidgetCallback = nullptr;
};

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_ModalWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void OnAnimFinished(const FName& aAnimName) override;

	void SetModal(const FMS_ModalParameter& aModalParameter);
	void CloseModal(const TFunction<void()>& _OnCloseModalWidgetCallback);

	void SetInModalPosition(const FVector2D& aInModalPosition) const;
private:
	void SetModalInternal(const TObjectPtr<UMS_Widget>& aNewWidget);
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_Button> CPP_BlurButton = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UCanvasPanel> CPP_InModalPanel = nullptr;
	
	bool bPlayCloseAnimation = true;
	TFunction<void()> OnCloseModalWidgetCallback = nullptr;
};
