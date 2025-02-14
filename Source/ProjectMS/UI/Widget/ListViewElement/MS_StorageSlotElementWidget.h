// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "ContentsUtilities/MS_LevelDefine.h"
#include "ContentsUtilities/MS_ItemDefine.h"
#include "MS_StorageSlotElementWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_StorageSlotElementWidget : public UMS_Widget, public IUserObjectListEntry
{
	GENERATED_BODY()
public:
	virtual void NativeOnListItemObjectSet(UObject* aListItemObject) override;
	virtual void NativeOnItemSelectionChanged(bool bIsSelected) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override; 

private:
	void UpdateWhenStorageRequestStatus();
	void UpdateWhenStorageCurrentStatus();
	void UpdateWhenRequestable();
	
private:
	EMS_ZoneType OwnerZoneType = EMS_ZoneType::None;
	EMS_ItemSlotUIType SlotUIType = EMS_ItemSlotUIType::None;
	int32 SlotIndex = 0;
	FMS_SlotData SlotData;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_ItemSlotWidget> CPP_ItemSlotWidget = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_WidgetSwitcher> CPP_TextSwitcher = nullptr;
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_CountWidget> CPP_CountWidget = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_RemainCount = nullptr;
};
