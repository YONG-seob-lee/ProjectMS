// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "MS_MenuExpanderWidget.generated.h"

/**
 * 
 */
class UMS_ListItemData : public UObject
{
public:
	UTexture2D* ItemTexture2D = nullptr;
	FString ItemName = FString();
};


UCLASS()
class PROJECTMS_API UMS_MenuExpanderWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	void SetList();
private:
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_TileView> CPP_MenuList = nullptr;
};
