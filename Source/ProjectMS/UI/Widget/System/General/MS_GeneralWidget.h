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

namespace BGM
{
	const FName Town = TEXT("TownBGM");
	const FName Market = TEXT("MarketBGM");
}
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

	void RequestPassTimer() const;

	void Test(int32 test);
private:
	void InitLeftExpander();
	
	void OnClickedLeftButton();
	void OnClickedRightButton();
	void OnClickedMenuElementButton();

	// Left Expander Button
	void OnClickedExpanderButton();

	void OnClickedBuyItemButton();
	void OnClickedBuyFurnitureButton();
	void OnClickedHireStaffButton();
	void OnClickedManageStaffButton();
	void OnClickedManageCustomerButton();
	void OnClickedFinancialIndicatorButton();

	void OnUpdateTimer(int32 ScheduleType);

	void OpenLeftExpander() const;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UMS_TimeLineWidget> CPP_TimeLineWidget = nullptr;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UCanvasPanel> CPP_LeftPanel = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UCanvasPanel> CPP_LeftExpanderPanel = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_GeneralButton> CPP_LeftExpanderButton01 = nullptr;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_GeneralButton> CPP_LeftExpanderButton02 = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_GeneralButton> CPP_LeftExpanderButton03 = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_GeneralButton> CPP_LeftExpanderButton04 = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_GeneralButton> CPP_LeftExpanderButton05 = nullptr;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_GeneralButton> CPP_LeftExpanderButton06 = nullptr;
	
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

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_DescriptionWidget> CPP_DescriptionWidget = nullptr;

	EMS_GeneralButtonType LeftButtonType = EMS_GeneralButtonType::None;
	EMS_GeneralButtonType RightButtonType = EMS_GeneralButtonType::None;
};
