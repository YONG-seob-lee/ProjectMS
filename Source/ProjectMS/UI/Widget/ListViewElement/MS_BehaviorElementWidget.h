﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Widget/MS_Widget.h"
#include "MS_BehaviorElementWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_BehaviorElementWidget : public UMS_Widget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnListItemObjectSet(UObject* aListItemObject) override;

private:
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_Minute = nullptr;
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_BehaviorDesc = nullptr;
};
