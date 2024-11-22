// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_Widget.h"
#include "MS_RootWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_RootWidget : public UMS_Widget
{
	GENERATED_BODY()

public:
	static FName GetWidgetName() { return TEXT("Root"); }
	UMS_RootWidget(const FObjectInitializer& aObjectInitializer);
	virtual void NativeOnInitialized() override;
	virtual void OnRuntimeInitialize() override;
	
	FORCEINLINE FVector2D GetCutoutFrameSize() const { return CutoutFrameSize; }
	FORCEINLINE FVector2D GetContentFrameSize() const { return ContentFrameSize; }

	void AttachContentWidget(const TObjectPtr<UMS_Widget>& aContentWidget) const;
	void RefreshContentCanvas() const;
	void SetShowLoadingWidget(bool bShow) const;

	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
	TObjectPtr<UMS_CanvasPanel> CPP_CutoutFrameCanvasPanel = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
	TObjectPtr<UMS_CanvasPanel> CPP_ContentFrameCanvasPanel = nullptr;
	
private:
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_DefaultLoadingWidget> CPP_LoadingWidget = nullptr;
	FVector2D CutoutFrameSize = {};
	FVector2D ContentFrameSize = {};
};
