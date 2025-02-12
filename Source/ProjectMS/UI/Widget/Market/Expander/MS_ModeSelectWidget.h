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

private:
	void InitCategory() const;
	void RefreshConstructListItems(EMS_ZoneType aZoneType);
	
	void OnClickedModeButton(UObject* Object);
	void OnClickedCategory(int32 aCategoryType);

	TFunction<void(EMS_ModeState)> OnClickedModeButtonCallback = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_ListView> CPP_ConstructCategoryListView = nullptr;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_ListView> CPP_ConstructItemListView = nullptr;
};
