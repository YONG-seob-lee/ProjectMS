// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Widget/MS_Widget.h"
#include "MS_MenuListElementWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_MenuListElementWidget : public UMS_Widget, public IUserObjectListEntry
{
	GENERATED_BODY()
public:

	virtual void NativeOnListItemObjectSet(UObject* aListItemObject) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnItemSelectionChanged(bool bIsSelected) override;
	
private:
	FString MenuName = FString();
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UImage> CPP_MenuImage = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_MenuName = nullptr;
};
