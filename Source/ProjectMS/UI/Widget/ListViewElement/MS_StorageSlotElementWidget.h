// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Widget/MS_Widget.h"
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

private:
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_SlotWidget> CPP_SlotWidget = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_CountWidget> CPP_CountWidget = nullptr;
};
