// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_Widget.h"
#include "Command/SceneCommand/MS_SceneCommand.h"
#include "System/General/MS_GeneralWidget.h"
#include "System/Modal/MS_ModalWidget.h"
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
	void ActivatePreventionCover(bool bShow) const;
	void SetContentWidgetRender(EMS_TransitionStyle aTransitionStyle) const;
	void SetContentWidgetTransition(EMS_TransitionStyle aTransitionStyle, EMS_FadeAnimationCurveType aFadeAnimationCurveType, float aFadeProgressRate) const;
	void ResetCanvasZOrder() const;

	void ResetToastPanel() const;
	
	void ShowToastMessage(const FString& Message) const;

	void ShowRotateWidget() const;
	void ShowModalWidget(const FMS_ModalParameter& aModalParameter) const;
	void SetGeneralWidget(EMS_LevelType aLevelType) const;
	void ShowGeneralWidget(bool bShow) const;
	void CloseModalWidget() const;

	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
	TObjectPtr<class UMS_CanvasPanel> CPP_CutoutFrameCanvasPanel = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
	TObjectPtr<UMS_CanvasPanel> CPP_ContentFrameCanvasPanel = nullptr;
	
private:
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<UMS_CanvasPanel> CPP_LoadingPanel = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<UMS_CanvasPanel> CPP_MessagePanel = nullptr;
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_WidgetSwitcher> CPP_MessageWidgetSwitcher = nullptr;
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_ToastWidget> CPP_ToastWidget = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_RotateWidget> CPP_RotateWidget = nullptr;
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_ModalWidget> CPP_ModalWidget = nullptr;
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_GeneralWidget> CPP_GeneralWidget = nullptr;
	
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UImage> CPP_PreventionCoverImage = nullptr;
	
	FVector2D CutoutFrameSize = {};
	FVector2D ContentFrameSize = {};
};
