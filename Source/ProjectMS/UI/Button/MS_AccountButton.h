﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_Button.h"
#include "MS_AccountButton.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_AccountButton : public UMS_Button
{
	GENERATED_BODY()
public:
	void SetAccountButton(bool bAlreadyLogin) const;
private:
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_WidgetSwitcher> CPP_AccountButtonSwitcher = nullptr;
};
