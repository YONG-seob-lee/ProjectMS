// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Table/RowBase/MS_ItemData.h"
#include "Widget/MS_Widget.h"
#include "MS_SlotManagementWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_SlotManagementWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	void SettingItems(TArray<TObjectPtr<class UMS_ItemElementData>>& aItemElementDatas) const;
	
private:
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UImage> CPP_StorageSlotImage = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_TileView> CPP_SelectItemTileView = nullptr;
};