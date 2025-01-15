// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Widget/MS_Widget.h"
#include "MS_OrderElementWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_OrderElementWidget : public UMS_Widget, public IUserObjectListEntry
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	virtual void NativeOnListItemObjectSet(UObject* aListItemObject) override;
	virtual void NativeOnItemSelectionChanged(bool bIsSelected) override;

private:
	void OnClickedCountButton(int32 aCount);

	int32 ItemCheckedCount = 0;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UImage> CPP_ItemImage = nullptr;

	UPROPERTY(Meta= (BindWidget))
	TObjectPtr<class UTextBlock> CPP_ItemName = nullptr;

	UPROPERTY(Meta= (BindWidget))
	TObjectPtr<class UTextBlock> CPP_ItemPrice = nullptr;

	UPROPERTY(Meta= (BindWidget))
	TObjectPtr<class UTextBlock> CPP_ItemCount = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_Button> CPP_CountUpButton = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_Button> CPP_CountDownButton = nullptr;
};
