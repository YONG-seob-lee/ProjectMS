// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Button/MS_GeneralButton.h"
#include "Widget/MS_Widget.h"
#include "MS_GeneralWidget.generated.h"

UENUM()
enum class EMS_GeneralWidgetType
{
	None = 0,
	Lobby,
	Town,
	Market,
};
/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_GeneralWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	
	void SetType(EMS_GeneralWidgetType aType);
	
private:
	void OnClickedLeftButton();
	void OnClickedRightButton();
	void OnClickedExpanderButton();
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UCanvasPanel> CPP_LeftPanel = nullptr;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UCanvasPanel> CPP_RightPanel = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_GeneralButton> CPP_LeftButton = nullptr;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_GeneralButton> CPP_RightButton = nullptr;

	UPROPERTY(meta= (BindWidget))
	TObjectPtr<class UCanvasPanel> CPP_MenuExpanderPanel = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_TileView> CPP_MenuTileView = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_GeneralButton> CPP_ExpanderButton = nullptr;

	EMS_GeneralButtonType LeftButtonType = EMS_GeneralButtonType::None;
	EMS_GeneralButtonType RightButtonType = EMS_GeneralButtonType::None;
};
