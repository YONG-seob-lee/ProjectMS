﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "ContentsUtilities/MS_LevelDefine.h"
#include "MS_ConstructExpanerWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_ConstructExpanerWidget : public UMS_Widget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	FORCEINLINE void SetOnClickedCategoryButtonFunc(const TFunction<void(int32)>& aFunc) { OnClickedCategoryButtonCallback = aFunc; }
	FORCEINLINE void SetOnClickedConstructItemFunc(const TFunction<void()>& aFunc) { OnClickedConstructItemCallback = aFunc; }

	void InitCategory() const;
	void RefreshConstructListItems(EMS_ZoneType aZoneType) const;
	
private:
	
	void OnClickedCategoryButton(UObject* Object);
	void OnClickedCategory(int32 aCategoryType);


private:
	TFunction<void(int32)> OnClickedCategoryButtonCallback = nullptr;
	TFunction<void()> OnClickedConstructItemCallback = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_ListView> CPP_ExpanderCategoryListView = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_WidgetSwitcher> CPP_ItemExistSwitcher = nullptr;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_ListView> CPP_ExpanderItemListView = nullptr;
};
