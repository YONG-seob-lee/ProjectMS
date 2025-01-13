// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "MS_StorageSlotManagementWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_StorageSlotManagementWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	UPROPERTY(meta= (BindWidget))
	TObjectPtr<class UMS_WidgetSwitcher> CPP_WidgetSwitcher = nullptr;

	UPROPERTY(meta= (BindWidget))
	TObjectPtr<class UMS_SlotWidget> CPP_Slot01 = nullptr;
	UPROPERTY(meta= (BindWidget))
	TObjectPtr<class UMS_SlotWidget> CPP_Slot02 = nullptr;
	UPROPERTY(meta= (BindWidget))
	TObjectPtr<class UMS_SlotWidget> CPP_Slot03 = nullptr;
	UPROPERTY(meta= (BindWidget))
	TObjectPtr<class UMS_SlotWidget> CPP_Slot04 = nullptr;
};
