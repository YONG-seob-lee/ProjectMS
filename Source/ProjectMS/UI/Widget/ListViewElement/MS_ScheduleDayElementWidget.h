// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Widget/MS_Widget.h"
#include "MS_ScheduleDayElementWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_ScheduleDayElementWidget : public UMS_Widget, public IUserObjectListEntry
{
	GENERATED_BODY()
public:
	virtual void NativeOnListItemObjectSet(UObject* aListItemObject) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

private:
	int32 Day = 0;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_Days = nullptr;
};
