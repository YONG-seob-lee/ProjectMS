// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "ContentsUtilities/MS_GameProcessDefine.h"
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
	virtual void NativeOnItemSelectionChanged(bool bIsSelected) override;

private:
	FMS_GameDate Date;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_Days = nullptr;
};
