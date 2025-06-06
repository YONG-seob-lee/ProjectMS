﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_CheckBoxItemBase.h"
#include "MS_TutorialSkipSettingWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_TutorialSkipSettingWidget : public UMS_CheckBoxItemBase
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void OnCheckChanged(bool IsChecked);
};
