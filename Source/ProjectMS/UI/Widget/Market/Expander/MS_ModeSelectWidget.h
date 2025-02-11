// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ContentsUtilities/MS_LevelDefine.h"
#include "Manager_Client/MS_ModeManager.h"
#include "Widget/MS_Widget.h"
#include "MS_ModeSelectWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_ModeSelectWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	FORCEINLINE void GetOnClickedModeButtonFunc(const TFunction<void(EMS_ModeState)>& aFunc) { OnClickedModeButtonCallback = aFunc; }

	void SwitchWidget(EMS_ModeState aModeState) const;
private:
	void InitCategory() const;
	void RefreshConstructListItems(EMS_ZoneType aZoneType);
	
	void OnClickModeButton(EMS_ModeState aModeState);
	void OnClickedCategory(int32 aCategoryType);

	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_Button> CPP_ModeButton01 = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_WidgetSwitcher> CPP_WidgetSwitcher = nullptr;

	TFunction<void(EMS_ModeState)> OnClickedModeButtonCallback = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_TileView> CPP_ConstructCategoryTileView = nullptr;
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_TileView> CPP_ConstructItemTileView = nullptr;
};
